/*!
*******************************************************************************
**
** \file      gh_uart2.h
**
** \brief     UART2.
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
#ifndef _GH_UART2_H
#define _GH_UART2_H

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

#define GH_UART2_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_UART2_DEBUG_PRINT_FUNCTION printk
#else
#define GH_UART2_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_UART2_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_UART2_RBR                                       FIO_ADDRESS(UART2,0xA001E000) /* read */
#define REG_UART2_THR                                       FIO_ADDRESS(UART2,0xA001E000) /* write */
#define REG_UART2_DLL                                       FIO_ADDRESS(UART2,0xA001E000) /* read/write */
#define REG_UART2_IER                                       FIO_ADDRESS(UART2,0xA001E004) /* read/write */
#define REG_UART2_DLH                                       FIO_ADDRESS(UART2,0xA001E004) /* read/write */
#define REG_UART2_IIR                                       FIO_ADDRESS(UART2,0xA001E008) /* read */
#define REG_UART2_FCR                                       FIO_ADDRESS(UART2,0xA001E008) /* write */
#define REG_UART2_LCR                                       FIO_ADDRESS(UART2,0xA001E00C) /* read/write */
#define REG_UART2_MCR                                       FIO_ADDRESS(UART2,0xA001E010) /* read/write */
#define REG_UART2_LSR                                       FIO_ADDRESS(UART2,0xA001E014) /* read */
#define REG_UART2_MSR                                       FIO_ADDRESS(UART2,0xA001E018) /* read */
#define REG_UART2_SCR                                       FIO_ADDRESS(UART2,0xA001E01C) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* UART2_RBR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART2_RBR_S;

typedef union { /* UART2_THR */
    U32 all;
    struct {
        U32 data                        : 8;
        U32                             : 24;
    } bitc;
} GH_UART2_THR_S;

typedef union { /* UART2_DLL */
    U32 all;
    struct {
        U32 bauddivint_l                : 8;
        U32                             : 24;
    } bitc;
} GH_UART2_DLL_S;

typedef union { /* UART2_IER */
    U32 all;
    struct {
        U32 erbfi                       : 1;
        U32 etbei                       : 1;
        U32 elsi                        : 1;
        U32 edssi                       : 1;
        U32                             : 28;
    } bitc;
} GH_UART2_IER_S;

typedef union { /* UART2_DLH */
    U32 all;
    struct {
        U32 bauddivint_h                : 8;
        U32                             : 24;
    } bitc;
} GH_UART2_DLH_S;

typedef union { /* UART2_IIR */
    U32 all;
    struct {
        U32 interrupt_id                : 4;
        U32                             : 2;
        U32 fifos_enabled               : 2;
        U32                             : 24;
    } bitc;
} GH_UART2_IIR_S;

typedef union { /* UART2_FCR */
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
} GH_UART2_FCR_S;

typedef union { /* UART2_LCR */
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
} GH_UART2_LCR_S;

typedef union { /* UART2_MCR */
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
} GH_UART2_MCR_S;

typedef union { /* UART2_LSR */
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
} GH_UART2_LSR_S;

typedef union { /* UART2_MSR */
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
} GH_UART2_MSR_S;

typedef union { /* UART2_SCR */
    U32 all;
    struct {
        U32 scr                         : 8;
        U32                             : 24;
    } bitc;
} GH_UART2_SCR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_UART2_THR_S                          m_uart2_thr;
extern GH_UART2_FCR_S                          m_uart2_fcr;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register UART2_RBR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'UART2_RBR'. */
U32  GH_UART2_get_RBR(void);
/*! \brief Reads the bit group 'Data' of register 'UART2_RBR'. */
U8   GH_UART2_get_RBR_Data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_UART2_get_RBR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_RBR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_RBR] --> 0x%08x\n",
                        REG_UART2_RBR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_UART2_get_RBR_Data(void)
{
    GH_UART2_RBR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_RBR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_RBR_Data] --> 0x%08x\n",
                        REG_UART2_RBR,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_THR (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'UART2_THR'. */
void GH_UART2_set_THR(U32 data);
/*! \brief Reads the mirror variable of the register 'UART2_THR'. */
U32  GH_UART2_getm_THR(void);
/*! \brief Writes the bit group 'Data' of register 'UART2_THR'. */
void GH_UART2_set_THR_Data(U8 data);
/*! \brief Reads the bit group 'Data' from the mirror variable of register 'UART2_THR'. */
U8   GH_UART2_getm_THR_Data(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_UART2_set_THR(U32 data)
{
    m_uart2_thr.all = data;
    *(volatile U32 *)REG_UART2_THR = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_THR] <-- 0x%08x\n",
                        REG_UART2_THR,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_getm_THR(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_THR] --> 0x%08x\n",
                        m_uart2_thr.all);
    #endif
    return m_uart2_thr.all;
}
GH_INLINE void GH_UART2_set_THR_Data(U8 data)
{
    m_uart2_thr.bitc.data = data;
    *(volatile U32 *)REG_UART2_THR = m_uart2_thr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_THR_Data] <-- 0x%08x\n",
                        REG_UART2_THR,m_uart2_thr.all,m_uart2_thr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_THR_Data(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_THR_Data] --> 0x%08x\n",
                        m_uart2_thr.bitc.data);
    #endif
    return m_uart2_thr.bitc.data;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register UART2_DLL (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_DLL'. */
void GH_UART2_set_DLL(U32 data);
/*! \brief Reads the register 'UART2_DLL'. */
U32  GH_UART2_get_DLL(void);
/*! \brief Writes the bit group 'BaudDivint_L' of register 'UART2_DLL'. */
void GH_UART2_set_DLL_BaudDivint_L(U8 data);
/*! \brief Reads the bit group 'BaudDivint_L' of register 'UART2_DLL'. */
U8   GH_UART2_get_DLL_BaudDivint_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_DLL(U32 data)
{
    *(volatile U32 *)REG_UART2_DLL = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_DLL] <-- 0x%08x\n",
                        REG_UART2_DLL,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_DLL(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_DLL);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_DLL] --> 0x%08x\n",
                        REG_UART2_DLL,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_DLL_BaudDivint_L(U8 data)
{
    GH_UART2_DLL_S d;
    d.all = *(volatile U32 *)REG_UART2_DLL;
    d.bitc.bauddivint_l = data;
    *(volatile U32 *)REG_UART2_DLL = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_DLL_BaudDivint_L] <-- 0x%08x\n",
                        REG_UART2_DLL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_DLL_BaudDivint_L(void)
{
    GH_UART2_DLL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_DLL);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_DLL_BaudDivint_L] --> 0x%08x\n",
                        REG_UART2_DLL,value);
    #endif
    return tmp_value.bitc.bauddivint_l;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_IER (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_IER'. */
void GH_UART2_set_IER(U32 data);
/*! \brief Reads the register 'UART2_IER'. */
U32  GH_UART2_get_IER(void);
/*! \brief Writes the bit group 'erbfi' of register 'UART2_IER'. */
void GH_UART2_set_IER_erbfi(U8 data);
/*! \brief Reads the bit group 'erbfi' of register 'UART2_IER'. */
U8   GH_UART2_get_IER_erbfi(void);
/*! \brief Writes the bit group 'etbei' of register 'UART2_IER'. */
void GH_UART2_set_IER_etbei(U8 data);
/*! \brief Reads the bit group 'etbei' of register 'UART2_IER'. */
U8   GH_UART2_get_IER_etbei(void);
/*! \brief Writes the bit group 'elsi' of register 'UART2_IER'. */
void GH_UART2_set_IER_elsi(U8 data);
/*! \brief Reads the bit group 'elsi' of register 'UART2_IER'. */
U8   GH_UART2_get_IER_elsi(void);
/*! \brief Writes the bit group 'edssi' of register 'UART2_IER'. */
void GH_UART2_set_IER_edssi(U8 data);
/*! \brief Reads the bit group 'edssi' of register 'UART2_IER'. */
U8   GH_UART2_get_IER_edssi(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_IER(U32 data)
{
    *(volatile U32 *)REG_UART2_IER = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_IER] <-- 0x%08x\n",
                        REG_UART2_IER,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_IER(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_IER);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IER] --> 0x%08x\n",
                        REG_UART2_IER,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_IER_erbfi(U8 data)
{
    GH_UART2_IER_S d;
    d.all = *(volatile U32 *)REG_UART2_IER;
    d.bitc.erbfi = data;
    *(volatile U32 *)REG_UART2_IER = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_IER_erbfi] <-- 0x%08x\n",
                        REG_UART2_IER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_IER_erbfi(void)
{
    GH_UART2_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IER);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IER_erbfi] --> 0x%08x\n",
                        REG_UART2_IER,value);
    #endif
    return tmp_value.bitc.erbfi;
}
GH_INLINE void GH_UART2_set_IER_etbei(U8 data)
{
    GH_UART2_IER_S d;
    d.all = *(volatile U32 *)REG_UART2_IER;
    d.bitc.etbei = data;
    *(volatile U32 *)REG_UART2_IER = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_IER_etbei] <-- 0x%08x\n",
                        REG_UART2_IER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_IER_etbei(void)
{
    GH_UART2_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IER);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IER_etbei] --> 0x%08x\n",
                        REG_UART2_IER,value);
    #endif
    return tmp_value.bitc.etbei;
}
GH_INLINE void GH_UART2_set_IER_elsi(U8 data)
{
    GH_UART2_IER_S d;
    d.all = *(volatile U32 *)REG_UART2_IER;
    d.bitc.elsi = data;
    *(volatile U32 *)REG_UART2_IER = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_IER_elsi] <-- 0x%08x\n",
                        REG_UART2_IER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_IER_elsi(void)
{
    GH_UART2_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IER);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IER_elsi] --> 0x%08x\n",
                        REG_UART2_IER,value);
    #endif
    return tmp_value.bitc.elsi;
}
GH_INLINE void GH_UART2_set_IER_edssi(U8 data)
{
    GH_UART2_IER_S d;
    d.all = *(volatile U32 *)REG_UART2_IER;
    d.bitc.edssi = data;
    *(volatile U32 *)REG_UART2_IER = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_IER_edssi] <-- 0x%08x\n",
                        REG_UART2_IER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_IER_edssi(void)
{
    GH_UART2_IER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IER);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IER_edssi] --> 0x%08x\n",
                        REG_UART2_IER,value);
    #endif
    return tmp_value.bitc.edssi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_DLH (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_DLH'. */
void GH_UART2_set_DLH(U32 data);
/*! \brief Reads the register 'UART2_DLH'. */
U32  GH_UART2_get_DLH(void);
/*! \brief Writes the bit group 'BaudDivint_H' of register 'UART2_DLH'. */
void GH_UART2_set_DLH_BaudDivint_H(U8 data);
/*! \brief Reads the bit group 'BaudDivint_H' of register 'UART2_DLH'. */
U8   GH_UART2_get_DLH_BaudDivint_H(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_DLH(U32 data)
{
    *(volatile U32 *)REG_UART2_DLH = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_DLH] <-- 0x%08x\n",
                        REG_UART2_DLH,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_DLH(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_DLH);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_DLH] --> 0x%08x\n",
                        REG_UART2_DLH,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_DLH_BaudDivint_H(U8 data)
{
    GH_UART2_DLH_S d;
    d.all = *(volatile U32 *)REG_UART2_DLH;
    d.bitc.bauddivint_h = data;
    *(volatile U32 *)REG_UART2_DLH = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_DLH_BaudDivint_H] <-- 0x%08x\n",
                        REG_UART2_DLH,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_DLH_BaudDivint_H(void)
{
    GH_UART2_DLH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_DLH);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_DLH_BaudDivint_H] --> 0x%08x\n",
                        REG_UART2_DLH,value);
    #endif
    return tmp_value.bitc.bauddivint_h;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_IIR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'UART2_IIR'. */
U32  GH_UART2_get_IIR(void);
/*! \brief Reads the bit group 'interrupt_id' of register 'UART2_IIR'. */
U8   GH_UART2_get_IIR_interrupt_id(void);
/*! \brief Reads the bit group 'fifos_enabled' of register 'UART2_IIR'. */
U8   GH_UART2_get_IIR_fifos_enabled(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_UART2_get_IIR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_IIR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IIR] --> 0x%08x\n",
                        REG_UART2_IIR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_UART2_get_IIR_interrupt_id(void)
{
    GH_UART2_IIR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IIR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IIR_interrupt_id] --> 0x%08x\n",
                        REG_UART2_IIR,value);
    #endif
    return tmp_value.bitc.interrupt_id;
}
GH_INLINE U8   GH_UART2_get_IIR_fifos_enabled(void)
{
    GH_UART2_IIR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_IIR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_IIR_fifos_enabled] --> 0x%08x\n",
                        REG_UART2_IIR,value);
    #endif
    return tmp_value.bitc.fifos_enabled;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_FCR (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'UART2_FCR'. */
void GH_UART2_set_FCR(U32 data);
/*! \brief Reads the mirror variable of the register 'UART2_FCR'. */
U32  GH_UART2_getm_FCR(void);
/*! \brief Writes the bit group 'FIFO_Enable' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_FIFO_Enable(U8 data);
/*! \brief Reads the bit group 'FIFO_Enable' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_FIFO_Enable(void);
/*! \brief Writes the bit group 'RCVR_FIFO_Reset' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_RCVR_FIFO_Reset(U8 data);
/*! \brief Reads the bit group 'RCVR_FIFO_Reset' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_RCVR_FIFO_Reset(void);
/*! \brief Writes the bit group 'XMIT_FIFO_Reset' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_XMIT_FIFO_Reset(U8 data);
/*! \brief Reads the bit group 'XMIT_FIFO_Reset' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_XMIT_FIFO_Reset(void);
/*! \brief Writes the bit group 'DMA_Mode' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_DMA_Mode(U8 data);
/*! \brief Reads the bit group 'DMA_Mode' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_DMA_Mode(void);
/*! \brief Writes the bit group 'TX_Empty_Trigger' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_TX_Empty_Trigger(U8 data);
/*! \brief Reads the bit group 'TX_Empty_Trigger' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_TX_Empty_Trigger(void);
/*! \brief Writes the bit group 'RCVR_Trigger' of register 'UART2_FCR'. */
void GH_UART2_set_FCR_RCVR_Trigger(U8 data);
/*! \brief Reads the bit group 'RCVR_Trigger' from the mirror variable of register 'UART2_FCR'. */
U8   GH_UART2_getm_FCR_RCVR_Trigger(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_UART2_set_FCR(U32 data)
{
    m_uart2_fcr.all = data;
    *(volatile U32 *)REG_UART2_FCR = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR] <-- 0x%08x\n",
                        REG_UART2_FCR,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_getm_FCR(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR] --> 0x%08x\n",
                        m_uart2_fcr.all);
    #endif
    return m_uart2_fcr.all;
}
GH_INLINE void GH_UART2_set_FCR_FIFO_Enable(U8 data)
{
    m_uart2_fcr.bitc.fifo_enable = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_FIFO_Enable] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_FIFO_Enable(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_FIFO_Enable] --> 0x%08x\n",
                        m_uart2_fcr.bitc.fifo_enable);
    #endif
    return m_uart2_fcr.bitc.fifo_enable;
}
GH_INLINE void GH_UART2_set_FCR_RCVR_FIFO_Reset(U8 data)
{
    m_uart2_fcr.bitc.rcvr_fifo_reset = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_RCVR_FIFO_Reset] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_RCVR_FIFO_Reset(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_RCVR_FIFO_Reset] --> 0x%08x\n",
                        m_uart2_fcr.bitc.rcvr_fifo_reset);
    #endif
    return m_uart2_fcr.bitc.rcvr_fifo_reset;
}
GH_INLINE void GH_UART2_set_FCR_XMIT_FIFO_Reset(U8 data)
{
    m_uart2_fcr.bitc.xmit_fifo_reset = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_XMIT_FIFO_Reset] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_XMIT_FIFO_Reset(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_XMIT_FIFO_Reset] --> 0x%08x\n",
                        m_uart2_fcr.bitc.xmit_fifo_reset);
    #endif
    return m_uart2_fcr.bitc.xmit_fifo_reset;
}
GH_INLINE void GH_UART2_set_FCR_DMA_Mode(U8 data)
{
    m_uart2_fcr.bitc.dma_mode = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_DMA_Mode] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_DMA_Mode(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_DMA_Mode] --> 0x%08x\n",
                        m_uart2_fcr.bitc.dma_mode);
    #endif
    return m_uart2_fcr.bitc.dma_mode;
}
GH_INLINE void GH_UART2_set_FCR_TX_Empty_Trigger(U8 data)
{
    m_uart2_fcr.bitc.tx_empty_trigger = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_TX_Empty_Trigger] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_TX_Empty_Trigger(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_TX_Empty_Trigger] --> 0x%08x\n",
                        m_uart2_fcr.bitc.tx_empty_trigger);
    #endif
    return m_uart2_fcr.bitc.tx_empty_trigger;
}
GH_INLINE void GH_UART2_set_FCR_RCVR_Trigger(U8 data)
{
    m_uart2_fcr.bitc.rcvr_trigger = data;
    *(volatile U32 *)REG_UART2_FCR = m_uart2_fcr.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_FCR_RCVR_Trigger] <-- 0x%08x\n",
                        REG_UART2_FCR,m_uart2_fcr.all,m_uart2_fcr.all);
    #endif
}
GH_INLINE U8   GH_UART2_getm_FCR_RCVR_Trigger(void)
{
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "[GH_UART2_getm_FCR_RCVR_Trigger] --> 0x%08x\n",
                        m_uart2_fcr.bitc.rcvr_trigger);
    #endif
    return m_uart2_fcr.bitc.rcvr_trigger;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register UART2_LCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_LCR'. */
void GH_UART2_set_LCR(U32 data);
/*! \brief Reads the register 'UART2_LCR'. */
U32  GH_UART2_get_LCR(void);
/*! \brief Writes the bit group 'cls' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_cls(U8 data);
/*! \brief Reads the bit group 'cls' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_cls(void);
/*! \brief Writes the bit group 'stop' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_stop(U8 data);
/*! \brief Reads the bit group 'stop' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_stop(void);
/*! \brief Writes the bit group 'pen' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_pen(U8 data);
/*! \brief Reads the bit group 'pen' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_pen(void);
/*! \brief Writes the bit group 'eps' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_eps(U8 data);
/*! \brief Reads the bit group 'eps' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_eps(void);
/*! \brief Writes the bit group 'sticky_parity' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_sticky_parity(U8 data);
/*! \brief Reads the bit group 'sticky_parity' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_sticky_parity(void);
/*! \brief Writes the bit group 'breaks' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_breaks(U8 data);
/*! \brief Reads the bit group 'breaks' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_breaks(void);
/*! \brief Writes the bit group 'dlab' of register 'UART2_LCR'. */
void GH_UART2_set_LCR_dlab(U8 data);
/*! \brief Reads the bit group 'dlab' of register 'UART2_LCR'. */
U8   GH_UART2_get_LCR_dlab(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_LCR(U32 data)
{
    *(volatile U32 *)REG_UART2_LCR = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR] <-- 0x%08x\n",
                        REG_UART2_LCR,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_LCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_LCR_cls(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.cls = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_cls] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_cls(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_cls] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.cls;
}
GH_INLINE void GH_UART2_set_LCR_stop(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.stop = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_stop] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_stop(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_stop] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.stop;
}
GH_INLINE void GH_UART2_set_LCR_pen(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.pen = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_pen] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_pen(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_pen] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.pen;
}
GH_INLINE void GH_UART2_set_LCR_eps(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.eps = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_eps] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_eps(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_eps] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.eps;
}
GH_INLINE void GH_UART2_set_LCR_sticky_parity(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.sticky_parity = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_sticky_parity] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_sticky_parity(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_sticky_parity] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.sticky_parity;
}
GH_INLINE void GH_UART2_set_LCR_breaks(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.breaks = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_breaks] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_breaks(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_breaks] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.breaks;
}
GH_INLINE void GH_UART2_set_LCR_dlab(U8 data)
{
    GH_UART2_LCR_S d;
    d.all = *(volatile U32 *)REG_UART2_LCR;
    d.bitc.dlab = data;
    *(volatile U32 *)REG_UART2_LCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_LCR_dlab] <-- 0x%08x\n",
                        REG_UART2_LCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_LCR_dlab(void)
{
    GH_UART2_LCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LCR_dlab] --> 0x%08x\n",
                        REG_UART2_LCR,value);
    #endif
    return tmp_value.bitc.dlab;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_MCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_MCR'. */
void GH_UART2_set_MCR(U32 data);
/*! \brief Reads the register 'UART2_MCR'. */
U32  GH_UART2_get_MCR(void);
/*! \brief Writes the bit group 'dtr' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_dtr(U8 data);
/*! \brief Reads the bit group 'dtr' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_dtr(void);
/*! \brief Writes the bit group 'rts' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_rts(U8 data);
/*! \brief Reads the bit group 'rts' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_rts(void);
/*! \brief Writes the bit group 'out1' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_out1(U8 data);
/*! \brief Reads the bit group 'out1' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_out1(void);
/*! \brief Writes the bit group 'out2' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_out2(U8 data);
/*! \brief Reads the bit group 'out2' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_out2(void);
/*! \brief Writes the bit group 'loopback' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_loopback(void);
/*! \brief Writes the bit group 'afce' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_afce(U8 data);
/*! \brief Reads the bit group 'afce' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_afce(void);
/*! \brief Writes the bit group 'sire' of register 'UART2_MCR'. */
void GH_UART2_set_MCR_sire(U8 data);
/*! \brief Reads the bit group 'sire' of register 'UART2_MCR'. */
U8   GH_UART2_get_MCR_sire(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_MCR(U32 data)
{
    *(volatile U32 *)REG_UART2_MCR = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR] <-- 0x%08x\n",
                        REG_UART2_MCR,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_MCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_MCR_dtr(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.dtr = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_dtr] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_dtr(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_dtr] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.dtr;
}
GH_INLINE void GH_UART2_set_MCR_rts(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.rts = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_rts] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_rts(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_rts] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.rts;
}
GH_INLINE void GH_UART2_set_MCR_out1(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.out1 = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_out1] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_out1(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_out1] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.out1;
}
GH_INLINE void GH_UART2_set_MCR_out2(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.out2 = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_out2] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_out2(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_out2] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.out2;
}
GH_INLINE void GH_UART2_set_MCR_loopback(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_loopback] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_loopback(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_loopback] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.loopback;
}
GH_INLINE void GH_UART2_set_MCR_afce(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.afce = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_afce] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_afce(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_afce] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.afce;
}
GH_INLINE void GH_UART2_set_MCR_sire(U8 data)
{
    GH_UART2_MCR_S d;
    d.all = *(volatile U32 *)REG_UART2_MCR;
    d.bitc.sire = data;
    *(volatile U32 *)REG_UART2_MCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_MCR_sire] <-- 0x%08x\n",
                        REG_UART2_MCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_MCR_sire(void)
{
    GH_UART2_MCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MCR_sire] --> 0x%08x\n",
                        REG_UART2_MCR,value);
    #endif
    return tmp_value.bitc.sire;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_LSR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'UART2_LSR'. */
U32  GH_UART2_get_LSR(void);
/*! \brief Reads the bit group 'dr' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_dr(void);
/*! \brief Reads the bit group 'oe' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_oe(void);
/*! \brief Reads the bit group 'pe' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_pe(void);
/*! \brief Reads the bit group 'fe' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_fe(void);
/*! \brief Reads the bit group 'bi' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_bi(void);
/*! \brief Reads the bit group 'temt' of register 'UART2_LSR'. */
U8   GH_UART2_get_LSR_temt(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_UART2_get_LSR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_UART2_get_LSR_dr(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_dr] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.dr;
}
GH_INLINE U8   GH_UART2_get_LSR_oe(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_oe] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.oe;
}
GH_INLINE U8   GH_UART2_get_LSR_pe(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_pe] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.pe;
}
GH_INLINE U8   GH_UART2_get_LSR_fe(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_fe] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.fe;
}
GH_INLINE U8   GH_UART2_get_LSR_bi(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_bi] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.bi;
}
GH_INLINE U8   GH_UART2_get_LSR_temt(void)
{
    GH_UART2_LSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_LSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_LSR_temt] --> 0x%08x\n",
                        REG_UART2_LSR,value);
    #endif
    return tmp_value.bitc.temt;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_MSR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'UART2_MSR'. */
U32  GH_UART2_get_MSR(void);
/*! \brief Reads the bit group 'dcts' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_dcts(void);
/*! \brief Reads the bit group 'ddsr' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_ddsr(void);
/*! \brief Reads the bit group 'teri' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_teri(void);
/*! \brief Reads the bit group 'ddcd' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_ddcd(void);
/*! \brief Reads the bit group 'cts' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_cts(void);
/*! \brief Reads the bit group 'dsr' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_dsr(void);
/*! \brief Reads the bit group 'ri' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_ri(void);
/*! \brief Reads the bit group 'dcd' of register 'UART2_MSR'. */
U8   GH_UART2_get_MSR_dcd(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_UART2_get_MSR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_UART2_get_MSR_dcts(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_dcts] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.dcts;
}
GH_INLINE U8   GH_UART2_get_MSR_ddsr(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_ddsr] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.ddsr;
}
GH_INLINE U8   GH_UART2_get_MSR_teri(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_teri] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.teri;
}
GH_INLINE U8   GH_UART2_get_MSR_ddcd(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_ddcd] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.ddcd;
}
GH_INLINE U8   GH_UART2_get_MSR_cts(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_cts] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.cts;
}
GH_INLINE U8   GH_UART2_get_MSR_dsr(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_dsr] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.dsr;
}
GH_INLINE U8   GH_UART2_get_MSR_ri(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_ri] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.ri;
}
GH_INLINE U8   GH_UART2_get_MSR_dcd(void)
{
    GH_UART2_MSR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_MSR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_MSR_dcd] --> 0x%08x\n",
                        REG_UART2_MSR,value);
    #endif
    return tmp_value.bitc.dcd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register UART2_SCR (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'UART2_SCR'. */
void GH_UART2_set_SCR(U32 data);
/*! \brief Reads the register 'UART2_SCR'. */
U32  GH_UART2_get_SCR(void);
/*! \brief Writes the bit group 'scr' of register 'UART2_SCR'. */
void GH_UART2_set_SCR_scr(U8 data);
/*! \brief Reads the bit group 'scr' of register 'UART2_SCR'. */
U8   GH_UART2_get_SCR_scr(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_UART2_set_SCR(U32 data)
{
    *(volatile U32 *)REG_UART2_SCR = data;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_SCR] <-- 0x%08x\n",
                        REG_UART2_SCR,data,data);
    #endif
}
GH_INLINE U32  GH_UART2_get_SCR(void)
{
    U32 value = (*(volatile U32 *)REG_UART2_SCR);

    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_SCR] --> 0x%08x\n",
                        REG_UART2_SCR,value);
    #endif
    return value;
}
GH_INLINE void GH_UART2_set_SCR_scr(U8 data)
{
    GH_UART2_SCR_S d;
    d.all = *(volatile U32 *)REG_UART2_SCR;
    d.bitc.scr = data;
    *(volatile U32 *)REG_UART2_SCR = d.all;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_UART2_set_SCR_scr] <-- 0x%08x\n",
                        REG_UART2_SCR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_UART2_get_SCR_scr(void)
{
    GH_UART2_SCR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_UART2_SCR);

    tmp_value.all = value;
    #if GH_UART2_ENABLE_DEBUG_PRINT
    GH_UART2_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_UART2_get_SCR_scr] --> 0x%08x\n",
                        REG_UART2_SCR,value);
    #endif
    return tmp_value.bitc.scr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_UART2_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_UART2_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

