/******************************************************************************
**
** \file      gh_uart1.c
**
** \brief     UART1.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef SRC_INLINE
#include "gh_uart1.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_UART1_RBR_REAL                                  FIO_ADDRESS(UART1,0x7001F000) /* read */
#define REG_UART1_THR_REAL                                  FIO_ADDRESS(UART1,0x7001F000) /* write */
#define REG_UART1_DLL_REAL                                  FIO_ADDRESS(UART1,0x7001F000) /* read/write */
#define REG_UART1_IER_REAL                                  FIO_ADDRESS(UART1,0x7001F004) /* read/write */
#define REG_UART1_DLH_REAL                                  FIO_ADDRESS(UART1,0x7001F004) /* read/write */
#define REG_UART1_IIR_REAL                                  FIO_ADDRESS(UART1,0x7001F008) /* read */
#define REG_UART1_FCR_REAL                                  FIO_ADDRESS(UART1,0x7001F008) /* write */
#define REG_UART1_LCR_REAL                                  FIO_ADDRESS(UART1,0x7001F00C) /* read/write */
#define REG_UART1_MCR_REAL                                  FIO_ADDRESS(UART1,0x7001F010) /* read/write */
#define REG_UART1_LSR_REAL                                  FIO_ADDRESS(UART1,0x7001F014) /* read */
#define REG_UART1_MSR_REAL                                  FIO_ADDRESS(UART1,0x7001F018) /* read */
#define REG_UART1_SCR_REAL                                  FIO_ADDRESS(UART1,0x7001F01C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* UART1_RBR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_RBR_REAL_S;

typedef union { /* UART1_THR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_THR_REAL_S;

typedef union { /* UART1_DLL */
    U32 all;
    struct {
        U32 bauddivint_l                : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_DLL_REAL_S;

typedef union { /* UART1_IER */
    U32 all;
    struct {
        U32 erbfi                       : 1;
        U32 etbei                       : 1;
        U32 elsi                        : 1;
        U32 edssi                       : 1;
        U32                             : 28;
    } bitc;
} GH_UART1_IER_REAL_S;

typedef union { /* UART1_DLH */
    U32 all;
    struct {
        U32 bauddivint_h                : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_DLH_REAL_S;

typedef union { /* UART1_IIR */
    U32 all;
    struct {
        U32 interrupt_id                : 4;
        U32                             : 2;
        U32 fifos_enabled               : 2;
        U32                             : 24;
    } bitc;
} GH_UART1_IIR_REAL_S;

typedef union { /* UART1_FCR */
    U32 all;
    struct {
        U32 fifo_enable                 : 1;
        U32 rcvr_fifo_reset             : 1;
        U32 xmit_fifo_reset             : 1;
        U32 dma_mode                    : 1;
        U32 tx_empty_trigger            : 2;
        U32 rcvr_trigger                : 2;
        U32                             : 24;
    } bitc;
} GH_UART1_FCR_REAL_S;

typedef union { /* UART1_LCR */
    U32 all;
    struct {
        U32 cls                         : 2;
        U32 stop                        : 1;
        U32 pen                         : 1;
        U32 eps                         : 1;
        U32 sticky_parity               : 1;
        U32 breaks                      : 1;
        U32 dlab                        : 1;
        U32                             : 24;
    } bitc;
} GH_UART1_LCR_REAL_S;

typedef union { /* UART1_MCR */
    U32 all;
    struct {
        U32 dtr                         : 1;
        U32 rts                         : 1;
        U32 out1                        : 1;
        U32 out2                        : 1;
        U32 loopback                    : 1;
        U32 afce                        : 1;
        U32 sire                        : 1;
        U32                             : 25;
    } bitc;
} GH_UART1_MCR_REAL_S;

typedef union { /* UART1_LSR */
    U32 all;
    struct {
        U32 dr                          : 1;
        U32 oe                          : 1;
        U32 pe                          : 1;
        U32 fe                          : 1;
        U32 bi                          : 1;
        U32                             : 1;
        U32 temt                        : 1;
        U32                             : 25;
    } bitc;
} GH_UART1_LSR_REAL_S;

typedef union { /* UART1_MSR */
    U32 all;
    struct {
        U32 dcts                        : 1;
        U32 ddsr                        : 1;
        U32 teri                        : 1;
        U32 ddcd                        : 1;
        U32 cts                         : 1;
        U32 dsr                         : 1;
        U32 ri                          : 1;
        U32 dcd                         : 1;
        U32                             : 24;
    } bitc;
} GH_UART1_MSR_REAL_S;

typedef union { /* UART1_SCR */
    U32 all;
    struct {
        U32 scr                         : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_SCR_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_UART1_THR_S                          m_uart1_thr;
GH_UART1_FCR_S                          m_uart1_fcr;

/*----------------------------------------------------------------------------*/
/* register UART1_RBR (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_UART1_get_RBR(void)
{
    GH_UART1_RBR_REAL_S real;
    GH_UART1_RBR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_RBR_REAL);

    dummy.bitc.data = real.bitc.data;
    return dummy.all;
}
GH_INLINE U8   GH_UART1_get_RBR_Data(void)
{
    GH_UART1_RBR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_RBR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register UART1_THR (write)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_THR(U32 data)
{
    m_uart1_thr.all = data;
    GH_UART1_THR_REAL_S real;
    GH_UART1_THR_S dummy;
    dummy.all = data ;
    real.bitc.data = dummy.bitc.data;
    *(volatile U32 *)REG_UART1_THR_REAL = real.all;
}
GH_INLINE U32  GH_UART1_getm_THR(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_THR] --> 0x%08x\n",
                        m_uart1_thr.all);
    #endif
    return m_uart1_thr.all;
}
GH_INLINE void GH_UART1_set_THR_Data(U8 data)
{
    m_uart1_thr.bitc.data = data;
    GH_UART1_THR_REAL_S real;
    real.bitc.data = m_uart1_thr.bitc.data;
    *(volatile U32 *)REG_UART1_THR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_THR_Data(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_THR_Data] --> 0x%08x\n",
                        m_uart1_thr.bitc.data);
    #endif
    return m_uart1_thr.bitc.data;
}

/*----------------------------------------------------------------------------*/
/* register UART1_DLL (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_DLL(U32 data)
{
    GH_UART1_DLL_REAL_S real;
    GH_UART1_DLL_S dummy;
    dummy.all = data ;
    real.bitc.bauddivint_l = dummy.bitc.bauddivint_l;
    *(volatile U32 *)REG_UART1_DLL_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_DLL(void)
{
    GH_UART1_DLL_REAL_S real;
    GH_UART1_DLL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_DLL_REAL);

    dummy.bitc.bauddivint_l = real.bitc.bauddivint_l;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_DLL_BaudDivint_L(U8 data)
{
    GH_UART1_DLL_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_DLL_REAL;
    d.bitc.bauddivint_l = data;
    *(volatile U32 *)REG_UART1_DLL_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_DLL_BaudDivint_L(void)
{
    GH_UART1_DLL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_DLL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bauddivint_l;
}

/*----------------------------------------------------------------------------*/
/* register UART1_IER (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_IER(U32 data)
{
    GH_UART1_IER_REAL_S real;
    GH_UART1_IER_S dummy;
    dummy.all = data ;
    real.bitc.erbfi = dummy.bitc.erbfi;
    real.bitc.etbei = dummy.bitc.etbei;
    real.bitc.elsi = dummy.bitc.elsi;
    real.bitc.edssi = dummy.bitc.edssi;
    *(volatile U32 *)REG_UART1_IER_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_IER(void)
{
    GH_UART1_IER_REAL_S real;
    GH_UART1_IER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_IER_REAL);

    dummy.bitc.erbfi = real.bitc.erbfi;
    dummy.bitc.etbei = real.bitc.etbei;
    dummy.bitc.elsi = real.bitc.elsi;
    dummy.bitc.edssi = real.bitc.edssi;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_IER_erbfi(U8 data)
{
    GH_UART1_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_IER_REAL;
    d.bitc.erbfi = data;
    *(volatile U32 *)REG_UART1_IER_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_IER_erbfi(void)
{
    GH_UART1_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.erbfi;
}
GH_INLINE void GH_UART1_set_IER_etbei(U8 data)
{
    GH_UART1_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_IER_REAL;
    d.bitc.etbei = data;
    *(volatile U32 *)REG_UART1_IER_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_IER_etbei(void)
{
    GH_UART1_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.etbei;
}
GH_INLINE void GH_UART1_set_IER_elsi(U8 data)
{
    GH_UART1_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_IER_REAL;
    d.bitc.elsi = data;
    *(volatile U32 *)REG_UART1_IER_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_IER_elsi(void)
{
    GH_UART1_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.elsi;
}
GH_INLINE void GH_UART1_set_IER_edssi(U8 data)
{
    GH_UART1_IER_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_IER_REAL;
    d.bitc.edssi = data;
    *(volatile U32 *)REG_UART1_IER_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_IER_edssi(void)
{
    GH_UART1_IER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.edssi;
}

/*----------------------------------------------------------------------------*/
/* register UART1_DLH (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_DLH(U32 data)
{
    GH_UART1_DLH_REAL_S real;
    GH_UART1_DLH_S dummy;
    dummy.all = data ;
    real.bitc.bauddivint_h = dummy.bitc.bauddivint_h;
    *(volatile U32 *)REG_UART1_DLH_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_DLH(void)
{
    GH_UART1_DLH_REAL_S real;
    GH_UART1_DLH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_DLH_REAL);

    dummy.bitc.bauddivint_h = real.bitc.bauddivint_h;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_DLH_BaudDivint_H(U8 data)
{
    GH_UART1_DLH_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_DLH_REAL;
    d.bitc.bauddivint_h = data;
    *(volatile U32 *)REG_UART1_DLH_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_DLH_BaudDivint_H(void)
{
    GH_UART1_DLH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_DLH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bauddivint_h;
}

/*----------------------------------------------------------------------------*/
/* register UART1_IIR (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_UART1_get_IIR(void)
{
    GH_UART1_IIR_REAL_S real;
    GH_UART1_IIR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_IIR_REAL);

    dummy.bitc.interrupt_id = real.bitc.interrupt_id;
    dummy.bitc.fifos_enabled = real.bitc.fifos_enabled;
    return dummy.all;
}
GH_INLINE U8   GH_UART1_get_IIR_interrupt_id(void)
{
    GH_UART1_IIR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IIR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.interrupt_id;
}
GH_INLINE U8   GH_UART1_get_IIR_fifos_enabled(void)
{
    GH_UART1_IIR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_IIR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fifos_enabled;
}

/*----------------------------------------------------------------------------*/
/* register UART1_FCR (write)                                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_FCR(U32 data)
{
    m_uart1_fcr.all = data;
    GH_UART1_FCR_REAL_S real;
    GH_UART1_FCR_S dummy;
    dummy.all = data ;
    real.bitc.fifo_enable = dummy.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = dummy.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = dummy.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = dummy.bitc.dma_mode;
    real.bitc.tx_empty_trigger = dummy.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = dummy.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U32  GH_UART1_getm_FCR(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR] --> 0x%08x\n",
                        m_uart1_fcr.all);
    #endif
    return m_uart1_fcr.all;
}
GH_INLINE void GH_UART1_set_FCR_FIFO_Enable(U8 data)
{
    m_uart1_fcr.bitc.fifo_enable = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_FIFO_Enable(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_FIFO_Enable] --> 0x%08x\n",
                        m_uart1_fcr.bitc.fifo_enable);
    #endif
    return m_uart1_fcr.bitc.fifo_enable;
}
GH_INLINE void GH_UART1_set_FCR_RCVR_FIFO_Reset(U8 data)
{
    m_uart1_fcr.bitc.rcvr_fifo_reset = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_RCVR_FIFO_Reset(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_RCVR_FIFO_Reset] --> 0x%08x\n",
                        m_uart1_fcr.bitc.rcvr_fifo_reset);
    #endif
    return m_uart1_fcr.bitc.rcvr_fifo_reset;
}
GH_INLINE void GH_UART1_set_FCR_XMIT_FIFO_Reset(U8 data)
{
    m_uart1_fcr.bitc.xmit_fifo_reset = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_XMIT_FIFO_Reset(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_XMIT_FIFO_Reset] --> 0x%08x\n",
                        m_uart1_fcr.bitc.xmit_fifo_reset);
    #endif
    return m_uart1_fcr.bitc.xmit_fifo_reset;
}
GH_INLINE void GH_UART1_set_FCR_DMA_Mode(U8 data)
{
    m_uart1_fcr.bitc.dma_mode = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_DMA_Mode(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_DMA_Mode] --> 0x%08x\n",
                        m_uart1_fcr.bitc.dma_mode);
    #endif
    return m_uart1_fcr.bitc.dma_mode;
}
GH_INLINE void GH_UART1_set_FCR_TX_Empty_Trigger(U8 data)
{
    m_uart1_fcr.bitc.tx_empty_trigger = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_TX_Empty_Trigger(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_TX_Empty_Trigger] --> 0x%08x\n",
                        m_uart1_fcr.bitc.tx_empty_trigger);
    #endif
    return m_uart1_fcr.bitc.tx_empty_trigger;
}
GH_INLINE void GH_UART1_set_FCR_RCVR_Trigger(U8 data)
{
    m_uart1_fcr.bitc.rcvr_trigger = data;
    GH_UART1_FCR_REAL_S real;
    real.bitc.fifo_enable = m_uart1_fcr.bitc.fifo_enable;
    real.bitc.rcvr_fifo_reset = m_uart1_fcr.bitc.rcvr_fifo_reset;
    real.bitc.xmit_fifo_reset = m_uart1_fcr.bitc.xmit_fifo_reset;
    real.bitc.dma_mode = m_uart1_fcr.bitc.dma_mode;
    real.bitc.tx_empty_trigger = m_uart1_fcr.bitc.tx_empty_trigger;
    real.bitc.rcvr_trigger = m_uart1_fcr.bitc.rcvr_trigger;
    *(volatile U32 *)REG_UART1_FCR_REAL = real.all;
}
GH_INLINE U8   GH_UART1_getm_FCR_RCVR_Trigger(void)
{
    #if GH_UART1_ENABLE_DEBUG_PRINT
    GH_UART1_DEBUG_PRINT_FUNCTION( "[GH_UART1_getm_FCR_RCVR_Trigger] --> 0x%08x\n",
                        m_uart1_fcr.bitc.rcvr_trigger);
    #endif
    return m_uart1_fcr.bitc.rcvr_trigger;
}

/*----------------------------------------------------------------------------*/
/* register UART1_LCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_LCR(U32 data)
{
    GH_UART1_LCR_REAL_S real;
    GH_UART1_LCR_S dummy;
    dummy.all = data ;
    real.bitc.cls = dummy.bitc.cls;
    real.bitc.stop = dummy.bitc.stop;
    real.bitc.pen = dummy.bitc.pen;
    real.bitc.eps = dummy.bitc.eps;
    real.bitc.sticky_parity = dummy.bitc.sticky_parity;
    real.bitc.breaks = dummy.bitc.breaks;
    real.bitc.dlab = dummy.bitc.dlab;
    *(volatile U32 *)REG_UART1_LCR_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_LCR(void)
{
    GH_UART1_LCR_REAL_S real;
    GH_UART1_LCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_LCR_REAL);

    dummy.bitc.cls = real.bitc.cls;
    dummy.bitc.stop = real.bitc.stop;
    dummy.bitc.pen = real.bitc.pen;
    dummy.bitc.eps = real.bitc.eps;
    dummy.bitc.sticky_parity = real.bitc.sticky_parity;
    dummy.bitc.breaks = real.bitc.breaks;
    dummy.bitc.dlab = real.bitc.dlab;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_LCR_cls(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.cls = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_cls(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cls;
}
GH_INLINE void GH_UART1_set_LCR_stop(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.stop = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_stop(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.stop;
}
GH_INLINE void GH_UART1_set_LCR_pen(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.pen = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_pen(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pen;
}
GH_INLINE void GH_UART1_set_LCR_eps(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.eps = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_eps(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.eps;
}
GH_INLINE void GH_UART1_set_LCR_sticky_parity(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.sticky_parity = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_sticky_parity(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sticky_parity;
}
GH_INLINE void GH_UART1_set_LCR_breaks(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.breaks = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_breaks(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.breaks;
}
GH_INLINE void GH_UART1_set_LCR_dlab(U8 data)
{
    GH_UART1_LCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_LCR_REAL;
    d.bitc.dlab = data;
    *(volatile U32 *)REG_UART1_LCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_LCR_dlab(void)
{
    GH_UART1_LCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dlab;
}

/*----------------------------------------------------------------------------*/
/* register UART1_MCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_MCR(U32 data)
{
    GH_UART1_MCR_REAL_S real;
    GH_UART1_MCR_S dummy;
    dummy.all = data ;
    real.bitc.dtr = dummy.bitc.dtr;
    real.bitc.rts = dummy.bitc.rts;
    real.bitc.out1 = dummy.bitc.out1;
    real.bitc.out2 = dummy.bitc.out2;
    real.bitc.loopback = dummy.bitc.loopback;
    real.bitc.afce = dummy.bitc.afce;
    real.bitc.sire = dummy.bitc.sire;
    *(volatile U32 *)REG_UART1_MCR_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_MCR(void)
{
    GH_UART1_MCR_REAL_S real;
    GH_UART1_MCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_MCR_REAL);

    dummy.bitc.dtr = real.bitc.dtr;
    dummy.bitc.rts = real.bitc.rts;
    dummy.bitc.out1 = real.bitc.out1;
    dummy.bitc.out2 = real.bitc.out2;
    dummy.bitc.loopback = real.bitc.loopback;
    dummy.bitc.afce = real.bitc.afce;
    dummy.bitc.sire = real.bitc.sire;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_MCR_dtr(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.dtr = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_dtr(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dtr;
}
GH_INLINE void GH_UART1_set_MCR_rts(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.rts = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_rts(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rts;
}
GH_INLINE void GH_UART1_set_MCR_out1(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.out1 = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_out1(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.out1;
}
GH_INLINE void GH_UART1_set_MCR_out2(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.out2 = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_out2(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.out2;
}
GH_INLINE void GH_UART1_set_MCR_loopback(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_loopback(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.loopback;
}
GH_INLINE void GH_UART1_set_MCR_afce(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.afce = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_afce(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.afce;
}
GH_INLINE void GH_UART1_set_MCR_sire(U8 data)
{
    GH_UART1_MCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_MCR_REAL;
    d.bitc.sire = data;
    *(volatile U32 *)REG_UART1_MCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_MCR_sire(void)
{
    GH_UART1_MCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sire;
}

/*----------------------------------------------------------------------------*/
/* register UART1_LSR (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_UART1_get_LSR(void)
{
    GH_UART1_LSR_REAL_S real;
    GH_UART1_LSR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_LSR_REAL);

    dummy.bitc.dr = real.bitc.dr;
    dummy.bitc.oe = real.bitc.oe;
    dummy.bitc.pe = real.bitc.pe;
    dummy.bitc.fe = real.bitc.fe;
    dummy.bitc.bi = real.bitc.bi;
    dummy.bitc.temt = real.bitc.temt;
    return dummy.all;
}
GH_INLINE U8   GH_UART1_get_LSR_dr(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dr;
}
GH_INLINE U8   GH_UART1_get_LSR_oe(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.oe;
}
GH_INLINE U8   GH_UART1_get_LSR_pe(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pe;
}
GH_INLINE U8   GH_UART1_get_LSR_fe(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fe;
}
GH_INLINE U8   GH_UART1_get_LSR_bi(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.bi;
}
GH_INLINE U8   GH_UART1_get_LSR_temt(void)
{
    GH_UART1_LSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_LSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.temt;
}

/*----------------------------------------------------------------------------*/
/* register UART1_MSR (read)                                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_UART1_get_MSR(void)
{
    GH_UART1_MSR_REAL_S real;
    GH_UART1_MSR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_MSR_REAL);

    dummy.bitc.dcts = real.bitc.dcts;
    dummy.bitc.ddsr = real.bitc.ddsr;
    dummy.bitc.teri = real.bitc.teri;
    dummy.bitc.ddcd = real.bitc.ddcd;
    dummy.bitc.cts = real.bitc.cts;
    dummy.bitc.dsr = real.bitc.dsr;
    dummy.bitc.ri = real.bitc.ri;
    dummy.bitc.dcd = real.bitc.dcd;
    return dummy.all;
}
GH_INLINE U8   GH_UART1_get_MSR_dcts(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dcts;
}
GH_INLINE U8   GH_UART1_get_MSR_ddsr(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ddsr;
}
GH_INLINE U8   GH_UART1_get_MSR_teri(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.teri;
}
GH_INLINE U8   GH_UART1_get_MSR_ddcd(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ddcd;
}
GH_INLINE U8   GH_UART1_get_MSR_cts(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.cts;
}
GH_INLINE U8   GH_UART1_get_MSR_dsr(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dsr;
}
GH_INLINE U8   GH_UART1_get_MSR_ri(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ri;
}
GH_INLINE U8   GH_UART1_get_MSR_dcd(void)
{
    GH_UART1_MSR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_MSR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dcd;
}

/*----------------------------------------------------------------------------*/
/* register UART1_SCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_set_SCR(U32 data)
{
    GH_UART1_SCR_REAL_S real;
    GH_UART1_SCR_S dummy;
    dummy.all = data ;
    real.bitc.scr = dummy.bitc.scr;
    *(volatile U32 *)REG_UART1_SCR_REAL = real.all;
}
GH_INLINE U32  GH_UART1_get_SCR(void)
{
    GH_UART1_SCR_REAL_S real;
    GH_UART1_SCR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_UART1_SCR_REAL);

    dummy.bitc.scr = real.bitc.scr;
    return dummy.all;
}
GH_INLINE void GH_UART1_set_SCR_scr(U8 data)
{
    GH_UART1_SCR_REAL_S d;
    d.all = *(volatile U32 *)REG_UART1_SCR_REAL;
    d.bitc.scr = data;
    *(volatile U32 *)REG_UART1_SCR_REAL = d.all;
}
GH_INLINE U8   GH_UART1_get_SCR_scr(void)
{
    GH_UART1_SCR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART1_SCR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.scr;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_UART1_init(void)
{
    GH_UART1_set_THR((U32)0x00000000);
    GH_UART1_set_DLL((U32)0x00000000);
    GH_UART1_set_IER((U32)0x00000000);
    GH_UART1_set_DLH((U32)0x00000000);
    GH_UART1_set_FCR((U32)0x00000000);
    GH_UART1_set_LCR((U32)0x00000000);
    GH_UART1_set_MCR((U32)0x00000000);
    GH_UART1_set_SCR((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

