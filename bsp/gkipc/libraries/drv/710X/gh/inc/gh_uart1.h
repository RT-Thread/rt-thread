/*!
*******************************************************************************
**
** \file      gh_uart1.h
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
#ifndef _GH_UART1_H
#define _GH_UART1_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_UART1_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_UART1_DEBUG_PRINT_FUNCTION printk
#else
#define GH_UART1_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_UART1_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_UART1_RBR                                       FIO_ADDRESS(UART1,0xa001F000) /* read */
#define REG_UART1_THR                                       FIO_ADDRESS(UART1,0xa001F000) /* write */
#define REG_UART1_DLL                                       FIO_ADDRESS(UART1,0xa001F000) /* read/write */
#define REG_UART1_IER                                       FIO_ADDRESS(UART1,0xa001F004) /* read/write */
#define REG_UART1_DLH                                       FIO_ADDRESS(UART1,0xa001F004) /* read/write */
#define REG_UART1_IIR                                       FIO_ADDRESS(UART1,0xa001F008) /* read */
#define REG_UART1_FCR                                       FIO_ADDRESS(UART1,0xa001F008) /* write */
#define REG_UART1_LCR                                       FIO_ADDRESS(UART1,0xa001F00C) /* read/write */
#define REG_UART1_MCR                                       FIO_ADDRESS(UART1,0xa001F010) /* read/write */
#define REG_UART1_LSR                                       FIO_ADDRESS(UART1,0xa001F014) /* read */
#define REG_UART1_MSR                                       FIO_ADDRESS(UART1,0xa001F018) /* read */
#define REG_UART1_SCR                                       FIO_ADDRESS(UART1,0xa001F01C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* UART1_RBR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_RBR_S;

typedef union { /* UART1_THR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_THR_S;

typedef union { /* UART1_DLL */
    U32 all;
    struct {
        U32 bauddivint_l                : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_DLL_S;

typedef union { /* UART1_IER */
    U32 all;
    struct {
        U32 erbfi                       : 1;
        U32 etbei                       : 1;
        U32 elsi                        : 1;
        U32 edssi                       : 1;
        U32                             : 28;
    } bitc;
} GH_UART1_IER_S;

typedef union { /* UART1_DLH */
    U32 all;
    struct {
        U32 bauddivint_h                : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_DLH_S;

typedef union { /* UART1_IIR */
    U32 all;
    struct {
        U32 interrupt_id                : 4;
        U32                             : 2;
        U32 fifos_enabled               : 2;
        U32                             : 24;
    } bitc;
} GH_UART1_IIR_S;

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
} GH_UART1_FCR_S;

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
} GH_UART1_LCR_S;

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
} GH_UART1_MCR_S;

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
} GH_UART1_LSR_S;

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
} GH_UART1_MSR_S;

typedef union { /* UART1_SCR */
    U32 all;
    struct {
        U32 scr                         : 8;
        U32                             : 24;
    } bitc;
} GH_UART1_SCR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_UART1_THR_S                          m_uart1_thr;
extern GH_UART1_FCR_S                          m_uart1_fcr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register UART1_RBR (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'UART1_RBR'. */
U32  GH_UART1_get_RBR(void);
/*! \brief Reads the bit group 'Data' of register 'UART1_RBR'. */
U8   GH_UART1_get_RBR_Data(void);

/*----------------------------------------------------------------------------*/
/* register UART1_THR (write)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_THR'. */
void GH_UART1_set_THR(U32 data);
/*! \brief Reads the mirror variable of the register 'UART1_THR'. */
U32  GH_UART1_getm_THR(void);
/*! \brief Writes the bit group 'Data' of register 'UART1_THR'. */
void GH_UART1_set_THR_Data(U8 data);
/*! \brief Reads the bit group 'Data' from the mirror variable of register 'UART1_THR'. */
U8   GH_UART1_getm_THR_Data(void);

/*----------------------------------------------------------------------------*/
/* register UART1_DLL (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_DLL'. */
void GH_UART1_set_DLL(U32 data);
/*! \brief Reads the register 'UART1_DLL'. */
U32  GH_UART1_get_DLL(void);
/*! \brief Writes the bit group 'BaudDivint_L' of register 'UART1_DLL'. */
void GH_UART1_set_DLL_BaudDivint_L(U8 data);
/*! \brief Reads the bit group 'BaudDivint_L' of register 'UART1_DLL'. */
U8   GH_UART1_get_DLL_BaudDivint_L(void);

/*----------------------------------------------------------------------------*/
/* register UART1_IER (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_IER'. */
void GH_UART1_set_IER(U32 data);
/*! \brief Reads the register 'UART1_IER'. */
U32  GH_UART1_get_IER(void);
/*! \brief Writes the bit group 'erbfi' of register 'UART1_IER'. */
void GH_UART1_set_IER_erbfi(U8 data);
/*! \brief Reads the bit group 'erbfi' of register 'UART1_IER'. */
U8   GH_UART1_get_IER_erbfi(void);
/*! \brief Writes the bit group 'etbei' of register 'UART1_IER'. */
void GH_UART1_set_IER_etbei(U8 data);
/*! \brief Reads the bit group 'etbei' of register 'UART1_IER'. */
U8   GH_UART1_get_IER_etbei(void);
/*! \brief Writes the bit group 'elsi' of register 'UART1_IER'. */
void GH_UART1_set_IER_elsi(U8 data);
/*! \brief Reads the bit group 'elsi' of register 'UART1_IER'. */
U8   GH_UART1_get_IER_elsi(void);
/*! \brief Writes the bit group 'edssi' of register 'UART1_IER'. */
void GH_UART1_set_IER_edssi(U8 data);
/*! \brief Reads the bit group 'edssi' of register 'UART1_IER'. */
U8   GH_UART1_get_IER_edssi(void);

/*----------------------------------------------------------------------------*/
/* register UART1_DLH (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_DLH'. */
void GH_UART1_set_DLH(U32 data);
/*! \brief Reads the register 'UART1_DLH'. */
U32  GH_UART1_get_DLH(void);
/*! \brief Writes the bit group 'BaudDivint_H' of register 'UART1_DLH'. */
void GH_UART1_set_DLH_BaudDivint_H(U8 data);
/*! \brief Reads the bit group 'BaudDivint_H' of register 'UART1_DLH'. */
U8   GH_UART1_get_DLH_BaudDivint_H(void);

/*----------------------------------------------------------------------------*/
/* register UART1_IIR (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'UART1_IIR'. */
U32  GH_UART1_get_IIR(void);
/*! \brief Reads the bit group 'interrupt_id' of register 'UART1_IIR'. */
U8   GH_UART1_get_IIR_interrupt_id(void);
/*! \brief Reads the bit group 'fifos_enabled' of register 'UART1_IIR'. */
U8   GH_UART1_get_IIR_fifos_enabled(void);

/*----------------------------------------------------------------------------*/
/* register UART1_FCR (write)                                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_FCR'. */
void GH_UART1_set_FCR(U32 data);
/*! \brief Reads the mirror variable of the register 'UART1_FCR'. */
U32  GH_UART1_getm_FCR(void);
/*! \brief Writes the bit group 'FIFO_Enable' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_FIFO_Enable(U8 data);
/*! \brief Reads the bit group 'FIFO_Enable' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_FIFO_Enable(void);
/*! \brief Writes the bit group 'RCVR_FIFO_Reset' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_RCVR_FIFO_Reset(U8 data);
/*! \brief Reads the bit group 'RCVR_FIFO_Reset' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_RCVR_FIFO_Reset(void);
/*! \brief Writes the bit group 'XMIT_FIFO_Reset' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_XMIT_FIFO_Reset(U8 data);
/*! \brief Reads the bit group 'XMIT_FIFO_Reset' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_XMIT_FIFO_Reset(void);
/*! \brief Writes the bit group 'DMA_Mode' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_DMA_Mode(U8 data);
/*! \brief Reads the bit group 'DMA_Mode' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_DMA_Mode(void);
/*! \brief Writes the bit group 'TX_Empty_Trigger' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_TX_Empty_Trigger(U8 data);
/*! \brief Reads the bit group 'TX_Empty_Trigger' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_TX_Empty_Trigger(void);
/*! \brief Writes the bit group 'RCVR_Trigger' of register 'UART1_FCR'. */
void GH_UART1_set_FCR_RCVR_Trigger(U8 data);
/*! \brief Reads the bit group 'RCVR_Trigger' from the mirror variable of register 'UART1_FCR'. */
U8   GH_UART1_getm_FCR_RCVR_Trigger(void);

/*----------------------------------------------------------------------------*/
/* register UART1_LCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_LCR'. */
void GH_UART1_set_LCR(U32 data);
/*! \brief Reads the register 'UART1_LCR'. */
U32  GH_UART1_get_LCR(void);
/*! \brief Writes the bit group 'cls' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_cls(U8 data);
/*! \brief Reads the bit group 'cls' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_cls(void);
/*! \brief Writes the bit group 'stop' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_stop(U8 data);
/*! \brief Reads the bit group 'stop' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_stop(void);
/*! \brief Writes the bit group 'pen' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_pen(U8 data);
/*! \brief Reads the bit group 'pen' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_pen(void);
/*! \brief Writes the bit group 'eps' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_eps(U8 data);
/*! \brief Reads the bit group 'eps' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_eps(void);
/*! \brief Writes the bit group 'sticky_parity' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_sticky_parity(U8 data);
/*! \brief Reads the bit group 'sticky_parity' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_sticky_parity(void);
/*! \brief Writes the bit group 'breaks' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_breaks(U8 data);
/*! \brief Reads the bit group 'breaks' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_breaks(void);
/*! \brief Writes the bit group 'dlab' of register 'UART1_LCR'. */
void GH_UART1_set_LCR_dlab(U8 data);
/*! \brief Reads the bit group 'dlab' of register 'UART1_LCR'. */
U8   GH_UART1_get_LCR_dlab(void);

/*----------------------------------------------------------------------------*/
/* register UART1_MCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_MCR'. */
void GH_UART1_set_MCR(U32 data);
/*! \brief Reads the register 'UART1_MCR'. */
U32  GH_UART1_get_MCR(void);
/*! \brief Writes the bit group 'dtr' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_dtr(U8 data);
/*! \brief Reads the bit group 'dtr' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_dtr(void);
/*! \brief Writes the bit group 'rts' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_rts(U8 data);
/*! \brief Reads the bit group 'rts' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_rts(void);
/*! \brief Writes the bit group 'out1' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_out1(U8 data);
/*! \brief Reads the bit group 'out1' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_out1(void);
/*! \brief Writes the bit group 'out2' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_out2(U8 data);
/*! \brief Reads the bit group 'out2' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_out2(void);
/*! \brief Writes the bit group 'loopback' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_loopback(void);
/*! \brief Writes the bit group 'afce' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_afce(U8 data);
/*! \brief Reads the bit group 'afce' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_afce(void);
/*! \brief Writes the bit group 'sire' of register 'UART1_MCR'. */
void GH_UART1_set_MCR_sire(U8 data);
/*! \brief Reads the bit group 'sire' of register 'UART1_MCR'. */
U8   GH_UART1_get_MCR_sire(void);

/*----------------------------------------------------------------------------*/
/* register UART1_LSR (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'UART1_LSR'. */
U32  GH_UART1_get_LSR(void);
/*! \brief Reads the bit group 'dr' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_dr(void);
/*! \brief Reads the bit group 'oe' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_oe(void);
/*! \brief Reads the bit group 'pe' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_pe(void);
/*! \brief Reads the bit group 'fe' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_fe(void);
/*! \brief Reads the bit group 'bi' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_bi(void);
/*! \brief Reads the bit group 'temt' of register 'UART1_LSR'. */
U8   GH_UART1_get_LSR_temt(void);

/*----------------------------------------------------------------------------*/
/* register UART1_MSR (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'UART1_MSR'. */
U32  GH_UART1_get_MSR(void);
/*! \brief Reads the bit group 'dcts' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_dcts(void);
/*! \brief Reads the bit group 'ddsr' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_ddsr(void);
/*! \brief Reads the bit group 'teri' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_teri(void);
/*! \brief Reads the bit group 'ddcd' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_ddcd(void);
/*! \brief Reads the bit group 'cts' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_cts(void);
/*! \brief Reads the bit group 'dsr' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_dsr(void);
/*! \brief Reads the bit group 'ri' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_ri(void);
/*! \brief Reads the bit group 'dcd' of register 'UART1_MSR'. */
U8   GH_UART1_get_MSR_dcd(void);

/*----------------------------------------------------------------------------*/
/* register UART1_SCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'UART1_SCR'. */
void GH_UART1_set_SCR(U32 data);
/*! \brief Reads the register 'UART1_SCR'. */
U32  GH_UART1_get_SCR(void);
/*! \brief Writes the bit group 'scr' of register 'UART1_SCR'. */
void GH_UART1_set_SCR_scr(U8 data);
/*! \brief Reads the bit group 'scr' of register 'UART1_SCR'. */
U8   GH_UART1_get_SCR_scr(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_UART1_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_uart1.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_UART1_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

