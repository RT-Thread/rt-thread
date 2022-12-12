/**
  ******************************************************************************
  * @file    tae32f53xx_ll_uart.c
  * @author  MCD Application Team
  * @brief   UART LL Module Driver.
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


#define DBG_TAG             "UART"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup UART_LL UART LL
  * @brief    UART LL module driver.
  * @{
  */

#ifdef LL_UART_MODULE_ENABLED

/* Private variables ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** @defgroup UART_LL_Private_Macros UART LL Private Macros
  * @brief    UART LL Private Macros
  * @{
  */

/**
  * @brief  UART Function Alternative
  * @param  flag Condition Flag
  * @param  func_t True Funciton
  * @param  func_f False Function
  * @return None
  */
#define UART_FUNC_ALTER(flag, func_t, func_f)   \
        do{                                     \
            if((flag)) {                        \
                func_t;                         \
            } else {                            \
                func_f;                         \
            }                                   \
        } while(0)

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @addtogroup UART_LL_Exported_Functions UART LL Exported Functions
  * @brief    UART LL Exported Functions
  * @{
  */
#ifdef LL_DMA_MODULE_ENABLED

    DMA_ChannelETypeDef LL_UART_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    LL_StatusETypeDef LL_UART_DMA_Deinit(DMA_ChannelETypeDef ch);
    void LL_UART_DMA_TXCHEndCallback(void *arg);
    void LL_UART_DMA_RXCHEndCallback(void *arg);
    void LL_UART_DMA_TXCHErrorCallBck(void *arg);
    void LL_UART_DMA_RXCHErrorCallBck(void *arg);

#endif  /*!< LL_DMA_MODULE_ENABLED */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup UART_LL_Exported_Functions UART LL Exported Functions
  * @brief    UART LL Exported Functions
  * @{
  */

/** @defgroup UART_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  UART LL init
  * @param  Instance Specifies UART peripheral
  * @param  Init init pointer
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Init(UART_TypeDef *Instance, UART_InitTypeDef *Init)
{
    uint32_t baud_rate;

    /* Init the low level hardware eg. Clock, NVIC */
    LL_UART_MspInit(Instance);

    //Parity config
    if (Init->parity == UART_PARITY_NO) {
        __LL_UART_Parity_Dis(Instance);
    } else {
        __LL_UART_Parity_En(Instance);
        UART_FUNC_ALTER(Init->parity == UART_PARITY_ODD, __LL_UART_EvenParity_Clr(Instance), __LL_UART_EvenParity_Set(Instance));
    }

    //Stop bit config
    UART_FUNC_ALTER(Init->stop_len == UART_STOP_LEN_1b, __LL_UART_Stop1Bit_Set(Instance), __LL_UART_Stop2bits_Set(Instance));

    //Data length config
    if (Init->dat_len == UART_DAT_LEN_9b) {
        __LL_UART_DatLen9bitsExt_En(Instance);
        __LL_UART_RAR_Set(Instance, Init->U9BRxAddress);

        if (Init->U9BAddrMatchMode_Enable == ENABLE) {
            __LL_UART_AddrMatchMode_En(Instance);
            __LL_UART_TxMode8bits_Set(Instance);
        } else {
            __LL_UART_AddrMatchMode_Dis(Instance);
            __LL_UART_TxMode9bits_Set(Instance);
        }
    } else {
        __LL_UART_DatLen9bitsExt_Dis(Instance);
        __LL_UART_DatLen_Sel(Instance, (uint8_t)Init->dat_len);
    }

    //FIFO config, FCR register can write only
    __LL_UART_FCR_Write(Instance, Init->rx_tl | Init->tx_tl | UART_FCR_XFIFOR_Msk | UART_FCR_RFIFOR_Msk | UART_FCR_FIFOE_Msk);

    //Baudrate config
    __LL_UART_DivLatchAccess_Set(Instance);

    baud_rate = (LL_SYSCTRL_APB0ClkGet() + Init->baudrate / 2) / Init->baudrate;
    __LL_UART_DivLatchLow_Write(Instance, (uint8_t)(baud_rate >> 4));
    __LL_UART_DivLatchHigh_Write(Instance, (uint8_t)(baud_rate >> 12));
    __LL_UART_DivLatchFrac_Set(Instance, (baud_rate & 0xFUL));

    __LL_UART_DivLatchAccess_Clr(Instance);

    return LL_OK;
}

/**
  * @brief  UART LL deinit
  * @param  Instance Specifies UART peripheral
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_DeInit(UART_TypeDef *Instance)
{
    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_UART_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the UART MSP.
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
  * @}
  */


/** @defgroup UART_LL_Exported_Functions_Group2 UART Transmit and Recieve Function
  * @brief    UART Transmit Function
  * @{
  */

/**
  * @brief Send an amount of data in blocking mode.
  * @note   When UART parity is not enabled, and Word Length is configured to 9 bits,
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pData.
  * @param  Instance Specifies UART peripheral
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size Amount of data elements (u8 or u16) to be sent.
  * @param  Timeout Timeout duration.
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Transmit_CPU(UART_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint8_t  *pdata8bits;
    uint16_t *pdata16bits;
    uint32_t tickstart;
    uint32_t TxXferCount = Size;

    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    /* In case of 9bits, pRxData needs to be handled as a uint16_t pointer */
    if (__LL_UART_IsDatLen9bitsEn(Instance) && __LL_UART_TxModeSta_Get(Instance)) {
        pdata8bits  = NULL;
        pdata16bits = (uint16_t *) pData;
    } else {
        pdata8bits  = pData;
        pdata16bits = NULL;
    }

    //Transmit data loop
    while (TxXferCount) {
        //Wait TxFIFO to be not full
        tickstart = LL_GetTick();

        while (!__LL_UART_IsTxFIFONotFull(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        if (pdata16bits) {
            __LL_UART_TxBuf9bits_Write(Instance, *pdata16bits++);
        } else {
            __LL_UART_TxBuf8bits_Write(Instance, *pdata8bits++);
        }

        /* Wait for UART Transmit completed */
        while (!__LL_UART_IsTxEmpty(Instance));

        TxXferCount--;
    }

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @note   When UART parity is not enabled, and Word Length is configured to 9 bits ,
  *         the received data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 available through pData.
  * @param  Instance Specifies UART peripheral
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size Amount of data elements (u8 or u16) to be received.
  * @param  Timeout Timeout duration.
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Receive_CPU(UART_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    uint8_t  *pdata8bits;
    uint16_t *pdata16bits;
    uint32_t tickstart;
    uint32_t RxXferCount = Size;

    //Check the UART initiation struct allocation
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    //In case of 9bits, pRxData needs to be handled as a uint16_t pointer
    if (__LL_UART_IsDatLen9bitsEn(Instance)) {
        pdata8bits  = NULL;
        pdata16bits = (uint16_t *) pData;
    } else {
        pdata8bits  = pData;
        pdata16bits = NULL;
    }

    //Receive data loop
    while (RxXferCount) {
        //Wait RxFIFO to be not empty
        tickstart = LL_GetTick();

        while (!__LL_UART_IsRxFIFONotEmpty(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        //Read data from RxFIFO
        if (pdata16bits) {
            *pdata16bits++ = (uint16_t)(__LL_UART_RxBuf9bits_Read(Instance));
        } else {
            *pdata8bits++ = (uint8_t)(__LL_UART_RxBuf8bits_Read(Instance));
        }

        RxXferCount--;
    }

    return LL_OK;
}

/**
  * @brief  Send an amount of data in interrupt mode.
  * @param  Instance Specifies UART peripheral
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Transmit_IT(UART_TypeDef *Instance)
{
    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    /* Enable Transmit Holding Register Empty Interrupt */
    __LL_UART_TxHoldEmpyt_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  Instance Specifies UART peripheral
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Receive_IT(UART_TypeDef *Instance)
{
    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    /* RX data available interrupt */
    __LL_UART_RxDatAvl_INT_En(Instance);

    return LL_OK;
}

#ifdef LL_DMA_MODULE_ENABLED
/**
  * @brief  UART LL Transmit by DMA
  * @param  Instance Specifies UART peripheral
  * @param  dma_user_cfg user dma config pointer
  * @param  huart uart transmit by DMA handle pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Transmit_DMA(UART_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                       UART_DMAHandleTypeDef *huart, uint32_t Timeout)
{
    uint8_t  *pdata8bits;
    uint16_t *pdata16bits;
    huart->dma_tx_ch = DMA_CHANNEL_INVALID;
    uint32_t tickstart;

    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if ((huart->buf == NULL) || (huart->buf_len == 0U)) {
        return LL_ERROR;
    }

    //In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer
    if (__LL_UART_IsDatLen9bitsEn(Instance) && __LL_UART_TxModeSta_Get(Instance)) {
        pdata8bits  = NULL;
        pdata16bits = (uint16_t *) huart->buf;
    } else {
        pdata8bits  = huart->buf;
        pdata16bits = NULL;
    }

    if (pdata16bits) {
        dma_user_cfg->dst_data_width  = DMA_DST_TRANS_WIDTH_16b;
    } else {
        dma_user_cfg->dst_data_width  = DMA_DST_TRANS_WIDTH_8b;
    }

    huart->Instance = Instance;
    huart->TXdma_status = UART_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)huart;
    dma_user_cfg->end_callback = LL_UART_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)huart;
    dma_user_cfg->err_callback = LL_UART_DMA_TXCHErrorCallBck;

    tickstart = LL_GetTick();

    while (huart->dma_tx_ch == DMA_CHANNEL_INVALID) {
        huart->dma_tx_ch = LL_UART_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    huart->TXdma_status = UART_DMA_STATE_READY;

    if (pdata16bits) {
        LL_DMA_Start_IT(DMA, huart->dma_tx_ch, (uint32_t)pdata16bits, (uint32_t)&Instance->THR, huart->buf_len);
    } else {
        LL_DMA_Start_IT(DMA, huart->dma_tx_ch, (uint32_t)pdata8bits, (uint32_t)&Instance->THR, huart->buf_len);
    }

    huart->TXdma_status = UART_DMA_STATE_BUSY;

    return LL_OK;
}

/**
  * @brief  UART LL Receive through DMA
  * @param  Instance Specifies UART peripheral
  * @param  huart uart transmit by DMA handle pointer
  * @param  dma_user_cfg user dma config pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_Receive_DMA(UART_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                      UART_DMAHandleTypeDef *huart, uint32_t Timeout)
{
    uint8_t  *pdata8bits;
    uint16_t *pdata16bits;
    huart->dma_rx_ch = DMA_CHANNEL_INVALID;
    uint32_t tickstart;

    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if ((huart->buf == NULL) || (huart->buf_len == 0U)) {
        return LL_ERROR;
    }

    //In case of 9bits/No Parity transfer, pRxData needs to be handled as a uint16_t pointer
    if (__LL_UART_IsDatLen9bitsEn(Instance)) {
        pdata8bits  = NULL;
        pdata16bits = (uint16_t *) huart->buf;
    } else {
        pdata8bits  = huart->buf;
        pdata16bits = NULL;
    }

    if (pdata16bits) {
        dma_user_cfg->src_data_width  = DMA_SRC_TRANS_WIDTH_16b;
    } else {
        dma_user_cfg->src_data_width  = DMA_SRC_TRANS_WIDTH_8b;
    }

    huart->Instance = Instance;
    huart->RXdma_status = UART_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)huart;
    dma_user_cfg->end_callback = LL_UART_DMA_RXCHEndCallback;
    dma_user_cfg->err_arg = (void *)huart;
    dma_user_cfg->err_callback = LL_UART_DMA_RXCHErrorCallBck;

    tickstart = LL_GetTick();

    while (huart->dma_rx_ch == DMA_CHANNEL_INVALID) {
        huart->dma_rx_ch = LL_UART_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    huart->RXdma_status = UART_DMA_STATE_READY;

    if (pdata16bits) {
        LL_DMA_Start_IT(DMA, huart->dma_rx_ch, (uint32_t)&Instance->RBR, (uint32_t)pdata16bits, huart->buf_len);
    } else {
        LL_DMA_Start_IT(DMA, huart->dma_rx_ch, (uint32_t)&Instance->RBR, (uint32_t)pdata8bits, huart->buf_len);
    }

    huart->RXdma_status = UART_DMA_STATE_BUSY;

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
  * @brief  UART LL 9BIT Transmit Addr Send
  * @param  Instance Specifies UART peripheral
  * @param  TxAddr 9BIT Transmit Addr Send
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_Uart_9bit_SendAddress(UART_TypeDef *Instance, uint8_t TxAddr)
{
    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    if (__LL_UART_IsDatLen9bitsEn(Instance)) {
        if (!(__LL_UART_TxModeSta_Get(Instance))) {
            /* Transmit Address set */
            __LL_UART_TAR_Set(Instance, TxAddr);
            /* Send address */
            __LL_UART_SendAddr_Start(Instance);
            return LL_OK;
        } else {
            __LL_UART_TxBuf9bits_Write(Instance, TxAddr | UART_THR_MSB_9thbit);
            __LL_UART_SendDat_Start(Instance);
            return LL_OK;
        }

    } else {
        return LL_ERROR;
    }
}


/**
  * @brief  UART LL RS485 Config
  * @param  Instance Specifies UART peripheral
  * @param  Cfg RS485 config pointer
    @note  The receive funtion is Enable by default
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_RS485Cfg(UART_TypeDef *Instance, UART_Rs485CfgTypeDef *Cfg)
{
    /* Check the UART initiation struct allocation */
    assert_param(IS_UART_ALL_INSTANCE(Instance));

    //RS485 mode enable
    __LL_UART_RS485Mode_En(Instance);

    //DE signal enable and palarity config
    UART_FUNC_ALTER(Cfg->de_en == ENABLE, __LL_UART_DE_En(Instance), __LL_UART_DE_Dis(Instance));

    /* The receive funtion is Enable by default*/
    __LL_UART_RE_En(Instance);

    UART_FUNC_ALTER(Cfg->de_polarity == UART_DE_POL_ACT_LOW, __LL_UART_DE_ActLow_Set(Instance), __LL_UART_DE_ActHigh_Set(Instance));

    //DE assert/deassert time config
    __LL_UART_DE_AssertTime_Set(Instance, Cfg->de_assert_time);
    __LL_UART_DE_DeAssertTime_Set(Instance, Cfg->de_deassert_time);

    return LL_OK;
}

/**
  * @brief  This indicates the number of data entries in the transmit FIFO
  * @param  Instance UART peripheral
  * @return the number of data entries in the transmit FIFO
  */
uint8_t LL_UART_TxFIFOLVL_GET(UART_TypeDef *Instance)
{
    return __LL_UART_TxFIFOLevel_Get(Instance);
}

/**
  * @brief  This indicates the number of data entries in the receive FIFO.
  * @param  Instance UART peripheral
  * @return the number of data entries in the receive FIFO.
  */
uint8_t LL_UART_RxFIFOLVL_GET(UART_TypeDef *Instance)
{
    return __LL_UART_RxFIFOLevel_Get(Instance);
}

/**
  * @}
  */


/** @defgroup UART_LL_Exported_Functions_Interrupt UART Interrupt handler and callback
  * @brief    UART Interrupt handler and callback
  * @{
  */

/**
  * @brief  UART LL IRQ Handler
  * @param  Instance &#&
  * @return None
  */
void LL_UART_IRQHandler(UART_TypeDef *Instance)
{
    uint8_t int_id = __LL_UART_INT_ID_Get(Instance);

    switch (int_id) {
        case UART_INT_ID_MODEM_STA:
            LL_UART_ModemStaCallback(Instance);
            break;

        case UART_INT_ID_TX_EMPTY:
            LL_UART_TxEmptyCallback(Instance);
            break;

        case UART_INT_ID_RX_AVL:
            LL_UART_RxAvailableCallback(Instance);
            break;

        case UART_INT_ID_RX_LINE_STA:
            LL_UART_RxLineStaCallback(Instance);
            break;

        case UART_INT_ID_BUSY_DET:
            LL_UART_BusyDetCallback(Instance);
            break;

        case UART_INT_ID_CHAR_TIMEOUT:
            LL_UART_CharTimeOutCallback(Instance);
            break;

        default:
            LOG_E("Error interrupt ID!\n");
            break;
    }
}


/**
  * @brief  UART LL Modem Status Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_ModemStaCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_ModemStaCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Tx Empty Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_TxEmptyCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_TxEmptyCallback could be implemented in the user file
     */

}

/**
  * @brief  UART LL Rx Available Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxAvailableCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxAvailableCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL RX Line Status Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxLineStaCallback(UART_TypeDef *Instance)
{
    uint32_t line_sta = __LL_UART_LineSta_Get(Instance);

    if (line_sta & UART_LSR_RFE_Msk) {
        if (line_sta & UART_LSR_BI_Msk) {
            LL_UART_BreakErrCallback(Instance);
        }

        if (line_sta & UART_LSR_FE_Msk) {
            LL_UART_FrameErrCallback(Instance);
        }

        if (line_sta & UART_LSR_PE_Msk) {
            LL_UART_ParityErrCallback(Instance);
        }

        if (line_sta & UART_LSR_OE_Msk) {
            LL_UART_RxOverrunErrCallback(Instance);
        }
    }
}

/**
  * @brief  UART LL Busy Detect Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_BusyDetCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_BusyDetCallback could be implemented in the user file
     */
}

/**
  * @brief  UART LL Character Timeout Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_CharTimeOutCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_CharTimeOutCallback could be implemented in the user file
     */
}


/**
  * @brief  UART LL Break Error Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_BreakErrCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_BreakErrCallback could be implemented in the user file
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
  * @brief  UART LL RX Overrun Error Interrupt Callback
  * @param  Instance Specifies UART peripheral
  * @return None
  */
__WEAK void LL_UART_RxOverrunErrCallback(UART_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_UART_RxOverrunErrCallback could be implemented in the user file
     */

}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/
/** @defgroup UART_LL_Private_Functions UART LL Private function
  * @brief    UART LL Private function
  * @{
  */


#ifdef LL_DMA_MODULE_ENABLED
/**
  * @brief  UART LL DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @param  Timeout Limited operation time
  * @return DMA_ChannelETypeDef
  */
DMA_ChannelETypeDef LL_UART_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
{
    DMA_ChannelETypeDef ch = DMA_CHANNEL_INVALID;
    int ret;

    /* User DAM channel request */
    ch = LL_DMA_ChannelRequest();

    if (ch == DMA_CHANNEL_INVALID) {
        LOG_E("Requset DMA channel Fail!\n");
        return DMA_CHANNEL_INVALID;
    }

    /* User DMA init */
    ret = LL_DMA_Init(DMA, ch, dma_user_cfg);

    if (ret) {
        LOG_E("DMA LL init fail!\n");
        LL_DMA_ChannelRelease(ch);
        ch = DMA_CHANNEL_INVALID;
        return DMA_CHANNEL_INVALID;
    }

    return ch;
}

/**
  * @brief  UART LL DMA Deinit
  * @param  Instance Specifies UART peripheral
  * @param  frame frame pointer
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_UART_DMA_Deinit(DMA_ChannelETypeDef ch)
{
    /* Deinit DMA after tranfer completed */
    LL_DMA_DeInit(DMA, ch);

    /* DMA LL channel release */
    LL_DMA_ChannelRelease(ch);

    /* DMA stop work */
    LL_DMA_Stop_IT(DMA, ch);

    return LL_OK;
}

/**
  * @brief  UART DMA TX Channel complete callback
  * @param  arg Unlimited parameter
  * @return None
  */
void LL_UART_DMA_TXCHEndCallback(void *arg)
{
    UART_DMAHandleTypeDef *p_frame = ((UART_DMAHandleTypeDef *)arg);

    /* Wait for UART Transmit completed */
    while (!__LL_UART_IsTxEmpty(p_frame->Instance));

    /* UART LL DMA Deinit */
    LL_UART_DMA_Deinit(p_frame->dma_tx_ch);

    /* Disable Transmit DMA func */
    p_frame->dma_tx_ch = DMA_CHANNEL_INVALID;

    /* process has been finished */
    p_frame->TXdma_status = UART_DMA_STATE_FINISH;
}

/**
  * @brief  UART DMA RX Channel complete callback
  * @param  arg Unlimited parameter
  * @return None
  */
void LL_UART_DMA_RXCHEndCallback(void *arg)
{
    UART_DMAHandleTypeDef *p_frame = ((UART_DMAHandleTypeDef *)arg);

    /* UART LL DMA Deinit */
    LL_UART_DMA_Deinit(p_frame->dma_rx_ch);

    p_frame->dma_rx_ch = DMA_CHANNEL_INVALID;

    /* process has been finished */
    p_frame->RXdma_status = UART_DMA_STATE_FINISH;
}

/**
  * @brief  UART DMA TX Channel Error callback
  * @param  arg Unlimited parameter
  * @return None
  */
void LL_UART_DMA_TXCHErrorCallBck(void *arg)
{
    UART_DMAHandleTypeDef *p_frame = ((UART_DMAHandleTypeDef *)arg);

    /* UART LL DMA Deinit */
    LL_UART_DMA_Deinit(p_frame->dma_tx_ch);

    p_frame->dma_tx_ch = DMA_CHANNEL_INVALID;

    /* process has been Error */
    p_frame->TXdma_status = UART_DMA_STATE_ERROR;
}

/**
  * @brief  UART DMA RX Channel Error callback
  * @param  arg Unlimited parameter
  * @return None
  */
void LL_UART_DMA_RXCHErrorCallBck(void *arg)
{
    UART_DMAHandleTypeDef *p_frame = ((UART_DMAHandleTypeDef *)arg);

    /* UART LL DMA Deinit */
    LL_UART_DMA_Deinit(p_frame->dma_rx_ch);

    p_frame->dma_rx_ch = DMA_CHANNEL_INVALID;

    /* process has been Error */
    p_frame->RXdma_status = UART_DMA_STATE_ERROR;
}

#endif  /* LL_DMA_MODULE_ENABLED */
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

