/******************************************************************************
**
** \file      gh_uart0.c
**
** \brief     UART0.
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
#include "gh_uart0.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_UART0_THR_S                          m_uart0_thr;
GH_UART0_FCR_S                          m_uart0_fcr;

/*----------------------------------------------------------------------------*/
/* register UART0_RBR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_UART0_get_RBR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_RBR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_RBR] --> 0x%08x\n",
                        REG_UART0_RBR,value);
    #endif
    return value;
}
U8   GH_UART0_get_RBR_Data(void)
{
    GH_UART0_RBR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_RBR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_RBR_Data] --> 0x%08x\n",
                        REG_UART0_RBR,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_THR (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_UART0_set_THR(U32 data)
{
    m_uart0_thr.all = data;
    *(volatile U32 *)REG_UART0_THR = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_THR] <-- 0x%08x\n",
                        REG_UART0_THR,data,data);
    #endif
}
U32  GH_UART0_getm_THR(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_THR] --> 0x%08x\n",
                        m_uart0_thr.all);
    #endif
    return m_uart0_thr.all;
}
void GH_UART0_set_THR_Data(U8 data)
{
    m_uart0_thr.bitc.data = data;
    *(volatile U32 *)REG_UART0_THR = m_uart0_thr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_THR_Data] <-- 0x%08x\n",
                        REG_UART0_THR,m_uart0_thr.all,m_uart0_thr.all);
    #endif
}
U8   GH_UART0_getm_THR_Data(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_THR_Data] --> 0x%08x\n",
                        m_uart0_thr.bitc.data);
    #endif
    return m_uart0_thr.bitc.data;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register UART0_DLL (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_DLL(U32 data)
{
    *(volatile U32 *)REG_UART0_DLL = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_DLL] <-- 0x%08x\n",
                        REG_UART0_DLL,data,data);
    #endif
}
U32  GH_UART0_get_DLL(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_DLL);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_DLL] --> 0x%08x\n",
                        REG_UART0_DLL,value);
    #endif
    return value;
}
void GH_UART0_set_DLL_BaudDivint_L(U8 data)
{
    GH_UART0_DLL_S d;
    d.all = *(volatile U32 *)REG_UART0_DLL;
    d.bitc.bauddivint_l = data;
    *(volatile U32 *)REG_UART0_DLL = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_DLL_BaudDivint_L] <-- 0x%08x\n",
                        REG_UART0_DLL,d.all,d.all);
    #endif
}
U8   GH_UART0_get_DLL_BaudDivint_L(void)
{
    GH_UART0_DLL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_DLL);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_DLL_BaudDivint_L] --> 0x%08x\n",
                        REG_UART0_DLL,value);
    #endif
    return tmp_value.bitc.bauddivint_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_IER (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_IER(U32 data)
{
    *(volatile U32 *)REG_UART0_IER = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_IER] <-- 0x%08x\n",
                        REG_UART0_IER,data,data);
    #endif
}
U32  GH_UART0_get_IER(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_IER);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IER] --> 0x%08x\n",
                        REG_UART0_IER,value);
    #endif
    return value;
}
void GH_UART0_set_IER_erbfi(U8 data)
{
    GH_UART0_IER_S d;
    d.all = *(volatile U32 *)REG_UART0_IER;
    d.bitc.erbfi = data;
    *(volatile U32 *)REG_UART0_IER = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_IER_erbfi] <-- 0x%08x\n",
                        REG_UART0_IER,d.all,d.all);
    #endif
}
U8   GH_UART0_get_IER_erbfi(void)
{
    GH_UART0_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IER);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IER_erbfi] --> 0x%08x\n",
                        REG_UART0_IER,value);
    #endif
    return tmp_value.bitc.erbfi;
}
void GH_UART0_set_IER_etbei(U8 data)
{
    GH_UART0_IER_S d;
    d.all = *(volatile U32 *)REG_UART0_IER;
    d.bitc.etbei = data;
    *(volatile U32 *)REG_UART0_IER = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_IER_etbei] <-- 0x%08x\n",
                        REG_UART0_IER,d.all,d.all);
    #endif
}
U8   GH_UART0_get_IER_etbei(void)
{
    GH_UART0_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IER);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IER_etbei] --> 0x%08x\n",
                        REG_UART0_IER,value);
    #endif
    return tmp_value.bitc.etbei;
}
void GH_UART0_set_IER_elsi(U8 data)
{
    GH_UART0_IER_S d;
    d.all = *(volatile U32 *)REG_UART0_IER;
    d.bitc.elsi = data;
    *(volatile U32 *)REG_UART0_IER = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_IER_elsi] <-- 0x%08x\n",
                        REG_UART0_IER,d.all,d.all);
    #endif
}
U8   GH_UART0_get_IER_elsi(void)
{
    GH_UART0_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IER);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IER_elsi] --> 0x%08x\n",
                        REG_UART0_IER,value);
    #endif
    return tmp_value.bitc.elsi;
}
void GH_UART0_set_IER_edssi(U8 data)
{
    GH_UART0_IER_S d;
    d.all = *(volatile U32 *)REG_UART0_IER;
    d.bitc.edssi = data;
    *(volatile U32 *)REG_UART0_IER = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_IER_edssi] <-- 0x%08x\n",
                        REG_UART0_IER,d.all,d.all);
    #endif
}
U8   GH_UART0_get_IER_edssi(void)
{
    GH_UART0_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IER);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IER_edssi] --> 0x%08x\n",
                        REG_UART0_IER,value);
    #endif
    return tmp_value.bitc.edssi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_DLH (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_DLH(U32 data)
{
    *(volatile U32 *)REG_UART0_DLH = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_DLH] <-- 0x%08x\n",
                        REG_UART0_DLH,data,data);
    #endif
}
U32  GH_UART0_get_DLH(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_DLH);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_DLH] --> 0x%08x\n",
                        REG_UART0_DLH,value);
    #endif
    return value;
}
void GH_UART0_set_DLH_BaudDivint_H(U8 data)
{
    GH_UART0_DLH_S d;
    d.all = *(volatile U32 *)REG_UART0_DLH;
    d.bitc.bauddivint_h = data;
    *(volatile U32 *)REG_UART0_DLH = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_DLH_BaudDivint_H] <-- 0x%08x\n",
                        REG_UART0_DLH,d.all,d.all);
    #endif
}
U8   GH_UART0_get_DLH_BaudDivint_H(void)
{
    GH_UART0_DLH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_DLH);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_DLH_BaudDivint_H] --> 0x%08x\n",
                        REG_UART0_DLH,value);
    #endif
    return tmp_value.bitc.bauddivint_h;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_IIR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_UART0_get_IIR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_IIR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IIR] --> 0x%08x\n",
                        REG_UART0_IIR,value);
    #endif
    return value;
}
U8   GH_UART0_get_IIR_interrupt_id(void)
{
    GH_UART0_IIR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IIR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IIR_interrupt_id] --> 0x%08x\n",
                        REG_UART0_IIR,value);
    #endif
    return tmp_value.bitc.interrupt_id;
}
U8   GH_UART0_get_IIR_fifos_enabled(void)
{
    GH_UART0_IIR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_IIR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_IIR_fifos_enabled] --> 0x%08x\n",
                        REG_UART0_IIR,value);
    #endif
    return tmp_value.bitc.fifos_enabled;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_FCR (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_UART0_set_FCR(U32 data)
{
    m_uart0_fcr.all = data;
    *(volatile U32 *)REG_UART0_FCR = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR] <-- 0x%08x\n",
                        REG_UART0_FCR,data,data);
    #endif
}
U32  GH_UART0_getm_FCR(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR] --> 0x%08x\n",
                        m_uart0_fcr.all);
    #endif
    return m_uart0_fcr.all;
}
void GH_UART0_set_FCR_FIFO_Enable(U8 data)
{
    m_uart0_fcr.bitc.fifo_enable = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_FIFO_Enable] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_FIFO_Enable(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_FIFO_Enable] --> 0x%08x\n",
                        m_uart0_fcr.bitc.fifo_enable);
    #endif
    return m_uart0_fcr.bitc.fifo_enable;
}
void GH_UART0_set_FCR_RCVR_FIFO_Reset(U8 data)
{
    m_uart0_fcr.bitc.rcvr_fifo_reset = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_RCVR_FIFO_Reset] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_RCVR_FIFO_Reset(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_RCVR_FIFO_Reset] --> 0x%08x\n",
                        m_uart0_fcr.bitc.rcvr_fifo_reset);
    #endif
    return m_uart0_fcr.bitc.rcvr_fifo_reset;
}
void GH_UART0_set_FCR_XMIT_FIFO_Reset(U8 data)
{
    m_uart0_fcr.bitc.xmit_fifo_reset = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_XMIT_FIFO_Reset] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_XMIT_FIFO_Reset(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_XMIT_FIFO_Reset] --> 0x%08x\n",
                        m_uart0_fcr.bitc.xmit_fifo_reset);
    #endif
    return m_uart0_fcr.bitc.xmit_fifo_reset;
}
void GH_UART0_set_FCR_DMA_Mode(U8 data)
{
    m_uart0_fcr.bitc.dma_mode = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_DMA_Mode] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_DMA_Mode(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_DMA_Mode] --> 0x%08x\n",
                        m_uart0_fcr.bitc.dma_mode);
    #endif
    return m_uart0_fcr.bitc.dma_mode;
}
void GH_UART0_set_FCR_TX_Empty_Trigger(U8 data)
{
    m_uart0_fcr.bitc.tx_empty_trigger = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_TX_Empty_Trigger] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_TX_Empty_Trigger(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_TX_Empty_Trigger] --> 0x%08x\n",
                        m_uart0_fcr.bitc.tx_empty_trigger);
    #endif
    return m_uart0_fcr.bitc.tx_empty_trigger;
}
void GH_UART0_set_FCR_RCVR_Trigger(U8 data)
{
    m_uart0_fcr.bitc.rcvr_trigger = data;
    *(volatile U32 *)REG_UART0_FCR = m_uart0_fcr.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_FCR_RCVR_Trigger] <-- 0x%08x\n",
                        REG_UART0_FCR,m_uart0_fcr.all,m_uart0_fcr.all);
    #endif
}
U8   GH_UART0_getm_FCR_RCVR_Trigger(void)
{
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "[GH_UART0_getm_FCR_RCVR_Trigger] --> 0x%08x\n",
                        m_uart0_fcr.bitc.rcvr_trigger);
    #endif
    return m_uart0_fcr.bitc.rcvr_trigger;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register UART0_LCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_LCR(U32 data)
{
    *(volatile U32 *)REG_UART0_LCR = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR] <-- 0x%08x\n",
                        REG_UART0_LCR,data,data);
    #endif
}
U32  GH_UART0_get_LCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return value;
}
void GH_UART0_set_LCR_cls(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.cls = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_cls] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_cls(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_cls] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.cls;
}
void GH_UART0_set_LCR_stop(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.stop = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_stop] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_stop(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_stop] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.stop;
}
void GH_UART0_set_LCR_pen(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.pen = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_pen] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_pen(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_pen] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.pen;
}
void GH_UART0_set_LCR_eps(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.eps = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_eps] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_eps(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_eps] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.eps;
}
void GH_UART0_set_LCR_sticky_parity(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.sticky_parity = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_sticky_parity] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_sticky_parity(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_sticky_parity] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.sticky_parity;
}
void GH_UART0_set_LCR_breaks(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.breaks = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_breaks] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_breaks(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_breaks] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.breaks;
}
void GH_UART0_set_LCR_dlab(U8 data)
{
    GH_UART0_LCR_S d;
    d.all = *(volatile U32 *)REG_UART0_LCR;
    d.bitc.dlab = data;
    *(volatile U32 *)REG_UART0_LCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_LCR_dlab] <-- 0x%08x\n",
                        REG_UART0_LCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_LCR_dlab(void)
{
    GH_UART0_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LCR_dlab] --> 0x%08x\n",
                        REG_UART0_LCR,value);
    #endif
    return tmp_value.bitc.dlab;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_MCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_MCR(U32 data)
{
    *(volatile U32 *)REG_UART0_MCR = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR] <-- 0x%08x\n",
                        REG_UART0_MCR,data,data);
    #endif
}
U32  GH_UART0_get_MCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return value;
}
void GH_UART0_set_MCR_dtr(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.dtr = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_dtr] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_dtr(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_dtr] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.dtr;
}
void GH_UART0_set_MCR_rts(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.rts = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_rts] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_rts(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_rts] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.rts;
}
void GH_UART0_set_MCR_out1(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.out1 = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_out1] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_out1(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_out1] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.out1;
}
void GH_UART0_set_MCR_out2(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.out2 = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_out2] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_out2(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_out2] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.out2;
}
void GH_UART0_set_MCR_loopback(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_loopback] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_loopback(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_loopback] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.loopback;
}
void GH_UART0_set_MCR_afce(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.afce = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_afce] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_afce(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_afce] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.afce;
}
void GH_UART0_set_MCR_sire(U8 data)
{
    GH_UART0_MCR_S d;
    d.all = *(volatile U32 *)REG_UART0_MCR;
    d.bitc.sire = data;
    *(volatile U32 *)REG_UART0_MCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_MCR_sire] <-- 0x%08x\n",
                        REG_UART0_MCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_MCR_sire(void)
{
    GH_UART0_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MCR_sire] --> 0x%08x\n",
                        REG_UART0_MCR,value);
    #endif
    return tmp_value.bitc.sire;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_LSR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_UART0_get_LSR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return value;
}
U8   GH_UART0_get_LSR_dr(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_dr] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.dr;
}
U8   GH_UART0_get_LSR_oe(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_oe] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.oe;
}
U8   GH_UART0_get_LSR_pe(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_pe] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.pe;
}
U8   GH_UART0_get_LSR_fe(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_fe] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.fe;
}
U8   GH_UART0_get_LSR_bi(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_bi] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.bi;
}
U8   GH_UART0_get_LSR_temt(void)
{
    GH_UART0_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_LSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_LSR_temt] --> 0x%08x\n",
                        REG_UART0_LSR,value);
    #endif
    return tmp_value.bitc.temt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_MSR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_UART0_get_MSR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return value;
}
U8   GH_UART0_get_MSR_dcts(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_dcts] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.dcts;
}
U8   GH_UART0_get_MSR_ddsr(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_ddsr] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.ddsr;
}
U8   GH_UART0_get_MSR_teri(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_teri] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.teri;
}
U8   GH_UART0_get_MSR_ddcd(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_ddcd] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.ddcd;
}
U8   GH_UART0_get_MSR_cts(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_cts] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.cts;
}
U8   GH_UART0_get_MSR_dsr(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_dsr] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.dsr;
}
U8   GH_UART0_get_MSR_ri(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_ri] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.ri;
}
U8   GH_UART0_get_MSR_dcd(void)
{
    GH_UART0_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_MSR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_MSR_dcd] --> 0x%08x\n",
                        REG_UART0_MSR,value);
    #endif
    return tmp_value.bitc.dcd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART0_SCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_UART0_set_SCR(U32 data)
{
    *(volatile U32 *)REG_UART0_SCR = data;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_SCR] <-- 0x%08x\n",
                        REG_UART0_SCR,data,data);
    #endif
}
U32  GH_UART0_get_SCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART0_SCR);

    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_SCR] --> 0x%08x\n",
                        REG_UART0_SCR,value);
    #endif
    return value;
}
void GH_UART0_set_SCR_scr(U8 data)
{
    GH_UART0_SCR_S d;
    d.all = *(volatile U32 *)REG_UART0_SCR;
    d.bitc.scr = data;
    *(volatile U32 *)REG_UART0_SCR = d.all;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART0_set_SCR_scr] <-- 0x%08x\n",
                        REG_UART0_SCR,d.all,d.all);
    #endif
}
U8   GH_UART0_get_SCR_scr(void)
{
    GH_UART0_SCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART0_SCR);

    tmp_value.all = value;
    #if GH_UART0_ENABLE_DEBUG_PRINT
    GH_UART0_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART0_get_SCR_scr] --> 0x%08x\n",
                        REG_UART0_SCR,value);
    #endif
    return tmp_value.bitc.scr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_UART0_init(void)
{
    GH_UART0_set_THR((U32)0x00000000);
    GH_UART0_set_DLL((U32)0x00000000);
    GH_UART0_set_IER((U32)0x00000000);
    GH_UART0_set_DLH((U32)0x00000000);
    GH_UART0_set_FCR((U32)0x00000000);
    GH_UART0_set_LCR((U32)0x00000000);
    GH_UART0_set_MCR((U32)0x00000000);
    GH_UART0_set_SCR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

