/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_uart.h"

void UART_Init(UART_Type * UARTx, UART_Init_Type * init)
{
    uint32_t ccr = UARTx->CCR & ~(    UART_CCR_PEN_MASK
                                    | UART_CCR_PSEL_MASK
                                    | UART_CCR_SPB0_MASK
                                    | UART_CCR_CHAR_MASK
                                    | UART_CCR_SPB1_MASK
                                 );
    /* WordLength. */
    ccr |= UART_CCR_CHAR(init->WordLength);

    /* StopBits. */
    if ( (init->StopBits == UART_StopBits_2) || (init->StopBits == UART_StopBits_1_5) )
    {
        ccr |= UART_CCR_SPB0_MASK;
    }
    if ( (init->StopBits == UART_StopBits_0_5) || (init->StopBits == UART_StopBits_1_5) )
    {
        ccr |= UART_CCR_SPB1_MASK;
    }

    /* Parity. */
    if (init->Parity == UART_Parity_Even)
    {
        ccr |= UART_CCR_PEN_MASK;
    }
    if (init->Parity == UART_Parity_Odd)
    {
        ccr |= UART_CCR_PEN_MASK | UART_CCR_PSEL_MASK;
    }
    UARTx->CCR = ccr;

    /* XferMode. */
    uint32_t gcr = UARTx->GCR & ~(   UART_GCR_RXEN_MASK
                                   | UART_GCR_TXEN_MASK
                                   | UART_GCR_AUTOFLOWEN_MASK
                                 );
    gcr |= ((uint32_t)(init->XferMode) << UART_GCR_RXEN_SHIFT);
    if (init->HwFlowControl == UART_HwFlowControl_RTS_CTS)
    {
        gcr |= UART_GCR_AUTOFLOWEN_MASK;
    }
    UARTx->GCR = gcr;

    /* Setup the baudrate. */
    UARTx->BRR = (init->ClockFreqHz / init->BaudRate) / 16u;
    UARTx->FRA = (init->ClockFreqHz / init->BaudRate) % 16u;
}

void UART_Enable(UART_Type * UARTx, bool enable)
{
    if (enable)
    {
        UARTx->GCR |= UART_GCR_UARTEN_MASK;
    }
    else
    {
        UARTx->GCR &= ~UART_GCR_UARTEN_MASK;
    }
}

void UART_EnableInterrupts(UART_Type * UARTx, uint32_t interrupts, bool enable)
{
    (enable) ? (UARTx->IER |= interrupts) : (UARTx->IER &= ~interrupts);
}

uint32_t UART_GetEnabledInterrupts(UART_Type * UARTx)
{
    return UARTx->IER;
}

void UART_EnableDMA(UART_Type * UARTx, bool enable)
{
    if (enable)
    {
        UARTx->GCR |= UART_GCR_DMAMODE_MASK;
    }
    else
    {
        UARTx->GCR &= ~UART_GCR_DMAMODE_MASK;
    }
}

void UART_PutData(UART_Type * UARTx, uint8_t value)
{
    UARTx->TDR = value;
}

uint8_t UART_GetData(UART_Type * UARTx)
{
    return (uint8_t)(UARTx->RDR & 0xFFU);
}

/* return flags */
uint32_t UART_GetStatus(UART_Type * UARTx)
{
    return UARTx->CSR;
}

/* return flags. */
uint32_t UART_GetInterruptStatus(UART_Type * UARTx)
{
    return UARTx->ISR;
}

void UART_ClearInterruptStatus(UART_Type * UARTx, uint32_t interrupts)
{
    UARTx->ICR = interrupts;
}

uint32_t   UART_GetRxDataRegAddr(UART_Type * UARTx)
{
    return (uint32_t)(&(UARTx->RDR));
}

uint32_t   UART_GetTxDataRegAddr(UART_Type * UARTx)
{
    return (uint32_t)(&(UARTx->TDR));
}

/* EOF. */
