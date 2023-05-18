/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_uart.c
 * @brief    source file for setting uart
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2020-11-06      wushengyan         V1.0.0         the first version
 */

#include "yc_uart.h"

#define uart_DMA_buf_len    1024
const UART_TypeDef * const UARTs[] = {MUART0, MUART1, MUART2, MUART3};
uint8_t uart0_DMA_buf[uart_DMA_buf_len] = {0};
uint8_t uart1_DMA_buf[uart_DMA_buf_len] = {0};
uint8_t uart2_DMA_buf[uart_DMA_buf_len] = {0};
uint8_t uart3_DMA_buf[uart_DMA_buf_len] = {0};

#define RX_ENABLE           BIT0
#define UART_DMA_ENABLE     BIT31
#define TX_INTR_ENABLE      BIT31
#define Set_RxITNum_Mask    0xff00
#define Statu_RxNum_Mask    (uint32_t)0xffff0000

/**
 * @method UART_Buffer_Select
 * @brief  select UART buffer
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval NULL
 */
static uint8_t *UART_Buffer_Select(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));
    uint8_t *buffers[] = {uart0_DMA_buf, uart1_DMA_buf, uart2_DMA_buf, uart3_DMA_buf};

    for (int i = 0; i < sizeof(UARTs) / sizeof(UARTs[0]); i++)
    {
        if ((void *)UARTs[i] == (void *)UARTx)
        {
            return buffers[i];
        }
    }
    return NULL;
}

/**
 * @method UART_DeInit
 * @brief  DeInit UART
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval None
 */
void UART_DeInit(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));
    UARTx->CTRL.reg = 0;
    UARTx->RX_INT_LEN.reg = 0;
}

/**
 * @method UART_Init
 * @brief  Initializes the UARTx peripheral according to
 *         the specified parameters.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure that
 *         contains the configuration information.
 */
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
    DMA_TypeDef *DMAx = NULL;
    uint8_t *uartx_DMA_buf = NULL;
    uint32_t temp_baudrate = 0;

    _ASSERT(IS_UART(UARTx));
    _ASSERT(IS_UART_RX_MODE(UART_InitStruct->RxMode));
    _ASSERT(IS_UART_PARITY(UART_InitStruct->Parity));
    _ASSERT(IS_UART_WORD_LENGTH(UART_InitStruct->DataBits));
    _ASSERT(IS_UART_STOPBITS(UART_InitStruct->StopBits));
    _ASSERT(IS_UART_FLOW_CTRL(UART_InitStruct->FlowCtrl));
    _ASSERT(IS_UART_SMART_CARD(UART_InitStruct->SmartCard));
    _ASSERT(IS_UART_COMM_MODE(UART_InitStruct->CommMode));
    _ASSERT(IS_UART_BAUDRATE(UART_InitStruct->BaudRate));

    DMAx = (DMA_TypeDef *)((uint32_t)UARTx - sizeof(DMA_TypeDef));
    uartx_DMA_buf = UART_Buffer_Select(UARTx);
    temp_baudrate = (48000000 / UART_InitStruct->BaudRate);

    UART_DeInit(UARTx);
    DMAx->DEST_ADDR.reg               = (uint32_t)uartx_DMA_buf;
    DMAx->LEN_LOW.bit.RX_LEN_L        = uart_DMA_buf_len;
    DMAx->CTRL.bit.LOOPBACK           = 1;
    DMAx->CTRL.bit.RESET              = 1;
    DMAx->CTRL.bit.RESET              = 0;

    UARTx->CTRL.bit.RX_EN           = UART_InitStruct->RxMode;
    UARTx->CTRL.bit.PARITY          = UART_InitStruct->Parity;
    UARTx->CTRL.bit.DATA_BITS       = UART_InitStruct->DataBits;
    UARTx->CTRL.bit.STOP_BITS       = UART_InitStruct->StopBits;
    UARTx->CTRL.bit.FLOW_CTRL       = UART_InitStruct->FlowCtrl;
    UARTx->CTRL.bit.SMART_CARD      = UART_InitStruct->SmartCard;
    UARTx->CTRL.bit.HDX_EN          = UART_InitStruct->CommMode;
    UARTx->CTRL.bit.RESET_BAUD      = ENABLE;
    UARTx->BAUD.bit.BAUD_RATE       = temp_baudrate;
}

/**
 * @method UART_StructInit
 * @brief  Fills each USART_InitStruct member with its default value.
 * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
 *         which will be initialized.
 * @retval None
 */
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
    UART_InitStruct->BaudRate  = 9600;
    UART_InitStruct->RxMode    = MODE_RX_ENABLE;
    UART_InitStruct->Parity    = YC_PARITY_NONE;
    UART_InitStruct->DataBits  = DATABITS_8B;
    UART_InitStruct->StopBits  = STOPBITS_1;
    UART_InitStruct->FlowCtrl  = FLOWCTRL_NONE;
    UART_InitStruct->SmartCard = SMARTCARD_DISABLE;
    UART_InitStruct->CommMode  = MODE_DUPLEX;
}

/**
 * @method UART_ITConfig
 * @brief  Enable or disable the specified UART interrupt.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  UART_IT: specifies the UART interrupt sources
 *         This parameter can be one of the following values:
 *     @arg UART_IT_TX:interrupt trigger after send data completed.
 *     @arg UART_IT_RX:interrupt trigger when received data.
 * @param  NewState: new state of the specified UART interrupt
 *          This parameter can be ENABLE or DISABLE
 */
void UART_ITConfig(UART_TypeDef *UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(IS_UART_IT(UART_IT));

    if (UART_IT == UART_IT_TX)
    {
        UARTx->BAUD.bit.TX_INT_EN = NewState;
    }
    else if (UART_IT == UART_IT_RX)
    {
        UARTx->RX_INT_LEN.bit.VAL = NewState;
    }
}

/**
 * @method UART_SendData
 * @brief  UART Send One Data
 * @param  UARTx: Select  the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval None
 */
void UART_SendData(UART_TypeDef *UARTx, uint8_t Data)
{
    _ASSERT(IS_UART(UARTx));

    volatile uint8_t buf[1];

    buf[0] = Data;
    DMA_TypeDef *DMAx                    = (DMA_TypeDef *)((uint32_t)UARTx - sizeof(DMA_TypeDef));
    DMAx->SRC_ADDR.reg                   = (uint32_t)buf;
    DMAx->LEN_LOW.bit.TX_LEN_L           = 1;
    DMAx->CTRL.bit.START                 = 1;

    while (DMAx->STATUS.bit.DONE != 1);
}

/**
 * @method UART_SendBuf
 * @brief  Transmits datas via UART DMA, the function will return after datas is sent.
 * @param  USARTx: Select the USART or the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  buf: pointer to a buf that contains the data you want transmit.
 * @param  len: the buf length
 * @retval None
 */
void UART_SendBuf(UART_TypeDef *UARTx, uint8_t *buf, uint32_t len)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(NULL != buf);
    _ASSERT(len < 0xfffff);

    DMA_TypeDef *DMAx                = (DMA_TypeDef *)((uint32_t)UARTx - sizeof(DMA_TypeDef));
    DMAx->SRC_ADDR.reg               = (uint32_t)buf;
    DMAx->LEN_LOW.bit.TX_LEN_L       = len & 0xffff;
    DMAx->CTRL.bit.TX_LEN_H          = len >> 16;
    DMAx->CTRL.bit.START             = 1;

    while (DMAx->STATUS.bit.DONE != 1);
}

/**
 * @method UART_ReceiveData
 * @brief  Receive single data through the USARTx peripheral.
 * @param  USARTx: Select the USART or the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval An one byte received data.
 */
uint8_t UART_ReceiveData(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));

    return UARTx->RX_DATA.bit.VAL;

}

/**
 * @method UART_ReceiveBuf
 * @brief  Receives datas through the UART DMA.
 * @param  USARTx: Select the USART or the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  buf: pointer to a buf that contains the data you want receive.
 * @param  len: the buf length, which size should be less than 20 bit (len < 0xfffff)
 * @retval The length of received data before return.
 */
uint32_t UART_ReceiveBuf(UART_TypeDef *UARTx, uint8_t *buf, uint32_t len)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(NULL != buf);
    _ASSERT(len < 0xfffff);

    uint32_t rcv_len = 0;
    while ((UART_ReceiveDataLen(UARTx) > 0) && (rcv_len < len))
    {
        buf[rcv_len++] = UARTx->RX_DATA.bit.VAL;
    }

    return rcv_len;
}

/**
 * @method UART_AutoFlowCtrlCmd
 * @brief  ENABLE or DISABLE UARTx auto flow control
 * @param  USARTx: Select the USART or the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  NewState: ENABLE or DISABLE auto flow control
 * @retval None
 */
void UART_AutoFlowCtrlCmd(UART_TypeDef *UARTx, FunctionalState NewState)
{
    _ASSERT(IS_UART(UARTx));

    UARTx->CTRL.bit.FLOW_CTRL = NewState;
}

/**
 * @method UART_GetITIdentity
 * @brief  Get IT Identity
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval IT Identity
 */
uint8_t UART_GetITIdentity(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));
    //return (0 || (UARTx->BAUD.bit.TX_INT_EN) || (UARTx->RX_INT_LEN.bit.VAL));
    if((UARTx->RX_INT_LEN.reg > 0)&& (UARTx->STATUS.bit.RX_ITEMS_L >=UARTx->RX_INT_LEN.reg))
    {
        return UART_IT_RX;
    }
    else if(UARTx->BAUD.bit.TX_INT_EN)
    {
        return UART_IT_TX;
    }
    return 0;
}

/**
 * @method UART_IsRXFIFOFull
 * @brief  Check if the Rx fifo is full or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval TRUE:  Rx fifo is full.
 *         FALSE: Rx fifo is not full
 */
Boolean UART_IsRXFIFOFull(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));

    return (Boolean)(UARTx->STATUS.bit.RX_FULL);
}

/**
 * @method UART_IsRXFIFONotEmpty
 * @brief  Check if the Rx fifo is empty or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval TRUE: Rx fifo is not empty.
 *         FALSE: Rx fifo is empty
 */
Boolean UART_IsRXFIFONotEmpty(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));

    return (Boolean)(!(UARTx->STATUS.bit.RX_EMPTY));
}

/**
 * @method UART_IsBusy
 * @brief  Check if the UARTx is busy or not.
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval TRUE: UARTx is busy.
 *         FALSE: UARTx is not busy.
 */
Boolean UART_IsBusy(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));

    return (Boolean)(!(UARTx->STATUS.bit.RX_EMPTY));
}

/**
 * @method UART_SetITTimeout
 * @brief  Sets the interruption time for serial port timeout.
 * @param  USARTx: Select the USART or the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  timeout: 0x00~0xff
 * @retval None
 */
void UART_SetITTimeout(UART_TypeDef *UARTx, uint16_t timeout)
{
    _ASSERT(IS_UART(UARTx));

    UARTx->TIMEOUT_INT.reg = timeout;
}

/**
 * @method UART_SetRxITNum
 * @brief  Set the number of uart receive data intterupt trigger
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @param  Bcnt: if the number of receive datas greater than Bcnt,interrupt trigger
 * @retval None
 */
void UART_SetRxITNum(UART_TypeDef *UARTx, uint8_t Bcnt)
{
    _ASSERT(IS_UART(UARTx));

    UARTx->RX_INT_LEN.reg = Bcnt;
}

/**
 * @method UART_ReceiveDataLen
 * @brief  Return the length of received data
 * @param  UARTx: Select the UART peripheral.
 *         This parameter can be one of the following values:
 *         MUART0, MUART1, MUART2 or MUART3.
 * @retval Data len
 */
uint32_t UART_ReceiveDataLen(UART_TypeDef *UARTx)
{
    _ASSERT(IS_UART(UARTx));

    return (UARTx->STATUS.bit.RX_ITEMS_H << 16) + UARTx->STATUS.bit.RX_ITEMS_L;
}

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
