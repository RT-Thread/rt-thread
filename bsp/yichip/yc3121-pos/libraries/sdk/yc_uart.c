/*
File Name    : yc_uart.c
Author       : Yichip
Version      : V1.0
Date         : 2019/12/4
Description  : UART encapsulation.
*/
#include "yc_uart.h"

#define uart_DMA_buf_len 1024
uint8_t uart0_DMA_buf[uart_DMA_buf_len] = {0};
uint8_t uart1_DMA_buf[uart_DMA_buf_len] = {0};

#define RX_ENABLE_BIT 0
#define RX_ENABLE (1 << RX_ENABLE_BIT)

#define UART_DMA_ENABLE_BIT 31
#define UART_DMA_ENABLE (1 << UART_DMA_ENABLE_BIT)

#define TX_INTR_ENABLE_BIT 31
#define TX_INTR_ENABLE ((uint32_t)1 << TX_INTR_ENABLE_BIT)

#define Set_RxITNum_Mask 0xff00
#define Statu_RxNum_Mask (uint32_t)0xffff0000

void UART_AutoFlowCtrlCmd(UART_TypeDef UARTx, FunctionalState NewState)
{
    _ASSERT(IS_UART(UARTx));

    if (NewState == ENABLE)
    {
        switch (UARTx)
        {
        case UART0:
            UART0_CTRL |= FlowCtrl_Enable;
            break;
        case UART1:
            UART1_CTRL |= FlowCtrl_Enable;
            break;
        }
    }
    else
    {
        switch (UARTx)
        {
        case UART0:
            UART0_CTRL &= (~FlowCtrl_Enable);
            break;
        case UART1:
            UART1_CTRL &= (~FlowCtrl_Enable);
            break;
        }
    }
    return;
}

void UART_ClearIT(UART_TypeDef UARTx)
{
    uint8_t ITType = UART_GetITIdentity(UARTx);
    UART_ITConfig(UARTx, ITType, DISABLE);
}

void UART_DeInit(UART_TypeDef UARTx)
{
    _ASSERT(IS_UART(UARTx));

    switch (UARTx)
    {
    case UART0:
        UART0_CTRL = 0;
        break;
    case UART1:
        UART1_CTRL = 0;
        break;
    }
}

void UART_DMASendBuf(UART_TypeDef UARTx, uint8_t *buf, int len)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(NULL != buf);
    _ASSERT((len < 0xffff));

    if (UARTx == UART0)
    {
        DMA_SRC_ADDR(DMACH_UART0) = (int)buf;
        DMA_LEN(DMACH_UART0) = (DMA_LEN(DMACH_UART0) & 0xffff) | len << 16;
        DMA_START(DMACH_UART0) = (1 << DMA_START_BIT);
    }
    else
    {
        DMA_SRC_ADDR(DMACH_UART1) = (int)buf;
        DMA_LEN(DMACH_UART1) = (DMA_LEN(DMACH_UART1) & 0xffff) | len << 16;
        DMA_START(DMACH_UART1) = (1 << DMA_START_BIT);
    }
}

uint8_t UART_GetITIdentity(UART_TypeDef UARTx)
{
    uint8_t IT_Mode = 0;
    switch (UARTx)
    {
    case UART0:
    {
        if (((UART0_CTRL & Set_RxITNum_Mask) > 0) && ((UART0_STATUS >> 16) > 0))
        {
            IT_Mode = UART_IT_RX;
        }
        else
        {
            if ((UART0_CTRL & (uint32_t)TX_INTR_ENABLE))
            {
                IT_Mode = UART_IT_TX;
            }
            else
            {
                IT_Mode = FALSE;
            }
        }
    }
    break;

    case UART1:
    {
        if (((UART1_CTRL & Set_RxITNum_Mask) > 0) && ((UART1_STATUS >> 16) > 0))
        {
            IT_Mode = UART_IT_RX;
        }
        else
        {
            if (UART1_CTRL & TX_INTR_ENABLE)
            {
                IT_Mode = UART_IT_TX;
            }
            else
            {
                IT_Mode = FALSE;
            }
        }
    }
    break;
    }
    return IT_Mode;
}

void UART_Init(UART_TypeDef UARTx, UART_InitTypeDef *UART_InitStruct)
{
#define RESET_BAUD (1 << 7)
#define AUTO_BAUD (0 << 7)
    uint32_t reg_value = 0;
    uint32_t temp_baudrate = 0;

    _ASSERT(IS_UART(UARTx));
    _ASSERT(IS_MODE(UART_InitStruct->Mode));
    _ASSERT(IS_BAUDRATE(UART_InitStruct->BaudRate));
    _ASSERT(IS_PARITY(UART_InitStruct->Parity));
    _ASSERT(IS_FlowCtrl(UART_InitStruct->FlowCtrl));
    _ASSERT(IS_USART_STOPBITS(UART_InitStruct->StopBits));

    temp_baudrate = ((48000000 / UART_InitStruct->BaudRate) << 16);

    reg_value = RX_ENABLE |
                UART_InitStruct->Parity |
                UART_InitStruct->DataBits |
                UART_InitStruct->StopBits |
                UART_InitStruct->FlowCtrl |
                UART_InitStruct->Mode |
                RESET_BAUD |
                temp_baudrate;

    if (UARTx == UART0)
    {
        UART0_CTRL = 0;
        DMA_DEST_ADDR(DMACH_UART0) = (int)uart0_DMA_buf;
        DMA_LEN(DMACH_UART0) = uart_DMA_buf_len;
        DMA_CONFIG(DMACH_UART0) = 1;
        DMA_START(DMACH_UART0) |= (1 << (DMA_RESET_BIT));
        DMA_START(DMACH_UART0) &= ~(1 << (DMA_RESET_BIT));
        UART0_CTRL = 0;
        UART0_CTRL = reg_value;
    }
    else
    {
        UART1_CTRL = 0;
        DMA_DEST_ADDR(DMACH_UART1) = (int)uart1_DMA_buf;
        DMA_LEN(DMACH_UART1) = uart_DMA_buf_len;
        DMA_CONFIG(DMACH_UART1) = 1;
        DMA_START(DMACH_UART1) |= (1 << (DMA_RESET_BIT));
        DMA_START(DMACH_UART1) &= ~(1 << (DMA_RESET_BIT));
        UART1_CTRL = 0;
        UART1_CTRL = reg_value;
    }
    return;
}

Boolean UART_IsRXFIFOFull(UART_TypeDef UARTx)
{
#define BITRXFULL 1
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        return (Boolean)(UART0_STATUS & (1 << BITRXFULL));
    }
    else
    {
        return (Boolean)(UART1_STATUS & (1 << BITRXFULL));
    }
}

Boolean UART_IsRXFIFONotEmpty(UART_TypeDef UARTx)
{
#define BITRXEMPTY 0
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        return (Boolean)((UART0_STATUS >> 16) ? 1 : 0);
    }
    else
    {
        return (Boolean)((UART1_STATUS >> 16) ? 1 : 0);
    }
}

Boolean UART_IsUARTBusy(UART_TypeDef UARTx)
{
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        return (Boolean)(!(DMA_STATUS(DMACH_UART0) & 1));
    }
    else
    {
        return (Boolean)(!(DMA_STATUS(DMACH_UART1) & 1));
    }
}

void UART_ITConfig(UART_TypeDef UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(IS_UART_IT(UART_IT));

    switch (UARTx)
    {
    case UART0:
    {
        if (UART_IT == UART_IT_RX)
        {
            if (NewState)
            {
                UART0_CTRL |= ((ENABLE << 8));
            }
            else
            {
                UART0_CTRL &= ~Set_RxITNum_Mask;
            }
        }
        else if (UART_IT == UART_IT_TX)
        {
            UART0_CTRL &= (~TX_INTR_ENABLE);
            UART0_CTRL |= (NewState << TX_INTR_ENABLE_BIT);
        }
    }
    break;

    case UART1:
    {
        if (UART_IT == UART_IT_RX)
        {
            if (NewState)
            {
                UART1_CTRL |= ((ENABLE << 8));
            }
            else
            {
                UART1_CTRL &= ~Set_RxITNum_Mask;
            }
        }
        else if (UART_IT == UART_IT_TX)
        {
            UART1_CTRL &= (uint32_t)~TX_INTR_ENABLE;
            UART1_CTRL |= (NewState << TX_INTR_ENABLE_BIT);
        }
    }
    break;
    }
}

uint8_t UART_ReceiveData(UART_TypeDef UARTx)
{
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        return UART0_RDATA;
    }
    else
    {
        return UART1_RDATA;
    }
}

int UART_RecvBuf(UART_TypeDef UARTx, uint8_t *buf, int len)
{
    uint32_t length = 0;
    volatile int *pstatus = NULL;
    volatile unsigned char *pdata = NULL;
    _ASSERT(IS_UART(UARTx));
    _ASSERT(NULL != buf);

    if (UART0 == UARTx)
    {
        pstatus = &UART0_STATUS;
        pdata = &UART0_RDATA;
    }
    else
    {
        pstatus = &UART1_STATUS;
        pdata = &UART1_RDATA;
    }

    while ((*pstatus >> 16) > 0)
    {
        if (length < len)
        {
            buf[length++] = *pdata;
        }
        else
        {
            break;
        }
    }

    return length;
}

void UART_SendBuf(UART_TypeDef UARTx, uint8_t *buf, int len)
{
    _ASSERT(IS_UART(UARTx));
    _ASSERT(NULL != buf);
    _ASSERT((len < 0xffff));

    if (UARTx == UART0)
    {
        DMA_SRC_ADDR(DMACH_UART0) = (int)buf;
        DMA_LEN(DMACH_UART0) = (DMA_LEN(DMACH_UART0) & 0xffff) | len << 16;
        DMA_START(DMACH_UART0) = (1 << DMA_START_BIT);
        while ((!(DMA_STATUS(DMACH_UART0) & 1)));
    }
    else
    {
        DMA_SRC_ADDR(DMACH_UART1) = (int)buf;
        DMA_LEN(DMACH_UART1) = (DMA_LEN(DMACH_UART1) & 0xffff) | len << 16;
        DMA_START(DMACH_UART1) = (1 << DMA_START_BIT);
        while ((!(DMA_STATUS(DMACH_UART1) & 1)));
    }
}

void UART_SendData(UART_TypeDef UARTx, uint8_t Data)
{
    uint8_t buf[1] = {Data};

    if (UARTx == UART0)
    {
        DMA_SRC_ADDR(DMACH_UART0) = (int)buf;
        DMA_LEN(DMACH_UART0) = (DMA_LEN(DMACH_UART0) & 0xffff) | 1 << 16;
        DMA_START(DMACH_UART0) = (1 << DMA_START_BIT);
        while (!(DMA_STATUS(DMACH_UART0) & 1));
    }
    else
    {
        DMA_SRC_ADDR(DMACH_UART1) = (int)buf;
        DMA_LEN(DMACH_UART1) = (DMA_LEN(DMACH_UART1) & 0xffff) | 1 << 16;
        DMA_START(DMACH_UART1) = (1 << DMA_START_BIT);
        while (!(DMA_STATUS(DMACH_UART1) & 1));
    }
}

void UART_SetITTimeout(UART_TypeDef UARTx, uint16_t timeout)
{
    if (UART0 == UARTx)
    {
        UART0_INTR = timeout;
    }
    else
    {
        UART1_INTR = timeout;
    }
}

void UART_SetRxITNum(UART_TypeDef UARTx, uint8_t Bcnt)
{
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        UART0_CTRL = (UART0_CTRL & 0xffff00ff) | ((Bcnt & 0xff) << 8);
    }
    else
    {
        UART1_CTRL = (UART1_CTRL & 0xffff00ff) | ((Bcnt & 0xff) << 8);
    }
}

void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
    UART_InitStruct->BaudRate = 9600;
    UART_InitStruct->DataBits = Databits_8b;
    UART_InitStruct->FlowCtrl = FlowCtrl_None;
    UART_InitStruct->Mode = Mode_duplex;
    UART_InitStruct->StopBits = StopBits_1;
    UART_InitStruct->Parity = 0;
}

uint16_t UART_ReceiveDataLen(UART_TypeDef UARTx)
{
    _ASSERT(IS_UART(UARTx));

    if (UART0 == UARTx)
    {
        return (uint16_t)(UART0_STATUS >> 16);
    }
    else
    {
        return (uint16_t)(UART1_STATUS >> 16);
    }
}
