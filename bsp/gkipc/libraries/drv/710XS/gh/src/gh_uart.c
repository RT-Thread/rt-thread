/******************************************************************************
**
** \file      gh_uart.c
**
** \brief     UART.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#include "gh_uart.h"

U32  GH_UART_get_RBR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_RBR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_RBR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_RBR();
    }
    return (U32)0;
}
U8   GH_UART_get_RBR_Data(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_RBR_Data();
    }
    else if(index == 1)
    {
        return GH_UART1_get_RBR_Data();
    }
    else if(index == 2)
    {
        return GH_UART2_get_RBR_Data();
    }
    return (U8)0;
}

void GH_UART_set_THR(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_THR(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_THR(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_THR(data);
    }
}
U32  GH_UART_getm_THR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_THR();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_THR();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_THR();
    }
    return (U32)0;
}
void GH_UART_set_THR_Data(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_THR_Data(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_THR_Data(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_THR_Data(data);
    }
}
U8   GH_UART_getm_THR_Data(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_THR_Data();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_THR_Data();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_THR_Data();
    }
    return (U8)0;
}

void GH_UART_set_DLL(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_DLL(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_DLL(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_DLL(data);
    }
}
U32  GH_UART_get_DLL(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_DLL();
    }
    else if(index == 1)
    {
        return GH_UART1_get_DLL();
    }
    else if(index == 2)
    {
        return GH_UART2_get_DLL();
    }
    return (U32)0;
}
void GH_UART_set_DLL_BaudDivint_L(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_DLL_BaudDivint_L(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_DLL_BaudDivint_L(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_DLL_BaudDivint_L(data);
    }
}
U8   GH_UART_get_DLL_BaudDivint_L(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_DLL_BaudDivint_L();
    }
    else if(index == 1)
    {
        return GH_UART1_get_DLL_BaudDivint_L();
    }
    else if(index == 2)
    {
        return GH_UART2_get_DLL_BaudDivint_L();
    }
    return (U8)0;
}

void GH_UART_set_IER(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_IER(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_IER(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_IER(data);
    }
}
U32  GH_UART_get_IER(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IER();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IER();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IER();
    }
    return (U32)0;
}
void GH_UART_set_IER_erbfi(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_IER_erbfi(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_IER_erbfi(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_IER_erbfi(data);
    }
}
U8   GH_UART_get_IER_erbfi(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IER_erbfi();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IER_erbfi();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IER_erbfi();
    }
    return (U8)0;
}
void GH_UART_set_IER_etbei(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_IER_etbei(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_IER_etbei(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_IER_etbei(data);
    }
}
U8   GH_UART_get_IER_etbei(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IER_etbei();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IER_etbei();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IER_etbei();
    }
    return (U8)0;
}
void GH_UART_set_IER_elsi(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_IER_elsi(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_IER_elsi(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_IER_elsi(data);
    }
}
U8   GH_UART_get_IER_elsi(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IER_elsi();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IER_elsi();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IER_elsi();
    }
    return (U8)0;
}
void GH_UART_set_IER_edssi(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_IER_edssi(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_IER_edssi(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_IER_edssi(data);
    }
}
U8   GH_UART_get_IER_edssi(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IER_edssi();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IER_edssi();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IER_edssi();
    }
    return (U8)0;
}

void GH_UART_set_DLH(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_DLH(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_DLH(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_DLH(data);
    }
}
U32  GH_UART_get_DLH(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_DLH();
    }
    else if(index == 1)
    {
        return GH_UART1_get_DLH();
    }
    else if(index == 2)
    {
        return GH_UART2_get_DLH();
    }
    return (U32)0;
}
void GH_UART_set_DLH_BaudDivint_H(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_DLH_BaudDivint_H(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_DLH_BaudDivint_H(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_DLH_BaudDivint_H(data);
    }
}
U8   GH_UART_get_DLH_BaudDivint_H(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_DLH_BaudDivint_H();
    }
    else if(index == 1)
    {
        return GH_UART1_get_DLH_BaudDivint_H();
    }
    else if(index == 2)
    {
        return GH_UART2_get_DLH_BaudDivint_H();
    }
    return (U8)0;
}

U32  GH_UART_get_IIR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IIR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IIR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IIR();
    }
    return (U32)0;
}
U8   GH_UART_get_IIR_interrupt_id(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IIR_interrupt_id();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IIR_interrupt_id();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IIR_interrupt_id();
    }
    return (U8)0;
}
U8   GH_UART_get_IIR_fifos_enabled(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_IIR_fifos_enabled();
    }
    else if(index == 1)
    {
        return GH_UART1_get_IIR_fifos_enabled();
    }
    else if(index == 2)
    {
        return GH_UART2_get_IIR_fifos_enabled();
    }
    return (U8)0;
}

void GH_UART_set_FCR(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR(data);
    }
}
U32  GH_UART_getm_FCR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR();
    }
    return (U32)0;
}
void GH_UART_set_FCR_FIFO_Enable(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_FIFO_Enable(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_FIFO_Enable(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_FIFO_Enable(data);
    }
}
U8   GH_UART_getm_FCR_FIFO_Enable(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_FIFO_Enable();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_FIFO_Enable();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_FIFO_Enable();
    }
    return (U8)0;
}
void GH_UART_set_FCR_RCVR_FIFO_Reset(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_RCVR_FIFO_Reset(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_RCVR_FIFO_Reset(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_RCVR_FIFO_Reset(data);
    }
}
U8   GH_UART_getm_FCR_RCVR_FIFO_Reset(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_RCVR_FIFO_Reset();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_RCVR_FIFO_Reset();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_RCVR_FIFO_Reset();
    }
    return (U8)0;
}
void GH_UART_set_FCR_XMIT_FIFO_Reset(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_XMIT_FIFO_Reset(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_XMIT_FIFO_Reset(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_XMIT_FIFO_Reset(data);
    }
}
U8   GH_UART_getm_FCR_XMIT_FIFO_Reset(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_XMIT_FIFO_Reset();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_XMIT_FIFO_Reset();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_XMIT_FIFO_Reset();
    }
    return (U8)0;
}
void GH_UART_set_FCR_DMA_Mode(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_DMA_Mode(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_DMA_Mode(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_DMA_Mode(data);
    }
}
U8   GH_UART_getm_FCR_DMA_Mode(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_DMA_Mode();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_DMA_Mode();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_DMA_Mode();
    }
    return (U8)0;
}
void GH_UART_set_FCR_TX_Empty_Trigger(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_TX_Empty_Trigger(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_TX_Empty_Trigger(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_TX_Empty_Trigger(data);
    }
}
U8   GH_UART_getm_FCR_TX_Empty_Trigger(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_TX_Empty_Trigger();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_TX_Empty_Trigger();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_TX_Empty_Trigger();
    }
    return (U8)0;
}
void GH_UART_set_FCR_RCVR_Trigger(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_FCR_RCVR_Trigger(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_FCR_RCVR_Trigger(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_FCR_RCVR_Trigger(data);
    }
}
U8   GH_UART_getm_FCR_RCVR_Trigger(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_getm_FCR_RCVR_Trigger();
    }
    else if(index == 1)
    {
        return GH_UART1_getm_FCR_RCVR_Trigger();
    }
    else if(index == 2)
    {
        return GH_UART2_getm_FCR_RCVR_Trigger();
    }
    return (U8)0;
}

void GH_UART_set_LCR(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR(data);
    }
}
U32  GH_UART_get_LCR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR();
    }
    return (U32)0;
}
void GH_UART_set_LCR_cls(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_cls(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_cls(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_cls(data);
    }
}
U8   GH_UART_get_LCR_cls(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_cls();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_cls();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_cls();
    }
    return (U8)0;
}
void GH_UART_set_LCR_stop(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_stop(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_stop(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_stop(data);
    }
}
U8   GH_UART_get_LCR_stop(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_stop();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_stop();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_stop();
    }
    return (U8)0;
}
void GH_UART_set_LCR_pen(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_pen(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_pen(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_pen(data);
    }
}
U8   GH_UART_get_LCR_pen(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_pen();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_pen();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_pen();
    }
    return (U8)0;
}
void GH_UART_set_LCR_eps(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_eps(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_eps(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_eps(data);
    }
}
U8   GH_UART_get_LCR_eps(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_eps();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_eps();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_eps();
    }
    return (U8)0;
}
void GH_UART_set_LCR_sticky_parity(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_sticky_parity(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_sticky_parity(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_sticky_parity(data);
    }
}
U8   GH_UART_get_LCR_sticky_parity(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_sticky_parity();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_sticky_parity();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_sticky_parity();
    }
    return (U8)0;
}
void GH_UART_set_LCR_breaks(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_breaks(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_breaks(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_breaks(data);
    }
}
U8   GH_UART_get_LCR_breaks(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_breaks();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_breaks();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_breaks();
    }
    return (U8)0;
}
void GH_UART_set_LCR_dlab(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_LCR_dlab(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_LCR_dlab(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_LCR_dlab(data);
    }
}
U8   GH_UART_get_LCR_dlab(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LCR_dlab();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LCR_dlab();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LCR_dlab();
    }
    return (U8)0;
}

void GH_UART_set_MCR(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR(data);
    }
}
U32  GH_UART_get_MCR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR();
    }
    return (U32)0;
}
void GH_UART_set_MCR_dtr(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_dtr(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_dtr(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_dtr(data);
    }
}
U8   GH_UART_get_MCR_dtr(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_dtr();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_dtr();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_dtr();
    }
    return (U8)0;
}
void GH_UART_set_MCR_rts(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_rts(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_rts(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_rts(data);
    }
}
U8   GH_UART_get_MCR_rts(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_rts();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_rts();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_rts();
    }
    return (U8)0;
}
void GH_UART_set_MCR_out1(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_out1(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_out1(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_out1(data);
    }
}
U8   GH_UART_get_MCR_out1(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_out1();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_out1();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_out1();
    }
    return (U8)0;
}
void GH_UART_set_MCR_out2(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_out2(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_out2(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_out2(data);
    }
}
U8   GH_UART_get_MCR_out2(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_out2();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_out2();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_out2();
    }
    return (U8)0;
}
void GH_UART_set_MCR_loopback(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_loopback(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_loopback(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_loopback(data);
    }
}
U8   GH_UART_get_MCR_loopback(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_loopback();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_loopback();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_loopback();
    }
    return (U8)0;
}
void GH_UART_set_MCR_afce(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_afce(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_afce(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_afce(data);
    }
}
U8   GH_UART_get_MCR_afce(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_afce();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_afce();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_afce();
    }
    return (U8)0;
}
void GH_UART_set_MCR_sire(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_MCR_sire(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_MCR_sire(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_MCR_sire(data);
    }
}
U8   GH_UART_get_MCR_sire(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MCR_sire();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MCR_sire();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MCR_sire();
    }
    return (U8)0;
}

U32  GH_UART_get_LSR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR();
    }
    return (U32)0;
}
U8   GH_UART_get_LSR_dr(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_dr();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_dr();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_dr();
    }
    return (U8)0;
}
U8   GH_UART_get_LSR_oe(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_oe();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_oe();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_oe();
    }
    return (U8)0;
}
U8   GH_UART_get_LSR_pe(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_pe();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_pe();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_pe();
    }
    return (U8)0;
}
U8   GH_UART_get_LSR_fe(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_fe();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_fe();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_fe();
    }
    return (U8)0;
}
U8   GH_UART_get_LSR_bi(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_bi();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_bi();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_bi();
    }
    return (U8)0;
}
U8   GH_UART_get_LSR_temt(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_LSR_temt();
    }
    else if(index == 1)
    {
        return GH_UART1_get_LSR_temt();
    }
    else if(index == 2)
    {
        return GH_UART2_get_LSR_temt();
    }
    return (U8)0;
}

U32  GH_UART_get_MSR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR();
    }
    return (U32)0;
}
U8   GH_UART_get_MSR_dcts(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_dcts();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_dcts();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_dcts();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_ddsr(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_ddsr();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_ddsr();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_ddsr();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_teri(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_teri();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_teri();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_teri();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_ddcd(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_ddcd();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_ddcd();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_ddcd();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_cts(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_cts();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_cts();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_cts();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_dsr(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_dsr();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_dsr();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_dsr();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_ri(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_ri();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_ri();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_ri();
    }
    return (U8)0;
}
U8   GH_UART_get_MSR_dcd(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_MSR_dcd();
    }
    else if(index == 1)
    {
        return GH_UART1_get_MSR_dcd();
    }
    else if(index == 2)
    {
        return GH_UART2_get_MSR_dcd();
    }
    return (U8)0;
}

void GH_UART_set_SCR(U8 index, U32 data)
{
    if(index == 0)
    {
        GH_UART0_set_SCR(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_SCR(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_SCR(data);
    }
}
U32  GH_UART_get_SCR(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_SCR();
    }
    else if(index == 1)
    {
        return GH_UART1_get_SCR();
    }
    else if(index == 2)
    {
        return GH_UART2_get_SCR();
    }
    return (U32)0;
}
void GH_UART_set_SCR_scr(U8 index, U8 data)
{
    if(index == 0)
    {
        GH_UART0_set_SCR_scr(data);
    }
    else if(index == 1)
    {
        GH_UART1_set_SCR_scr(data);
    }
    else if(index == 2)
    {
        GH_UART2_set_SCR_scr(data);
    }
}
U8   GH_UART_get_SCR_scr(U8 index)
{
    if(index == 0)
    {
        return GH_UART0_get_SCR_scr();
    }
    else if(index == 1)
    {
        return GH_UART1_get_SCR_scr();
    }
    else if(index == 2)
    {
        return GH_UART2_get_SCR_scr();
    }
    return (U8)0;
}

void GH_UART_init(void)
{
    GH_UART0_init();
    GH_UART1_init();
    GH_UART2_init();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

