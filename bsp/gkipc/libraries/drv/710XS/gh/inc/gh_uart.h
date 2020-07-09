/*!
*******************************************************************************
**
** \file      gh_uart.h
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
#ifndef _GH_UART_H
#define _GH_UART_H

#include "gh_uart0.h"
#include "gh_uart1.h"
#include "gh_uart2.h"

#ifdef __cplusplus
extern "C" {
#endif

U32  GH_UART_get_RBR(U8 index);
U8   GH_UART_get_RBR_Data(U8 index);
void GH_UART_set_THR(U8 index, U32 data);
U32  GH_UART_getm_THR(U8 index);
void GH_UART_set_THR_Data(U8 index, U8 data);
U8   GH_UART_getm_THR_Data(U8 index);
void GH_UART_set_DLL(U8 index, U32 data);
U32  GH_UART_get_DLL(U8 index);
void GH_UART_set_DLL_BaudDivint_L(U8 index, U8 data);
U8   GH_UART_get_DLL_BaudDivint_L(U8 index);
void GH_UART_set_IER(U8 index, U32 data);
U32  GH_UART_get_IER(U8 index);
void GH_UART_set_IER_erbfi(U8 index, U8 data);
U8   GH_UART_get_IER_erbfi(U8 index);
void GH_UART_set_IER_etbei(U8 index, U8 data);
U8   GH_UART_get_IER_etbei(U8 index);
void GH_UART_set_IER_elsi(U8 index, U8 data);
U8   GH_UART_get_IER_elsi(U8 index);
void GH_UART_set_IER_edssi(U8 index, U8 data);
U8   GH_UART_get_IER_edssi(U8 index);
void GH_UART_set_DLH(U8 index, U32 data);
U32  GH_UART_get_DLH(U8 index);
void GH_UART_set_DLH_BaudDivint_H(U8 index, U8 data);
U8   GH_UART_get_DLH_BaudDivint_H(U8 index);
U32  GH_UART_get_IIR(U8 index);
U8   GH_UART_get_IIR_interrupt_id(U8 index);
U8   GH_UART_get_IIR_fifos_enabled(U8 index);
void GH_UART_set_FCR(U8 index, U32 data);
U32  GH_UART_getm_FCR(U8 index);
void GH_UART_set_FCR_FIFO_Enable(U8 index, U8 data);
U8   GH_UART_getm_FCR_FIFO_Enable(U8 index);
void GH_UART_set_FCR_RCVR_FIFO_Reset(U8 index, U8 data);
U8   GH_UART_getm_FCR_RCVR_FIFO_Reset(U8 index);
void GH_UART_set_FCR_XMIT_FIFO_Reset(U8 index, U8 data);
U8   GH_UART_getm_FCR_XMIT_FIFO_Reset(U8 index);
void GH_UART_set_FCR_DMA_Mode(U8 index, U8 data);
U8   GH_UART_getm_FCR_DMA_Mode(U8 index);
void GH_UART_set_FCR_TX_Empty_Trigger(U8 index, U8 data);
U8   GH_UART_getm_FCR_TX_Empty_Trigger(U8 index);
void GH_UART_set_FCR_RCVR_Trigger(U8 index, U8 data);
U8   GH_UART_getm_FCR_RCVR_Trigger(U8 index);
void GH_UART_set_LCR(U8 index, U32 data);
U32  GH_UART_get_LCR(U8 index);
void GH_UART_set_LCR_cls(U8 index, U8 data);
U8   GH_UART_get_LCR_cls(U8 index);
void GH_UART_set_LCR_stop(U8 index, U8 data);
U8   GH_UART_get_LCR_stop(U8 index);
void GH_UART_set_LCR_pen(U8 index, U8 data);
U8   GH_UART_get_LCR_pen(U8 index);
void GH_UART_set_LCR_eps(U8 index, U8 data);
U8   GH_UART_get_LCR_eps(U8 index);
void GH_UART_set_LCR_sticky_parity(U8 index, U8 data);
U8   GH_UART_get_LCR_sticky_parity(U8 index);
void GH_UART_set_LCR_breaks(U8 index, U8 data);
U8   GH_UART_get_LCR_breaks(U8 index);
void GH_UART_set_LCR_dlab(U8 index, U8 data);
U8   GH_UART_get_LCR_dlab(U8 index);
void GH_UART_set_MCR(U8 index, U32 data);
U32  GH_UART_get_MCR(U8 index);
void GH_UART_set_MCR_dtr(U8 index, U8 data);
U8   GH_UART_get_MCR_dtr(U8 index);
void GH_UART_set_MCR_rts(U8 index, U8 data);
U8   GH_UART_get_MCR_rts(U8 index);
void GH_UART_set_MCR_out1(U8 index, U8 data);
U8   GH_UART_get_MCR_out1(U8 index);
void GH_UART_set_MCR_out2(U8 index, U8 data);
U8   GH_UART_get_MCR_out2(U8 index);
void GH_UART_set_MCR_loopback(U8 index, U8 data);
U8   GH_UART_get_MCR_loopback(U8 index);
void GH_UART_set_MCR_afce(U8 index, U8 data);
U8   GH_UART_get_MCR_afce(U8 index);
void GH_UART_set_MCR_sire(U8 index, U8 data);
U8   GH_UART_get_MCR_sire(U8 index);
U32  GH_UART_get_LSR(U8 index);
U8   GH_UART_get_LSR_dr(U8 index);
U8   GH_UART_get_LSR_oe(U8 index);
U8   GH_UART_get_LSR_pe(U8 index);
U8   GH_UART_get_LSR_fe(U8 index);
U8   GH_UART_get_LSR_bi(U8 index);
U8   GH_UART_get_LSR_temt(U8 index);
U32  GH_UART_get_MSR(U8 index);
U8   GH_UART_get_MSR_dcts(U8 index);
U8   GH_UART_get_MSR_ddsr(U8 index);
U8   GH_UART_get_MSR_teri(U8 index);
U8   GH_UART_get_MSR_ddcd(U8 index);
U8   GH_UART_get_MSR_cts(U8 index);
U8   GH_UART_get_MSR_dsr(U8 index);
U8   GH_UART_get_MSR_ri(U8 index);
U8   GH_UART_get_MSR_dcd(U8 index);
void GH_UART_set_SCR(U8 index, U32 data);
U32  GH_UART_get_SCR(U8 index);
void GH_UART_set_SCR_scr(U8 index, U8 data);
U8   GH_UART_get_SCR_scr(U8 index);

void GH_UART_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_UART_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

