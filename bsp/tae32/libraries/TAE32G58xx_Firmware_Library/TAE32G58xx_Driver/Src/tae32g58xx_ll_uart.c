/**
  ******************************************************************************
  * @file    tae32g58xx_ll_uart.c
  * @author  MCD Application Team
  * @brief   UART LL module driver
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

#define DBG_TAG             "UART"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup UART_LL UART LL
  * @brief    UART LL module driver
  * @{
  */

#ifdef LL_UART_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/* Private Variables ---------------------------------------------------------*/
/** @defgroup UART_LL_Private_Variables UART LL Private Variables
  * @brief    UART LL Private Variables
  * @{
  */

/**
  * @brief Default UART LL Config
  */
static const UART_LLCfgTypeDef uart_ll_cfg_def = {
    .tx_rx_swap_en = false,
    .rx_timeout_en = false,
    .one_wire_en = false,
    .tx_pol = UART_PIN_POL_INACT_HIGH,
    .rx_pol = UART_PIN_POL_INACT_HIGH,
    .bit_order = UART_BIT_ORDER_LSB,
    .tx_fifo_empty_thres = 0,   // 0~15
    .rx_fifo_full_thres  = 1,   // 1~16
    .rx_timeout = 0,
    .rx_timeout_mode = UART_RTO_MODE_FNE_RXIDEL,
};

/**
  * @brief UART Handle global variable
  */
static UART_HandleTypeDef uart_hdl_global[UART_INSTANCE_NUMS];

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @addtogroup UART_LL_Exported_Functions UART LL Exported Functions
  * @brief    UART LL Exported Functions
  * @{
  */
static UART_HandleTypeDef *UART_Handle_Get(UART_TypeDef *Instance);

static void UART_TxISR_8BIT(UART_TypeDef *Instance);
static void UART_TxISR_16BIT(UART_TypeDef *Instance);
static void UART_RxISR_8BIT(UART_TypeDef *Instance);
static void UART_RxISR_16BIT(UART_TypeDef *Instance);
static void UART_TxDone_ISR(UART_TypeDef *Instance);
static void UART_RxTimeout_ISR(UART_TypeDef *Instance);

#ifdef LL_DMA_MODULE_ENABLED
    static DMA_ChannelETypeDef UART_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    static void UART_DMA_DeInit(DMA_ChannelETypeDef ch);

    static void UART_DMATransmitCplt(UART_TypeDef *Instance);
    static void UART_DMAReceiveCplt(UART_TypeDef *Instance);
    static void UART_DMAHalfTransmitCplt(UART_TypeDef *Instance);
    static void UART_DMAHalfReceiveCplt(UART_TypeDef *Instance);
    static void UART_DMATransmitError(UART_TypeDef *Instance);
    static void UART_DMAReceiveError(UART_TypeDef *Instance);
#endif
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Functions UART LL Exported Functions
  * @brief    UART LL Exported Functions
  * @{
  */

/** @defgroup UART_LL_Exported_Functions_Group1 UART Init and DeInit Functions
  * @brief    UART Init and DeInit Functions
  * @{
  */

/**
  * @brief  UART LL Init
  * @param  Instance Specifies UART peripheral
  * @param  init UART Init Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_UART_Init(UART_TypeDef *Instance, UART_InitTypeDef *init)
{
    uint32_t baud_rate = 1;
    UART_LLCfgTypeDef *ll_cfg;
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(init != NULL);
    assert_param(init->baudrate);

    if (!IS_UART_ALL_INSTANCE(Instance) || init == NULL || !init->baudrate) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_RESET || uart_hdl->rx_ctrl.state != UART_STATE_RESET) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't being used\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    //It must disable the UART while configuring certain registers
    __LL_UART_Dis(Instance);

    uart_hdl->tx_ctrl.state = UART_STATE_BUSY;
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY;

    //LL config pointer config
    LL_FUNC_ALTER(init->ll_cfg == NULL, ll_cfg = (UART_LLCfgTypeDef *)&uart_ll_cfg_def, ll_cfg = init->ll_cfg);

    /* init the low level hardware eg. Clock, NVIC */
    LL_UART_MspInit(Instance);

    /* Reset UART FIFO */
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_RxFIFO_Reset(Instance);

    //LL config
    __LL_UART_TxPinPol_Set(Instance, ll_cfg->tx_pol);
    __LL_UART_RxPinPol_Set(Instance, ll_cfg->rx_pol);
    __LL_UART_BitOrder_Set(Instance, ll_cfg->bit_order);
    __LL_UART_RxFIFOFullThres_Set(Instance, ll_cfg->rx_fifo_full_thres);
    __LL_UART_TxFIFOEmptyThres_Set(Instance, ll_cfg->tx_fifo_empty_thres);
    __LL_UART_RxTimeoutTime_Set(Instance, ll_cfg->rx_timeout);
    LL_FUNC_ALTER(ll_cfg->tx_rx_swap_en, __LL_UART_TxRxPinSwap_En(Instance), __LL_UART_TxRxPinSwap_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->one_wire_en, __LL_UART_OneWire_En(Instance), __LL_UART_OneWire_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->rx_timeout_en, __LL_UART_RxTimeout_En(Instance), __LL_UART_RxTimeout_Dis(Instance));

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_UART))) {
        __LL_UART_RTOMode_Set(Instance, ll_cfg->rx_timeout_mode);
    }

    //User config
    if (init->parity == UART_PARITY_NO) {
        __LL_UART_Parity_Dis(Instance);
    } else {
        __LL_UART_Parity_En(Instance);
        __LL_UART_Parity_Set(Instance, init->parity);
    }

    __LL_UART_StopLen_Set(Instance, init->stop_len);
    __LL_UART_DatLen_Set(Instance, init->dat_len);

    //Extend Mode Config
    if (init->ext_bit_en) {
        __LL_UART_ExtBit_En(Instance);

        __LL_UART_RxExtMode_Set(Instance, init->rx_ext_mode);
        __LL_UART_RxExtAddr_Set(Instance, init->rx_addr_ext);
    } else {
        __LL_UART_ExtBit_Dis(Instance);
    }

    //Baudrate Config
    if (Instance == UART0 || Instance == UART1 || Instance == UART2) {
        baud_rate = (LL_RCU_APB0ClkGet() + init->baudrate / 2) / init->baudrate;
    } else if (Instance == UART3 || Instance == UART4) {
        baud_rate = (LL_RCU_APB1ClkGet() + init->baudrate / 2) / init->baudrate;
    }

    __LL_UART_Baudrate_Set(Instance, baud_rate);
    __LL_UART_OverSampleMode_Set(Instance, init->over_samp);

    //Transfer State Init
    uart_hdl->tx_ctrl.state = UART_STATE_READY;
    uart_hdl->rx_ctrl.state = UART_STATE_READY;
    uart_hdl->user_callback = init->user_callback;

#ifdef LL_DMA_MODULE_ENABLED
    uart_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    //All Interrupt Pending Clear
    __LL_UART_AllIntPnd_Clr(Instance);

    //TX/RX Enable
    __LL_UART_Tx_En(Instance);
    __LL_UART_Rx_En(Instance);

    //UART Enable
    __LL_UART_En(Instance);

    return LL_OK;
}

/**
  * @brief  UART LL DeInit
  * @param  Instance Specifies UART peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_UART_DeInit(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state == UART_STATE_BUSY_TX || uart_hdl->rx_ctrl.state == UART_STATE_BUSY_RX) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    uart_hdl->tx_ctrl.state = UART_STATE_BUSY;
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY;

    //UART Disable
    __LL_UART_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_UART_MspDeInit(Instance);

    memset((void *)uart_hdl, 0, sizeof(UART_HandleTypeDef));
    uart_hdl->tx_ctrl.state = UART_STATE_RESET;
    uart_hdl->rx_ctrl.state = UART_STATE_RESET;

#ifdef LL_DMA_MODULE_ENABLED
    uart_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    return LL_OK;
}

/**
  * @brief  UART LL Reset
  * @param  Instance Specifies UART peripheral
  * @return Status of the Reset
  */
LL_StatusETypeDef LL_UART_Reset(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;
    IRQn_Type irq_num;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } 

    irq_num = GET_UART_IRQ_NUMBER(Instance);
    if (irq_num < 0) {
        LOG_E("UART IRQ does not exist!\n");
        return LL_ERROR;
    }

    //Clear pending and interrupt disable
    __disable_irq();
    NVIC_DisableIRQ(irq_num);
    (void) CLEAR_BIT(Instance->CR0, 0x7UL);
    (void) SET_BIT(Instance->CR0, 0x18UL);
    (void) CLEAR_BIT(Instance->CR0, 0x33FFE0UL);
    CLEAR_BIT(Instance->INTEN, 0xffffffffUL);
    NVIC_ClearPendingIRQ(irq_num);
    __LL_UART_RxFIFO_Reset(Instance);
    __LL_UART_TxFIFO_Reset(Instance);
    __enable_irq();

    __LL_UART_AllIntPnd_Clr(Instance);

    uart_hdl->tx_ctrl.state = UART_STATE_BUSY;
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY;

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_UART_MspDeInit(Instance);

    memset((void *)uart_hdl, 0, sizeof(UART_HandleTypeDef));
    uart_hdl->tx_ctrl.state = UART_STATE_RESET;
    uart_hdl->rx_ctrl.state = UART_STATE_RESET;

#ifdef LL_DMA_MODULE_ENABLED
    uart_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
#endif

    return LL_OK;
}

/**
  * @brief  Initializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_MspInit(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the UART MSP
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_MspDeInit(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Register an User UART Callback
  * @note   User can register callback only in UART Ready State
  * @param  Instance Specifies UART peripheral
  * @param  CallbackID ID of the callback to be registered
  * @param  pCallback pointer to the Callback function
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_RegisterCallback(UART_TypeDef *Instance, UART_UserCallbackIdETypeDef CallbackID, UART_UserCallback pCallback)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    }

    //Check callback pointer valid or not
    if (pCallback == NULL) {
        LOG_E("The callback pointer which to be registered is NULL!\n");
        return LL_INVALID;
    }

    //Register user callback
    switch (CallbackID) {
        case UART_TX_CPLT_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.TxCpltCallback = pCallback;
            break;

        case UART_RX_CPLT_CB_ID:
            if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.RxCpltCallback = pCallback;
            break;

        case UART_TX_HALF_CPLT_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.TxHalfCpltCallback = pCallback;
            break;

        case UART_RX_HALF_CPLT_CB_ID:
            if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.RxHalfCpltCallback = pCallback;
            break;

        case UART_ERROR_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY || uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't register Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.ErrorCallback = pCallback;
            break;

        default:
            LOG_E("UART user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  UnRegister an User UART Callback
  * @note   User can unregister callback only in UART Ready State
  * @param  Instance Specifies UART peripheral
  * @param  CallbackID ID of the callback to be unregistered
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_UnRegisterCallback(UART_TypeDef *Instance, UART_UserCallbackIdETypeDef CallbackID)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    }

    //UnRegister user callback
    switch (CallbackID) {
        case UART_TX_CPLT_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.TxCpltCallback = NULL;
            break;

        case UART_RX_CPLT_CB_ID:
            if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.RxCpltCallback = NULL;
            break;

        case UART_TX_HALF_CPLT_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.TxHalfCpltCallback = NULL;
            break;

        case UART_RX_HALF_CPLT_CB_ID:
            if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.RxHalfCpltCallback = NULL;
            break;

        case UART_ERROR_CB_ID:
            if (uart_hdl->tx_ctrl.state != UART_STATE_READY || uart_hdl->rx_ctrl.state != UART_STATE_READY) {
                LOG_E("This UART[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't unregister Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            uart_hdl->user_callback.ErrorCallback = NULL;
            break;

        default:
            LOG_E("UART user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup UART_LL_Exported_Functions_Group2 UART Transmit and Recieve Function
  * @brief    UART Transmit and Recieve Function
  * @{
  */

/**
  * @brief  Send an amount of data in blocking mode
  * @note   When UART parity is not enabled, and Word Length is configured to 9 bits,
  *         the sent data is handled as a set of u16. In this case, size must indicate the number
  *         of u16 provided through buf.
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be sent
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Transmit_CPU(UART_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    bool tx_9bits_en;
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx READY state, can't start Tx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    uart_hdl->tx_ctrl.state = UART_STATE_BUSY_TX;
    uart_hdl->tx_ctrl.cnt = 0;
    uart_hdl->tx_ctrl.isr = NULL;
    uart_hdl->tx_ctrl.buf = buf;
    uart_hdl->tx_ctrl.size = size;
    tx_9bits_en = (bool)(__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsTxExtAddrMatchMode(Instance) &&
                         (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b);

    //Clear TxFIFO and TX Done Pending
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_TxDoneIntPnd_Clr(Instance);
    __LL_UART_Tx_En(Instance);
    tickstart = LL_GetTick();

    //Transmit data loop
    while (uart_hdl->tx_ctrl.cnt < uart_hdl->tx_ctrl.size) {
        //if CPU has been broken a long time by Interrupt, the TxDone flag maybe set
        if (__LL_UART_IsTxDoneIntPnd(Instance)) {
            __LL_UART_TxDoneIntPnd_Clr(Instance);
        }

        //Wait TxFIFO to be not full
        while (__LL_UART_IsTxFIFOFull(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Write data to TxFIFO
        if (tx_9bits_en) {
            __LL_UART_TxDat9bits_Write(Instance, *(uint16_t *)uart_hdl->tx_ctrl.buf);
            uart_hdl->tx_ctrl.buf += 2;
        } else {
            __LL_UART_TxDat8bits_Write(Instance, *uart_hdl->tx_ctrl.buf++);
        }

        uart_hdl->tx_ctrl.cnt++;
    }

    //Wait for UART Transmit completed
    while (!__LL_UART_IsTxDoneIntPnd(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear TX Done Pending
    __LL_UART_TxDoneIntPnd_Clr(Instance);

    ret = LL_OK;

exit:
    uart_hdl->tx_ctrl.state = UART_STATE_READY;
    return ret;
}

/**
  * @brief  Receive an amount of data in blocking mode
  * @note   When UART parity is not enabled, and Word Length is configured to 9 bits ,
  *         the received data is handled as a set of u16. In this case, size must indicate the number
  *         of u16 available through buf.
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be sent
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Receive_CPU(UART_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    bool rx_9bits_en;
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx READY state, can't start Rx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY_RX;
    uart_hdl->rx_ctrl.cnt = 0;
    uart_hdl->rx_ctrl.isr = NULL;
    uart_hdl->rx_ctrl.buf = buf;
    uart_hdl->rx_ctrl.size = size;
    rx_9bits_en = (bool)(__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsRxExtAddrMatchMode(Instance) &&
                         (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b);

    //Clear RxFIFO
    __LL_UART_RxFIFO_Reset(Instance);
    __LL_UART_Rx_En(Instance);
    tickstart = LL_GetTick();

    //Receive data loop
    while (uart_hdl->rx_ctrl.cnt < uart_hdl->rx_ctrl.size) {
        //Wait RxFIFO to be not empty
        while (__LL_UART_IsRxFIFOEmpty(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Read data from RxFIFO
        if (rx_9bits_en) {
            *(uint16_t *)uart_hdl->rx_ctrl.buf = (uint16_t)(__LL_UART_RxDat9bits_Read(Instance));
            uart_hdl->rx_ctrl.buf += 2;
        } else {
            *uart_hdl->rx_ctrl.buf++ = (uint8_t)(__LL_UART_RxDat8bits_Read(Instance));
        }

        uart_hdl->rx_ctrl.cnt++;
    }

    ret = LL_OK;

exit:
    uart_hdl->rx_ctrl.state = UART_STATE_READY;
    return ret;
}


/**
  * @brief  Send an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Transmit_IT(UART_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx READY state, can't start Tx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    uart_hdl->tx_ctrl.state = UART_STATE_BUSY_TX;
    uart_hdl->tx_ctrl.buf = buf;
    uart_hdl->tx_ctrl.size = size;
    uart_hdl->tx_ctrl.cnt = 0;
    LL_FUNC_ALTER(__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsTxExtAddrMatchMode(Instance) &&
                  (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b,
                  uart_hdl->tx_ctrl.isr = UART_TxISR_16BIT,
                  uart_hdl->tx_ctrl.isr = UART_TxISR_8BIT);

    //Clear TxFIFO and TX Done Pending
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_TxDoneIntPnd_Clr(Instance);
    __LL_UART_Tx_En(Instance);

    //Tx Empty Interrupt Enable
    __LL_UART_TxEmpty_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Receive_IT(UART_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx READY state, can't start Rx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY_RX;
    uart_hdl->rx_ctrl.buf = buf;
    uart_hdl->rx_ctrl.size = size;
    uart_hdl->rx_ctrl.cnt = 0;
    LL_FUNC_ALTER(__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsRxExtAddrMatchMode(Instance) &&
                  (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b,
                  uart_hdl->rx_ctrl.isr = UART_RxISR_16BIT,
                  uart_hdl->rx_ctrl.isr = UART_RxISR_8BIT);

    //Clear RxFIFO
    __LL_UART_RxFIFO_Reset(Instance);
    __LL_UART_Rx_En(Instance);

    //Rx TimeOut Interrupt Enable if RxFIFO Full Trigger Level more than 1
    if (__LL_UART_RxFIFOFullThres_Get(Instance) > 1) {
        __LL_UART_RxTimeout_INT_En(Instance);
    }

    //RxFIFO Full Interrupt Enable
    __LL_UART_RxFull_INT_En(Instance);

    return LL_OK;
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  Send an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Transmit_DMA(UART_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    uint32_t dma_size;
    UART_HandleTypeDef *uart_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx READY state, can't start Tx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0, sizeof(dma_user_cfg));

    if (__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsTxExtAddrMatchMode(Instance) &&
        (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b) {
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        dma_size = size * 2;
    } else {
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        dma_size = size;
    }

    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == UART0) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART0_TX;
    } else if (Instance == UART1) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART1_TX;
    } else if (Instance == UART2) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART2_TX;
    } else if (Instance == UART3) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART3_TX;
    } else if (Instance == UART4) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_UART4_TX;
    } else {
        LOG_E("UART DMA destination handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_arg = (void *)Instance;
    dma_user_cfg.end_callback = (DMA_IRQCallback)UART_DMATransmitCplt;
    dma_user_cfg.err_arg = (void *)Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)UART_DMATransmitError;
    dma_user_cfg.half_arg = (void *)Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)UART_DMAHalfTransmitCplt;

    uart_hdl->tx_ctrl.dma_ch = UART_DMA_Init(&dma_user_cfg);

    if (uart_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("UART transmit request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    uart_hdl->tx_ctrl.state = UART_STATE_BUSY_TX;
    uart_hdl->tx_ctrl.buf = buf;
    uart_hdl->tx_ctrl.size = dma_size;
    uart_hdl->tx_ctrl.cnt = 0;
    uart_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO and TX Done Pending
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_TxDoneIntPnd_Clr(Instance);
    __LL_UART_Tx_En(Instance);

    //UART TX DMA Enable
    __LL_UART_TxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, uart_hdl->tx_ctrl.dma_ch, (uint32_t)uart_hdl->tx_ctrl.buf, (uint32_t)&Instance->TDR, uart_hdl->tx_ctrl.size);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies UART peripheral
  * @param  buf Pointer to data buffer (u8 or u16 data elements)
  * @param  size Amount of data elements (u8 or u16) to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_Receive_DMA(UART_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    uint32_t dma_size;
    UART_HandleTypeDef *uart_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_UART_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx READY state, can't start Rx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0, sizeof(dma_user_cfg));

    if (__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsRxExtAddrMatchMode(Instance) &&
        (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b) {
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        dma_size = size * 2;
    } else {
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        dma_size = size;
    }

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == UART0) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_UART0_RX;
    } else if (Instance == UART1) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_UART1_RX;
    } else if (Instance == UART2) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_UART2_RX;
    } else if (Instance == UART3) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_UART3_RX;
    } else if (Instance == UART4) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_UART4_RX;
    } else {
        LOG_E("UART DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Receive Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_arg = (void *)Instance;
    dma_user_cfg.end_callback = (DMA_IRQCallback)UART_DMAReceiveCplt;
    dma_user_cfg.err_arg = (void *)Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)UART_DMAReceiveError;
    dma_user_cfg.half_arg = (void *)Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)UART_DMAHalfReceiveCplt;

    //Transmit config
    uart_hdl->rx_ctrl.state = UART_STATE_BUSY_RX;
    uart_hdl->rx_ctrl.buf = buf;
    uart_hdl->rx_ctrl.size = dma_size;
    uart_hdl->rx_ctrl.cnt = 0;
    uart_hdl->rx_ctrl.isr = NULL;

    uart_hdl->rx_ctrl.dma_ch = UART_DMA_Init(&dma_user_cfg);

    if (uart_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("UART receive request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Clear RxFIFO
    __LL_UART_RxFIFO_Reset(Instance);
    __LL_UART_Rx_En(Instance);

    //UART RX DMA Enable
    __LL_UART_RxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, uart_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->RDR, (uint32_t)uart_hdl->rx_ctrl.buf, uart_hdl->rx_ctrl.size);

    return LL_OK;
}

#endif

/**
  * @}
  */


/** @defgroup UART_LL_Exported_Functions_Group3 UART Misc Functions
  * @brief    UART Misc Functions
  * @{
  */

/**
  * @brief  Abort ongoing Transmit transfer for CPU blocking mode
  * @param  Instance Specifies UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_AbortTransmit_CPU(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_BUSY_TX) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx state, can't abort Tx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check UART is in Tx IT state or not
    if (uart_hdl->tx_ctrl.isr) {
        LOG_E("This UART[0x%08" PRIx32 "] is in Tx_IT state, can't abort it through CPU interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

#ifdef LL_DMA_MODULE_ENABLED

    //Check UART is in Tx DMA state or not
    if (uart_hdl->tx_ctrl.dma_ch != DMA_CHANNEL_INVALID) {
        LOG_E("This UART[0x%08" PRIx32 "] is in Tx_DMA state, can't abort it through CPU interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

#endif

    //Clear TxFIFO
    __LL_UART_TxFIFO_Reset(Instance);

    //Set to complete
    uart_hdl->tx_ctrl.cnt = uart_hdl->tx_ctrl.size;
    uart_hdl->tx_ctrl.state = UART_STATE_READY;

    return LL_OK;
}

/**
  * @brief  Abort ongoing Receive transfer for CPU blocking mode
  * @param  Instance Specifies UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_AbortReceive_CPU(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_BUSY_RX) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx state, can't abort Rx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check UART is in Rx IT state or not
    if (uart_hdl->rx_ctrl.isr) {
        LOG_E("This UART[0x%08" PRIx32 "] is in Rx_IT state, can't abort it through CPU interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

#ifdef LL_DMA_MODULE_ENABLED

    //Check UART is in Rx DMA state or not
    if (uart_hdl->rx_ctrl.dma_ch != DMA_CHANNEL_INVALID) {
        LOG_E("This UART[0x%08" PRIx32 "] is in Rx_DMA state, can't abort it through CPU interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

#endif

    //Clear RxFIFO
    __LL_UART_RxFIFO_Reset(Instance);

    //Check RxFIFO any error or not
    if (__LL_UART_IsRxFIFOErr(Instance)) {
        __LL_UART_RxFIFOErrIntPnd_Clr(Instance);
    }

    //Set to complete
    uart_hdl->rx_ctrl.cnt = uart_hdl->rx_ctrl.size;
    uart_hdl->rx_ctrl.state = UART_STATE_READY;

    return LL_OK;
}

/**
  * @brief  Abort ongoing Transmit transfer for Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_AbortTransmit_IT(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->tx_ctrl.state != UART_STATE_BUSY_TX) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx state, can't abort Tx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check UART is in Tx IT state or not
    if (uart_hdl->tx_ctrl.isr == NULL) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Tx_IT state, can't abort it through IT interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check has Tx complete or not
    if (uart_hdl->tx_ctrl.isr == UART_TxDone_ISR) {
        LOG_E("This UART[0x%08" PRIx32 "] has Tx complete and now is waiting for Tx_Done interrupt flag, can't abort it!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //TxFIFO Empty Interrupt Disable
    __LL_UART_TxEmpty_INT_Dis(Instance);
    uart_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO
    __LL_UART_TxFIFO_Reset(Instance);

    //Set to complete
    uart_hdl->tx_ctrl.cnt = uart_hdl->tx_ctrl.size;
    uart_hdl->tx_ctrl.state = UART_STATE_READY;

    return LL_OK;
}

/**
  * @brief  Abort ongoing Receive transfer for Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_AbortReceive_IT(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_BUSY_RX) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx state, can't abort Rx!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Check UART is in Rx IT state or not
    if (uart_hdl->rx_ctrl.isr == NULL) {
        LOG_E("This UART[0x%08" PRIx32 "] isn't in Rx_IT state, can't abort it through IT interface!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //RxFIFO Full Interrupt Disable
    __LL_UART_RxFull_INT_Dis(Instance);
    uart_hdl->rx_ctrl.isr = NULL;

    //Rx Timeout Interrupt Disable
    if (__LL_UART_RxFIFOFullThres_Get(Instance) > 1) {
        __LL_UART_RxTimeout_INT_Dis(Instance);
    }

    //Clear RxFIFO
    __LL_UART_RxFIFO_Reset(Instance);

    //Check RxFIFO any error or not
    if (__LL_UART_IsRxFIFOErr(Instance)) {
        __LL_UART_RxFIFOErrIntPnd_Clr(Instance);
    }

    //Set to complete
    uart_hdl->rx_ctrl.cnt = uart_hdl->rx_ctrl.size;
    uart_hdl->rx_ctrl.state = UART_STATE_READY;

    return LL_OK;
}

/**
  * @brief  UART LL Tx Extend Address Config on runtime
  * @param  Instance Specifies UART peripheral
  * @param  tx_addr_ext tx extend address
  * @return LL Status
  */
LL_StatusETypeDef LL_Uart_TxExtAddrCfg(UART_TypeDef *Instance, uint8_t tx_addr_ext)
{
    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    if (!__LL_UART_IsExtBitEn(Instance)) {
        LOG_E("Extend Bit feature isn't Enable!\n");
        return LL_ERROR;
    }

    //Tx Extend Address Config
    __LL_UART_TxExtAddr_Set(Instance, tx_addr_ext);
    __LL_UART_TxExtMode_Set(Instance, UART_EXT_MODE_ADDR_MATCH);

    return LL_OK;
}

/**
  * @brief  UART LL RS485 Config
  * @param  Instance Specifies UART peripheral
  * @param  cfg RS485 config pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_RS485Cfg(UART_TypeDef *Instance, UART_Rs485CfgTypeDef *cfg)
{
    bool uart_en;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_UART_ALL_INSTANCE(Instance) || cfg == NULL) {
        return LL_INVALID;
    }

    //UART Enable state store and set UART Disable to config following params
    uart_en = __LL_UART_IsEn(Instance);
    __LL_UART_Dis(Instance);

    if (!cfg->enable) {
        __LL_UART_RS485_Dis(Instance);
        goto exit;
    }

    //RS485 Config
    __LL_UART_DE_Pol_Set(Instance, cfg->de_pol);
    __LL_UART_RE_Pol_Set(Instance, cfg->re_pol);
    __LL_UART_DE_AssertTime_Set(Instance, cfg->de_assert_time);
    __LL_UART_DE_DeAssertTime_Set(Instance, cfg->de_deassert_time);
    __LL_UART_DEtoRE_TurnAroundTime_Set(Instance, cfg->de2re_turn_ard_time);
    __LL_UART_REtoDE_TurnAroundTime_Set(Instance, cfg->re2de_turn_ard_time);

    //RS485 Enable
    __LL_UART_RS485_En(Instance);

exit:
    //Recover UART to Enable if need
    LL_FUNC_ALTER(uart_en, __LL_UART_En(Instance), (void)0U);

    return LL_OK;
}

/**
  * @brief  Update on the fly the receiver timeout value
  * @param  Instance UART peripheral
  * @param  TimeoutValue receiver timeout value in number of baud blocks. The timeout value must be less or equal to 0xFFFF
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_ReceiverTimeout_Config(UART_TypeDef *Instance, uint16_t TimeoutValue)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state == UART_STATE_RESET) {
        LOG_E("This UART[0x%08" PRIx32 "] Rx is in Reset state, can't config receiver timeout value!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Set Rx Timeout value
    __LL_UART_RxTimeoutTime_Set(Instance, TimeoutValue);

    return LL_OK;
}

/**
  * @brief  Enable the UART receiver timeout feature
  * @param  Instance UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_EnableReceiverTimeout(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't enable receiver timeout feature!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    __LL_UART_RxTimeout_En(Instance);

    return LL_OK;
}

/**
  * @brief  Disable the UART receiver timeout feature
  * @param  Instance UART peripheral
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_DisableReceiverTimeout(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if (uart_hdl->rx_ctrl.state != UART_STATE_READY) {
        LOG_E("This UART[0x%08" PRIx32 "] Rx isn't in Ready state, can't disable receiver timeout feature!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    __LL_UART_RxTimeout_Dis(Instance);

    return LL_OK;
}

/**
  * @brief  UART LL Auto Baud Rate Config
  * @note   (1) The actual timeout value maybe is 'timeout + 2' if timeout is effected.
  *         (2) This function can be used when Rx & Tx Idle only.
  * @param  Instance Specifies UART peripheral
  * @param  cfg Auto Baud Rate config pointer
  * @param  timeout Timeout for waitting detection
  * @return LL Status
  */
LL_StatusETypeDef LL_UART_AutoBaudRateCfg(UART_TypeDef *Instance, UART_AutoBaudCfgTypeDef *cfg, uint32_t timeout)
{
    UART_HandleTypeDef *uart_hdl;
    uint32_t pre_time, rem_time;
    volatile uint32_t use_time = 0;
    uint32_t baud_rate;
    uint8_t is_uart_en;
    uint8_t is_over_sample_x8;
    LL_StatusETypeDef err_status;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(cfg != NULL);

    if (!IS_UART_ALL_INSTANCE(Instance) || cfg == NULL || cfg->default_baud == 0) {
        return LL_INVALID;
    }

    if (cfg->detect_at_once && (timeout == 0)) {
        return LL_INVALID;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return LL_ERROR;
    } else if ((uart_hdl->rx_ctrl.state != UART_STATE_READY) || (uart_hdl->tx_ctrl.state != UART_STATE_READY)) {
        LOG_E("This UART[0x%08" PRIx32 "] Rx/Tx isn't in Ready state!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    uart_hdl->rx_ctrl.state = UART_STATE_BUSY;
    uart_hdl->tx_ctrl.state = UART_STATE_BUSY;

    baud_rate = __LL_UART_Baudrate_Read(Instance);
    is_uart_en = __LL_UART_IsEn(Instance); 

    //Baudrate check
    if (Instance == UART0 || Instance == UART1 || Instance == UART2) {
        baud_rate = (LL_RCU_APB0ClkGet() + cfg->default_baud / 2) / cfg->default_baud;
    } else if (Instance == UART3 || Instance == UART4) {
        baud_rate = (LL_RCU_APB1ClkGet() + cfg->default_baud / 2) / cfg->default_baud;
    } else {
        err_status = LL_INVALID;
        goto ABNORMAL_EXIT;
    }

    if (baud_rate == 0) {
        err_status = LL_INVALID;
        goto ABNORMAL_EXIT;
    }

    if (((!is_uart_en) && (cfg->detect_at_once))) {
        err_status = LL_ERROR;
        goto ABNORMAL_EXIT;
    }

    if (cfg->over_samp_refresh == false) {
        is_over_sample_x8 = __LL_UART_IsOverSampleX8(Instance);

        if (is_over_sample_x8) {
            if (baud_rate < 0x8) {
                LOG_E("BAUD value is too small when OverSample is 8X \n");
                err_status = LL_INVALID;
                goto ABNORMAL_EXIT;
            }
        } else {
            if (baud_rate < 0x10) {
                LOG_E("BAUD value is too small when OverSample is 16X \n");
                err_status = LL_INVALID;
                goto ABNORMAL_EXIT;
            }            
        }

    } else {
        if (cfg->over_samp_reload == UART_OVER_SAMP_16X) {
            if (baud_rate < 0x10) {
                LOG_E("BAUD value is too small for UART_OVER_SAMP_16X \n");
                err_status = LL_INVALID;
                goto ABNORMAL_EXIT;
            }   

            __LL_UART_Dis(Instance); 
            __LL_UART_OverSampleMode_Set(Instance, cfg->over_samp_reload);
        } else if (cfg->over_samp_reload == UART_OVER_SAMP_8X) {
            if (baud_rate < 0x8) {
                LOG_E("BAUD value is too small for UART_OVER_SAMP_8X \n");
                err_status = LL_INVALID;
                goto ABNORMAL_EXIT;
            }

            __LL_UART_Dis(Instance); 
            __LL_UART_OverSampleMode_Set(Instance, cfg->over_samp_reload);
        } else {
            err_status = LL_INVALID;
            goto ABNORMAL_EXIT;
        }
    }

    __LL_UART_Dis(Instance); 
    __LL_UART_Baudrate_Set(Instance, baud_rate);
    LL_FUNC_ALTER(is_uart_en, __LL_UART_En(Instance), __LL_UART_Dis(Instance));

    //Set Auto-baudrate Mode
    __LL_UART_AutoBaudRateMode_Set(Instance, cfg->mode);

    //Detect baud rate at once
    if (!cfg->detect_at_once) {
        goto NORMAL_END;
    }

    pre_time = LL_GetTick();

    while (__LL_UART_IsAutoBaudRateEn(Instance)) {
        use_time = LL_GetTick() - pre_time;
        if (use_time > timeout) {
            err_status = LL_TIMEOUT;
            goto ABNORMAL_EXIT;
        }
    }

    //Start once detect
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_RxFIFO_Reset(Instance);
    __LL_UART_AutoBaudRate_En(Instance);

    rem_time = (timeout > use_time) ? (timeout - use_time) : 2;
    pre_time = LL_GetTick();

    while (__LL_UART_IsAutoBaudRateEn(Instance)) {
        use_time = LL_GetTick() - pre_time;
        if (use_time > rem_time) {
            err_status = LL_TIMEOUT;
            goto ABNORMAL_EXIT;
        }
    }

NORMAL_END:
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_RxFIFO_Reset(Instance);
    uart_hdl->rx_ctrl.state = UART_STATE_READY;
    uart_hdl->tx_ctrl.state = UART_STATE_READY;
    return LL_OK;

ABNORMAL_EXIT:
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_RxFIFO_Reset(Instance);
    uart_hdl->rx_ctrl.state = UART_STATE_READY;
    uart_hdl->tx_ctrl.state = UART_STATE_READY;
    return err_status;
}

/**
  * @brief  UART LL Handle Get
  * @param  Instance Specifies UART peripheral
  * @return UART_HandleTypeDef pointer
  */
UART_HandleTypeDef *LL_UART_Handle_Get(UART_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return NULL;
    }

    return UART_Handle_Get(Instance);
}

/**
  * @}
  */


/** @defgroup UART_LL_Exported_Functions_Interrupt UART Interrupt Handler and Callback
  * @brief    UART Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  UART LL IRQ Handler
  * @param  Instance UART peripheral
  * @return None
  */
void LL_UART_IRQHandler(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (!IS_UART_ALL_INSTANCE(Instance)) {
        return;
    }

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_UART_AllIntEn_Get(Instance);
    int_pending = __LL_UART_AllIntPnd_Get(Instance);


    //Rx Address Match Interrupt Handler
    if ((int_en & UART0_INTEN_AMIE_Msk) && (int_pending & UART0_INT_AMIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxAddrMatchIntPnd_Clr(Instance);

        //Callback
        LL_UART_RxAddrMatchCallback(Instance);
    }

    //Tx Idle Done Interrupt Handler
    if ((int_en & UART0_INTEN_IDLE_Msk) && (int_pending & UART0_INT_IDLF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_TxIdleDoneIntPnd_Clr(Instance);

        //Callback
        LL_UART_TxIdleDoneCallback(Instance);
    }

    //Tx Break Done Interrupt Handler
    if ((int_en & UART0_INTEN_TBIE_Msk) && (int_pending & UART0_INT_TBIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_TxBreakDoneIntPnd_Clr(Instance);

        //Callback
        LL_UART_TxBreakDoneCallback(Instance);
    }

    //Tx Done Interrupt Handler
    if ((int_en & UART0_INTEN_TDIE_Msk) && (int_pending & UART0_INT_TDIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_TxDoneIntPnd_Clr(Instance);

        if (uart_hdl->tx_ctrl.cnt >= uart_hdl->tx_ctrl.size && uart_hdl->tx_ctrl.isr) {
            uart_hdl->tx_ctrl.isr(Instance);
        }

        //Callback
        LL_UART_TxDoneCallback(Instance);
    }

    //Rx Timeout Interrupt Handler
    if ((int_en & UART0_INTEN_RTIE_Msk) && (int_pending & UART0_INT_RTOI_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxTimeoutIntPnd_Clr(Instance);

        if (__LL_UART_RxFIFOFullThres_Get(Instance) > 1) {
            UART_RxTimeout_ISR(Instance);
        }

        //Callback
        LL_UART_RxTimeoutCallback(Instance);
    }

    //Rx Break Interrupt Handler
    if ((int_en & UART0_INTEN_BKIE_Msk) && (int_pending & UART0_INT_BKIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxBreakIntPnd_Clr(Instance);

        //Callback
        LL_UART_RxBreakCallback(Instance);
    }

    //Frame Error Interrupt Handler
    if ((int_en & UART0_INTEN_FEIE_Msk) && (int_pending & UART0_INT_FEIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_FrameErrIntPnd_Clr(Instance);

        //Callback
        LL_UART_FrameErrCallback(Instance);
    }

    //Parity Error Interrupt Handler
    if ((int_en & UART0_INTEN_PEIE_Msk) && (int_pending & UART0_INT_PEIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_ParityErrIntPnd_Clr(Instance);

        //Callback
        LL_UART_ParityErrCallback(Instance);
    }

    //Tx Overflow Interrupt Handler
    if ((int_en & UART0_INTEN_TOIE_Msk) && (int_pending & UART0_INT_TOIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_TxFIFOOverFlowIntPnd_Clr(Instance);

        //Callback
        LL_UART_TxFIFOOverFlowCallback(Instance);
    }

    //Rx Underflow Interrupt Handler
    if ((int_en & UART0_INTEN_RUIE_Msk) && (int_pending & UART0_INT_RUIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxFIFOUnderFlowIntPnd_Clr(Instance);

        //Callback
        LL_UART_RxFIFOUnderFlowCallback(Instance);
    }

    //Rx Overflow Interrupt Handler
    if ((int_en & UART0_INTEN_ROIE_Msk) && (int_pending & UART0_INT_ROIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxFIFOOverFlowIntPnd_Clr(Instance);

        //Callback
        LL_UART_RxFIFOOverFlowCallback(Instance);
    }

    //Tx Empty Interrupt Handler
    if ((int_en & UART0_INTEN_TEIE_Msk) && (int_pending & UART0_INT_TXEI_Msk)) {
        //interrupt pending auto clear

        //Callback
        if (uart_hdl->tx_ctrl.isr) {
            uart_hdl->tx_ctrl.isr(Instance);
        }

        LL_UART_TxFIFOEmptyCallback(Instance);
    }

    //Rx Full Interrupt Handler
    if ((int_en & UART0_INTEN_RFIE_Msk) && (int_pending & UART0_INT_RXFI_Msk)) {
        //interrupt pending auto clear

        //Callback
        if (uart_hdl->rx_ctrl.isr) {
            uart_hdl->rx_ctrl.isr(Instance);
        }

        LL_UART_RxFIFOFullCallback(Instance);
    }

    //The following features are available for later versions
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        return;
    }

    //Rx Idle Interrupt Handler
    if ((int_en & UART0_INTEN_IDIE_Msk) && (int_pending & UART0_INT_IDIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_RxIdleIntPnd_Clr(Instance);

        //Callback
        LL_UART_RxIdleDoneCallback(Instance);
    }   

    //Noise Detection Interrupt Handler
    if ((int_en & UART0_INTEN_NOIE_Msk) && (int_pending & UART0_INT_NOIF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_NoiseDetectIntPnd_Clr(Instance);

        //Callback
        LL_UART_NoiseDetectCallback(Instance);
    }   

    //Auto Baud Rate Error Interrupt Handler
    if ((int_en & UART0_INTEN_ABRE_Msk) && (int_pending & UART0_INT_ABRF_Msk)) {
        //Interrupt Pending Clear
        __LL_UART_AutoBaudRateErrIntPnd_Clr(Instance);

        //Callback
        LL_UART_AutoBaudRateErrCallback(Instance);
    }   
}

/**
  * @brief  UART LL Auto Baud Rate Error Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_AutoBaudRateErrCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_AutoBaudRateErrCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Rx Address Match Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxAddrMatchCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxAddrMatchCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Tx Idle Done Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxIdleDoneCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxIdleDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Tx Break Done Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxBreakDoneCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxBreakDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL TX Done Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxDoneCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL RX Timeout Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxTimeoutCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Rx Break Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxBreakCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxBreakCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Frame Error Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_FrameErrCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_FrameErrCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Parity Error Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_ParityErrCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_ParityErrCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Noise Detection Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_NoiseDetectCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_NoiseDetectCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Rx Idle Done Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxIdleDoneCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxIdleDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL TxFIFO OverFlow Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxFIFOOverFlowCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxFIFOOverFlowCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL RxFIFO UnderFlow Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxFIFOUnderFlowCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxFIFOUnderFlowCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL RxFIFO OverFlow Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxFIFOOverFlowCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxFIFOOverFlowCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL TxFIFO Empty Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxFIFOEmptyCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxFIFOEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL RxFIFO Full Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxFIFOFullCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxFIFOFullCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @defgroup UART_LL_Private_Functions UART LL Private function
  * @brief    UART LL Private function
  * @{
  */

/**
  * @brief  UART Handle Get
  * @param  Instance Specifies UART peripheral
  * @return UART_HandleTypeDef pointer
  */
static UART_HandleTypeDef *UART_Handle_Get(UART_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (Instance == UART0) {
        return &uart_hdl_global[UART_INSTANCE_0];
    } else if (Instance == UART1) {
        return &uart_hdl_global[UART_INSTANCE_1];
    } else if (Instance == UART2) {
        return &uart_hdl_global[UART_INSTANCE_2];
    } else if (Instance == UART3) {
        return &uart_hdl_global[UART_INSTANCE_3];
    } else if (Instance == UART4) {
        return &uart_hdl_global[UART_INSTANCE_4];
    }

    return NULL;
}

/**
  * @brief  UART TxDone Interrupt Service Routine
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_TxDone_ISR(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    if (uart_hdl->tx_ctrl.cnt >= uart_hdl->tx_ctrl.size) {
        //Disable Tx Done Interrupt
        __LL_UART_TxDone_INT_Dis(Instance);
        uart_hdl->tx_ctrl.isr = NULL;
        uart_hdl->tx_ctrl.state = UART_STATE_READY;

        //Tx Complete Callback
        if (uart_hdl->user_callback.TxCpltCallback) {
            uart_hdl->user_callback.TxCpltCallback();
        }
    }
}

/**
  * @brief  UART RxTimeout Interrupt Service Routine
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_RxTimeout_ISR(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    if (uart_hdl->rx_ctrl.state == UART_STATE_BUSY_RX) {    //In Rx Status
        //Check is Interrupt Receive mode not, only handle Rx_IT mode, not handle Rx_CPU/Rx_DMA mode
        if (uart_hdl->rx_ctrl.isr == NULL) {
            return;
        }

        //Check buffer pointer to be valid, Check has received complete or not
        if (uart_hdl->rx_ctrl.buf == NULL || uart_hdl->rx_ctrl.cnt >= uart_hdl->rx_ctrl.size) {
            //Clear RxFIFO
            __LL_UART_RxFIFO_Reset(Instance);
            return;
        }

        //Check Rx Error or not
        if (__LL_UART_IsRxFIFOErr(Instance)) {
            LOG_E("<%s> error!\n", __FUNCTION__);

            //RxFIFO Full Interrupt Disable
            __LL_UART_RxFull_INT_Dis(Instance);
            uart_hdl->rx_ctrl.isr = NULL;
            uart_hdl->rx_ctrl.state = UART_STATE_READY;

            //Error Callback
            if (uart_hdl->user_callback.ErrorCallback) {
                uart_hdl->user_callback.ErrorCallback();
            }

            return;
        }

        //Get RxFIFO level and Rx 9Bits Enable status
        uint8_t rx_fifo_lvl = __LL_UART_RxFIFOLvl_Get(Instance);
        bool rx_9bits_en = (bool)(__LL_UART_IsExtBitEn(Instance) && !__LL_UART_IsRxExtAddrMatchMode(Instance) &&
                                  (UART_DatLenETypeDef)__LL_UART_DatLen_Get(Instance) >= UART_DAT_LEN_8b);

        //Read remain data from RxFIFO until receive enough data
        if (rx_9bits_en) {
            while (rx_fifo_lvl-- && uart_hdl->rx_ctrl.cnt < uart_hdl->rx_ctrl.size) {
                *(uint16_t *)uart_hdl->rx_ctrl.buf = (uint16_t)(__LL_UART_RxDat9bits_Read(Instance));
                uart_hdl->rx_ctrl.buf += 2;
                uart_hdl->rx_ctrl.cnt++;
            }
        } else {
            while (rx_fifo_lvl-- && uart_hdl->rx_ctrl.cnt < uart_hdl->rx_ctrl.size) {
                *uart_hdl->rx_ctrl.buf = (uint8_t)__LL_UART_RxDat8bits_Read(Instance);
                uart_hdl->rx_ctrl.buf++;
                uart_hdl->rx_ctrl.cnt++;
            }
        }

        //RxFIFO Full Interrupt Disable
        __LL_UART_RxFull_INT_Dis(Instance);
        uart_hdl->rx_ctrl.isr = NULL;
        uart_hdl->rx_ctrl.state = UART_STATE_READY;

        //Complete or Error Callback
        if (uart_hdl->rx_ctrl.cnt >= uart_hdl->rx_ctrl.size) {
            //Rx Complete Callback
            if (uart_hdl->user_callback.RxCpltCallback) {
                uart_hdl->user_callback.RxCpltCallback();
            }
        } else {
            //Error Callback
            if (uart_hdl->user_callback.ErrorCallback) {
                uart_hdl->user_callback.ErrorCallback();
            }
        }

        //Rx Timeout Interrupt Disable
        __LL_UART_RxTimeout_INT_Dis(Instance);

    } else {                                                //Not in Rx Status

        //Clear RxFIFO
        __LL_UART_RxFIFO_Reset(Instance);
    }
}

/**
  * @brief  UART write 8bit data handle in Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_TxISR_8BIT(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Write data to TxFIFO
    if (!__LL_UART_IsTxFIFOFull(Instance) && uart_hdl->tx_ctrl.cnt < uart_hdl->tx_ctrl.size) {
        //if TxDone flag has been set before write data to TxFIFO, clear it
        if (__LL_UART_IsTxDoneIntPnd(Instance)) {
            __LL_UART_TxDoneIntPnd_Clr(Instance);
        }

        __LL_UART_TxDat8bits_Write(Instance, *uart_hdl->tx_ctrl.buf);
        uart_hdl->tx_ctrl.buf++;
        uart_hdl->tx_ctrl.cnt++;
    }

    //Write Complete
    if (uart_hdl->tx_ctrl.cnt >= uart_hdl->tx_ctrl.size) {
        //TxFIFO Empty Interrupt Disable
        __LL_UART_TxEmpty_INT_Dis(Instance);

        //Switch isr to TxDone ISR
        uart_hdl->tx_ctrl.isr = UART_TxDone_ISR;

        //Enable Tx Done Interrupt
        __LL_UART_TxDone_INT_En(Instance);
    }
}

/**
  * @brief  UART write 16bit data handle in Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_TxISR_16BIT(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Write data to TxFIFO
    if (!__LL_UART_IsTxFIFOFull(Instance) && uart_hdl->tx_ctrl.cnt < uart_hdl->tx_ctrl.size) {
        //if TxDone flag has been set before write data to TxFIFO, clear it
        if (__LL_UART_IsTxDoneIntPnd(Instance)) {
            __LL_UART_TxDoneIntPnd_Clr(Instance);
        }

        __LL_UART_TxDat9bits_Write(Instance, *(uint16_t *)uart_hdl->tx_ctrl.buf);
        uart_hdl->tx_ctrl.buf += 2;
        uart_hdl->tx_ctrl.cnt++;
    }

    //Write Complete
    if (uart_hdl->tx_ctrl.cnt >= uart_hdl->tx_ctrl.size) {
        //TxFIFO Empty Interrupt Disable
        __LL_UART_TxEmpty_INT_Dis(Instance);

        //Switch isr to TxDone ISR
        uart_hdl->tx_ctrl.isr = UART_TxDone_ISR;

        //Enable Tx Done Interrupt
        __LL_UART_TxDone_INT_En(Instance);
    }
}

/**
  * @brief  UART read 8bit data handle in Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_RxISR_8BIT(UART_TypeDef *Instance)
{
    uint8_t rx_fifo_trig_lvl;
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    rx_fifo_trig_lvl = __LL_UART_RxFIFOFullThres_Get(Instance);

    //Receive data from RxFIFO
    while (rx_fifo_trig_lvl-- && uart_hdl->rx_ctrl.cnt < uart_hdl->rx_ctrl.size) {
        //Rx Error
        if (__LL_UART_IsRxFIFOErr(Instance)) {
            LOG_E("<%s> error!\n", __FUNCTION__);

            //RxFIFO Full Interrupt Disable
            __LL_UART_RxFull_INT_Dis(Instance);
            uart_hdl->rx_ctrl.isr = NULL;
            uart_hdl->rx_ctrl.state = UART_STATE_READY;

            //Error Callback
            if (uart_hdl->user_callback.ErrorCallback) {
                uart_hdl->user_callback.ErrorCallback();
            }

            return;
        }

        *uart_hdl->rx_ctrl.buf = (uint8_t)__LL_UART_RxDat8bits_Read(Instance);
        uart_hdl->rx_ctrl.buf++;
        uart_hdl->rx_ctrl.cnt++;
    }

    //Read Complete
    if (uart_hdl->rx_ctrl.cnt >= uart_hdl->rx_ctrl.size) {
        //RxFIFO Full Interrupt Disable
        __LL_UART_RxFull_INT_Dis(Instance);
        uart_hdl->rx_ctrl.isr = NULL;
        uart_hdl->rx_ctrl.state = UART_STATE_READY;

        //Rx Complete Callback
        if (uart_hdl->user_callback.RxCpltCallback) {
            uart_hdl->user_callback.RxCpltCallback();
        }
    }
}

/**
  * @brief  UART read 16bit data handle in Interrupt mode
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_RxISR_16BIT(UART_TypeDef *Instance)
{
    uint8_t rx_fifo_trig_lvl;
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    rx_fifo_trig_lvl = __LL_UART_RxFIFOFullThres_Get(Instance);

    //Receive data from RxFIFO
    while (rx_fifo_trig_lvl-- && uart_hdl->rx_ctrl.cnt < uart_hdl->rx_ctrl.size) {
        //Rx Error
        if (__LL_UART_IsRxFIFOErr(Instance)) {
            LOG_E("<%s> error!\n", __FUNCTION__);

            //RxFIFO Full Interrupt Disable
            __LL_UART_RxFull_INT_Dis(Instance);
            uart_hdl->rx_ctrl.isr = NULL;
            uart_hdl->rx_ctrl.state = UART_STATE_READY;

            //Error Callback
            if (uart_hdl->user_callback.ErrorCallback) {
                uart_hdl->user_callback.ErrorCallback();
            }

            return;
        }

        *(uint16_t *)uart_hdl->rx_ctrl.buf = (uint16_t)(__LL_UART_RxDat9bits_Read(Instance));
        uart_hdl->rx_ctrl.buf += 2;
        uart_hdl->rx_ctrl.cnt++;
    }

    //Read Complete
    if (uart_hdl->rx_ctrl.cnt >= uart_hdl->rx_ctrl.size) {
        //RxFIFO Full Interrupt Disable
        __LL_UART_RxFull_INT_Dis(Instance);
        uart_hdl->rx_ctrl.isr = NULL;
        uart_hdl->rx_ctrl.state = UART_STATE_READY;

        //Rx Complete Callback
        if (uart_hdl->user_callback.RxCpltCallback) {
            uart_hdl->user_callback.RxCpltCallback();
        }
    }
}


#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  UART LL DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @return DMA_ChannelETypeDef
  */
static DMA_ChannelETypeDef UART_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
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
  * @brief  UART LL DMA DeInit
  * @param  ch DMA channel to DeInit
  * @return None
  */
static void UART_DMA_DeInit(DMA_ChannelETypeDef ch)
{
    if (ch == DMA_CHANNEL_INVALID) {
        return;
    }

    LL_DMA_Stop_IT(DMA, ch);
    LL_DMA_DeInit(DMA, ch);
    LL_DMA_ChannelRelease(ch);
}

/**
  * @brief  DMA UART transmit process complete callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMATransmitCplt(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_UART_TxDMA_Dis(Instance);

    //DMA DeInit
    UART_DMA_DeInit(uart_hdl->tx_ctrl.dma_ch);
    uart_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->tx_ctrl.cnt = uart_hdl->tx_ctrl.size;

    //Switch isr to TxDone ISR
    uart_hdl->tx_ctrl.isr = UART_TxDone_ISR;

    //Enable Tx Done Interrupt
    __LL_UART_TxDone_INT_En(Instance);
}

/**
  * @brief  DMA UART receive process complete callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMAReceiveCplt(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_UART_RxDMA_Dis(Instance);

    //DMA DeInit
    UART_DMA_DeInit(uart_hdl->rx_ctrl.dma_ch);
    uart_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    uart_hdl->rx_ctrl.cnt = uart_hdl->rx_ctrl.size;
    uart_hdl->rx_ctrl.state = UART_STATE_READY;

    //Rx Complete Callback
    if (uart_hdl->user_callback.RxCpltCallback) {
        uart_hdl->user_callback.RxCpltCallback();
    }
}

/**
  * @brief  DMA UART transmit process half complete callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMAHalfTransmitCplt(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Tx Half Complete Callback
    if (uart_hdl->user_callback.TxHalfCpltCallback) {
        uart_hdl->user_callback.TxHalfCpltCallback();
    }
}

/**
  * @brief  DMA UART receive process half complete callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMAHalfReceiveCplt(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Rx Half Complete Callback
    if (uart_hdl->user_callback.RxHalfCpltCallback) {
        uart_hdl->user_callback.RxHalfCpltCallback();
    }
}

/**
  * @brief  DMA UART transmit process error callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMATransmitError(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_UART_TxDMA_Dis(Instance);

    //DMA DeInit
    UART_DMA_DeInit(uart_hdl->tx_ctrl.dma_ch);

    uart_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->tx_ctrl.state = UART_STATE_READY;

    if (uart_hdl->user_callback.ErrorCallback) {
        uart_hdl->user_callback.ErrorCallback();
    }
}

/**
  * @brief  DMA UART receive process error callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
static void UART_DMAReceiveError(UART_TypeDef *Instance)
{
    UART_HandleTypeDef *uart_hdl;

    //UART handle get
    uart_hdl = UART_Handle_Get(Instance);

    if (uart_hdl == NULL) {
        LOG_E("Get UART handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_UART_RxDMA_Dis(Instance);

    //DMA DeInit
    UART_DMA_DeInit(uart_hdl->rx_ctrl.dma_ch);

    uart_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    uart_hdl->rx_ctrl.state = UART_STATE_READY;

    if (uart_hdl->user_callback.ErrorCallback) {
        uart_hdl->user_callback.ErrorCallback();
    }
}

#endif

/**
  * @}
  */


#endif  /* LL_UART_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

