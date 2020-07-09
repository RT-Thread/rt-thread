/*!
*******************************************************************************
**
** \file      gh_i2s.h
**
** \brief     I2S Interface..
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
#ifndef _GH_I2S_H
#define _GH_I2S_H

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

#define GH_I2S_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_I2S_DEBUG_PRINT_FUNCTION printk
#else
#define GH_I2S_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_I2S_ENABLE_DEBUG_PRINT
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
#define REG_I2S_CLOCK                                       FIO_ADDRESS(I2S,0x9000A000) /* read/write */
#define REG_I2S_CHANSLECT                                   FIO_ADDRESS(I2S,0x9000A004) /* read/write */
#define REG_I2S_MODE                                        FIO_ADDRESS(I2S,0x9000A008) /* read/write */
#define REG_I2S_TXCONTR                                     FIO_ADDRESS(I2S,0x9000A00C) /* read/write */
#define REG_I2S_TXFIFOLTH                                   FIO_ADDRESS(I2S,0x9000A010) /* read/write */
#define REG_I2S_TXFIFOFLAG                                  FIO_ADDRESS(I2S,0x9000A014) /* read */
#define REG_I2S_TXFIFCNTR                                   FIO_ADDRESS(I2S,0x9000A018) /* read */
#define REG_I2S_TXLEFTDATA                                  FIO_ADDRESS(I2S,0x9000A01C) /* write */
#define REG_I2S_TXRIGHTDATA                                 FIO_ADDRESS(I2S,0x9000A020) /* write */
#define REG_I2S_TXINTENREG                                  FIO_ADDRESS(I2S,0x9000A024) /* read/write */
#define REG_I2S_MULTIPMODE                                  FIO_ADDRESS(I2S,0x9000A028) /* read/write */
#define REG_I2S_RXCONTR                                     FIO_ADDRESS(I2S,0x9000A02C) /* read/write */
#define REG_I2S_RXDATA                                      FIO_ADDRESS(I2S,0x9000A030) /* read */
#define REG_I2S_RXFIFCNTR                                   FIO_ADDRESS(I2S,0x9000A034) /* read */
#define REG_I2S_RXINTENREG                                  FIO_ADDRESS(I2S,0x9000A038) /* read/write */
#define REG_I2S_RXFIFOGTH                                   FIO_ADDRESS(I2S,0x9000A03C) /* read/write */
#define REG_I2S_RXECHO                                      FIO_ADDRESS(I2S,0x9000A040) /* read/write */
#define REG_I2S_WPREG                                       FIO_ADDRESS(I2S,0x9000A044) /* read/write */
#define REG_I2S_SHIFT                                       FIO_ADDRESS(I2S,0x9000A048) /* read/write */
#define REG_I2S_INITREG                                     FIO_ADDRESS(I2S,0x9000A04C) /* read/write */
#define REG_I2S_SLOTREG                                     FIO_ADDRESS(I2S,0x9000A050) /* read/write */
#define REG_I2S_RXFIFOFLAG                                  FIO_ADDRESS(I2S,0x9000A054) /* read */
#define REG_I2S_WLREG                                       FIO_ADDRESS(I2S,0x9000A058) /* read/write */
#define REG_I2S_RX_DMA                                      FIO_ADDRESS(I2S,0x9000A080) /* read */
#define REG_I2S_TX_LEFT_DMA                                 FIO_ADDRESS(I2S,0x9000A0C0) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* I2S_Clock */
    U32 all;
    struct {
        U32 clk_div                     : 5;
        U32 soe                         : 1;
        U32 rsp                         : 1;
        U32 woe                         : 1;
        U32 ss                          : 1;
        U32 tsp                         : 1;
        U32                             : 22;
    } bitc;
} GH_I2S_CLOCK_S;

typedef union { /* I2S_ChanSlect */
    U32 all;
    struct {
        U32 chan                        : 2;
        U32                             : 30;
    } bitc;
} GH_I2S_CHANSLECT_S;

typedef union { /* I2S_Mode */
    U32 all;
    struct {
        U32 mode                        : 3;
        U32                             : 29;
    } bitc;
} GH_I2S_MODE_S;

typedef union { /* I2S_TxContr */
    U32 all;
    struct {
        U32 mono                        : 2;
        U32 twi                         : 1;
        U32 order                       : 1;
        U32 unison                      : 1;
        U32 loopback                    : 1;
        U32 twm                         : 1;
        U32 mute                        : 1;
        U32                             : 24;
    } bitc;
} GH_I2S_TXCONTR_S;

typedef union { /* I2S_TxFifoLth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFOLTH_S;

typedef union { /* I2S_TxFifoFlag */
    U32 all;
    struct {
        U32 ftv                         : 1;
        U32 ff                          : 1;
        U32 ti                          : 1;
        U32                             : 1;
        U32 fe                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_TXFIFOFLAG_S;

typedef union { /* I2S_TxFifCntr */
    U32 all;
    struct {
        U32 num                         : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_TXFIFCNTR_S;

typedef union { /* I2S_TxLeftData */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TXLEFTDATA_S;

typedef union { /* I2S_TxRightData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_TXRIGHTDATA_S;

typedef union { /* I2S_TxIntEnReg */
    U32 all;
    struct {
        U32 ftv                         : 1;
        U32                             : 1;
        U32 ti                          : 1;
        U32 ff                          : 1;
        U32 fe                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_TXINTENREG_S;

typedef union { /* I2S_MultipMode */
    U32 all;
    struct {
        U32 fdmaen                      : 1;
        U32 rest                        : 1;
        U32 dma                         : 1;
        U32 en                          : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_MULTIPMODE_S;

typedef union { /* I2S_RxContr */
    U32 all;
    struct {
        U32 order                       : 1;
        U32 rwi                         : 1;
        U32 loopback                    : 1;
        U32 rwm                         : 1;
        U32                             : 28;
    } bitc;
} GH_I2S_RXCONTR_S;

typedef union { /* I2S_RxData */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RXDATA_S;

typedef union { /* I2S_Rxfifcntr */
    U32 all;
    struct {
        U32 num                         : 8;
        U32                             : 24;
    } bitc;
} GH_I2S_RXFIFCNTR_S;

typedef union { /* I2S_RxIntEnReg */
    U32 all;
    struct {
        U32 fo                          : 1;
        U32 fe                          : 1;
        U32 ftv                         : 1;
        U32 ri                          : 1;
        U32 ff                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_RXINTENREG_S;

typedef union { /* I2S_RxFifoGth */
    U32 all;
    struct {
        U32 ft                          : 7;
        U32                             : 25;
    } bitc;
} GH_I2S_RXFIFOGTH_S;

typedef union { /* I2S_RxEcho */
    U32 all;
    struct {
        U32 echo                        : 1;
        U32                             : 31;
    } bitc;
} GH_I2S_RXECHO_S;

typedef union { /* I2S_WPREG */
    U32 all;
    struct {
        U32 ignbit                      : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WPREG_S;

typedef union { /* I2S_Shift */
    U32 all;
    struct {
        U32 rx                          : 1;
        U32 tx                          : 1;
        U32                             : 30;
    } bitc;
} GH_I2S_SHIFT_S;

typedef union { /* I2S_Initreg */
    U32 all;
    struct {
        U32 txfrst                      : 1;
        U32 re                          : 1;
        U32 te                          : 1;
        U32 rxfrst                      : 1;
        U32 frst                        : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_INITREG_S;

typedef union { /* I2S_SlotReg */
    U32 all;
    struct {
        U32 slotcont                    : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_SLOTREG_S;

typedef union { /* I2S_RxFifoFlag */
    U32 all;
    struct {
        U32 fo                          : 1;
        U32 fe                          : 1;
        U32 ftv                         : 1;
        U32 ri                          : 1;
        U32 ff                          : 1;
        U32                             : 27;
    } bitc;
} GH_I2S_RXFIFOFLAG_S;

typedef union { /* I2S_WlReg */
    U32 all;
    struct {
        U32 wlen                        : 5;
        U32                             : 27;
    } bitc;
} GH_I2S_WLREG_S;

typedef union { /* I2S_Rx_Dma */
    U32 all;
    struct {
        U32 data                        : 24;
        U32                             : 8;
    } bitc;
} GH_I2S_RX_DMA_S;

typedef union { /* I2S_Tx_Left_Dma */
    U32 all;
    struct {
        U32 data                        : 32;
    } bitc;
} GH_I2S_TX_LEFT_DMA_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_I2S_TXLEFTDATA_S                     m_i2s_txleftdata;
extern GH_I2S_TXRIGHTDATA_S                    m_i2s_txrightdata;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register I2S_Clock (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_Clock'. */
void GH_I2S_set_Clock(U32 data);
/*! \brief Reads the register 'I2S_Clock'. */
U32  GH_I2S_get_Clock(void);
/*! \brief Writes the bit group 'clk_div' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_clk_div(U8 data);
/*! \brief Reads the bit group 'clk_div' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_clk_div(void);
/*! \brief Writes the bit group 'soe' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_soe(U8 data);
/*! \brief Reads the bit group 'soe' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_soe(void);
/*! \brief Writes the bit group 'rsp' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_rsp(U8 data);
/*! \brief Reads the bit group 'rsp' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_rsp(void);
/*! \brief Writes the bit group 'woe' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_woe(U8 data);
/*! \brief Reads the bit group 'woe' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_woe(void);
/*! \brief Writes the bit group 'ss' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_ss(U8 data);
/*! \brief Reads the bit group 'ss' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_ss(void);
/*! \brief Writes the bit group 'tsp' of register 'I2S_Clock'. */
void GH_I2S_set_Clock_tsp(U8 data);
/*! \brief Reads the bit group 'tsp' of register 'I2S_Clock'. */
U8   GH_I2S_get_Clock_tsp(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_Clock(U32 data)
{
    *(volatile U32 *)REG_I2S_CLOCK = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock] <-- 0x%08x\n",
                        REG_I2S_CLOCK,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_Clock(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_Clock_clk_div(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.clk_div = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_clk_div] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_clk_div(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_clk_div] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.clk_div;
}
GH_INLINE void GH_I2S_set_Clock_soe(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.soe = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_soe] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_soe(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_soe] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.soe;
}
GH_INLINE void GH_I2S_set_Clock_rsp(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.rsp = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_rsp] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_rsp(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_rsp] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.rsp;
}
GH_INLINE void GH_I2S_set_Clock_woe(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.woe = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_woe] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_woe(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_woe] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.woe;
}
GH_INLINE void GH_I2S_set_Clock_ss(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.ss = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_ss] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_ss(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_ss] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.ss;
}
GH_INLINE void GH_I2S_set_Clock_tsp(U8 data)
{
    GH_I2S_CLOCK_S d;
    d.all = *(volatile U32 *)REG_I2S_CLOCK;
    d.bitc.tsp = data;
    *(volatile U32 *)REG_I2S_CLOCK = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock_tsp] <-- 0x%08x\n",
                        REG_I2S_CLOCK,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Clock_tsp(void)
{
    GH_I2S_CLOCK_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock_tsp] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return tmp_value.bitc.tsp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_ChanSlect (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_ChanSlect'. */
void GH_I2S_set_ChanSlect(U32 data);
/*! \brief Reads the register 'I2S_ChanSlect'. */
U32  GH_I2S_get_ChanSlect(void);
/*! \brief Writes the bit group 'chan' of register 'I2S_ChanSlect'. */
void GH_I2S_set_ChanSlect_chan(U8 data);
/*! \brief Reads the bit group 'chan' of register 'I2S_ChanSlect'. */
U8   GH_I2S_get_ChanSlect_chan(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_ChanSlect(U32 data)
{
    *(volatile U32 *)REG_I2S_CHANSLECT = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_ChanSlect] <-- 0x%08x\n",
                        REG_I2S_CHANSLECT,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_ChanSlect(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_CHANSLECT);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_ChanSlect] --> 0x%08x\n",
                        REG_I2S_CHANSLECT,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_ChanSlect_chan(U8 data)
{
    GH_I2S_CHANSLECT_S d;
    d.all = *(volatile U32 *)REG_I2S_CHANSLECT;
    d.bitc.chan = data;
    *(volatile U32 *)REG_I2S_CHANSLECT = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_ChanSlect_chan] <-- 0x%08x\n",
                        REG_I2S_CHANSLECT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_ChanSlect_chan(void)
{
    GH_I2S_CHANSLECT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_CHANSLECT);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_ChanSlect_chan] --> 0x%08x\n",
                        REG_I2S_CHANSLECT,value);
    #endif
    return tmp_value.bitc.chan;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_Mode'. */
void GH_I2S_set_Mode(U32 data);
/*! \brief Reads the register 'I2S_Mode'. */
U32  GH_I2S_get_Mode(void);
/*! \brief Writes the bit group 'MODE' of register 'I2S_Mode'. */
void GH_I2S_set_Mode_MODE(U8 data);
/*! \brief Reads the bit group 'MODE' of register 'I2S_Mode'. */
U8   GH_I2S_get_Mode_MODE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_Mode(U32 data)
{
    *(volatile U32 *)REG_I2S_MODE = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Mode] <-- 0x%08x\n",
                        REG_I2S_MODE,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_Mode(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_MODE);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Mode] --> 0x%08x\n",
                        REG_I2S_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_Mode_MODE(U8 data)
{
    GH_I2S_MODE_S d;
    d.all = *(volatile U32 *)REG_I2S_MODE;
    d.bitc.mode = data;
    *(volatile U32 *)REG_I2S_MODE = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Mode_MODE] <-- 0x%08x\n",
                        REG_I2S_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Mode_MODE(void)
{
    GH_I2S_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MODE);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Mode_MODE] --> 0x%08x\n",
                        REG_I2S_MODE,value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_TxContr'. */
void GH_I2S_set_TxContr(U32 data);
/*! \brief Reads the register 'I2S_TxContr'. */
U32  GH_I2S_get_TxContr(void);
/*! \brief Writes the bit group 'mono' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_mono(U8 data);
/*! \brief Reads the bit group 'mono' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_mono(void);
/*! \brief Writes the bit group 'twi' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_twi(U8 data);
/*! \brief Reads the bit group 'twi' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_twi(void);
/*! \brief Writes the bit group 'order' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_order(U8 data);
/*! \brief Reads the bit group 'order' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_order(void);
/*! \brief Writes the bit group 'unison' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_unison(U8 data);
/*! \brief Reads the bit group 'unison' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_unison(void);
/*! \brief Writes the bit group 'loopback' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_loopback(void);
/*! \brief Writes the bit group 'twm' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_twm(U8 data);
/*! \brief Reads the bit group 'twm' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_twm(void);
/*! \brief Writes the bit group 'mute' of register 'I2S_TxContr'. */
void GH_I2S_set_TxContr_mute(U8 data);
/*! \brief Reads the bit group 'mute' of register 'I2S_TxContr'. */
U8   GH_I2S_get_TxContr_mute(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_TxContr(U32 data)
{
    *(volatile U32 *)REG_I2S_TXCONTR = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_TxContr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_TxContr_mono(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.mono = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_mono] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_mono(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_mono] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.mono;
}
GH_INLINE void GH_I2S_set_TxContr_twi(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.twi = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_twi] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_twi(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_twi] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.twi;
}
GH_INLINE void GH_I2S_set_TxContr_order(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.order = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_order] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_order(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_order] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.order;
}
GH_INLINE void GH_I2S_set_TxContr_unison(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.unison = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_unison] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_unison(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_unison] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.unison;
}
GH_INLINE void GH_I2S_set_TxContr_loopback(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_loopback] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_loopback(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_loopback] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.loopback;
}
GH_INLINE void GH_I2S_set_TxContr_twm(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.twm = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_twm] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_twm(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_twm] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.twm;
}
GH_INLINE void GH_I2S_set_TxContr_mute(U8 data)
{
    GH_I2S_TXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_TXCONTR;
    d.bitc.mute = data;
    *(volatile U32 *)REG_I2S_TXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr_mute] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxContr_mute(void)
{
    GH_I2S_TXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr_mute] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return tmp_value.bitc.mute;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoLth (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_TxFifoLth'. */
void GH_I2S_set_TxFifoLth(U32 data);
/*! \brief Reads the register 'I2S_TxFifoLth'. */
U32  GH_I2S_get_TxFifoLth(void);
/*! \brief Writes the bit group 'ft' of register 'I2S_TxFifoLth'. */
void GH_I2S_set_TxFifoLth_ft(U8 data);
/*! \brief Reads the bit group 'ft' of register 'I2S_TxFifoLth'. */
U8   GH_I2S_get_TxFifoLth_ft(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_TxFifoLth(U32 data)
{
    *(volatile U32 *)REG_I2S_TXFIFOLTH = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxFifoLth] <-- 0x%08x\n",
                        REG_I2S_TXFIFOLTH,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_TxFifoLth(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOLTH);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoLth] --> 0x%08x\n",
                        REG_I2S_TXFIFOLTH,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_TxFifoLth_ft(U8 data)
{
    GH_I2S_TXFIFOLTH_S d;
    d.all = *(volatile U32 *)REG_I2S_TXFIFOLTH;
    d.bitc.ft = data;
    *(volatile U32 *)REG_I2S_TXFIFOLTH = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxFifoLth_ft] <-- 0x%08x\n",
                        REG_I2S_TXFIFOLTH,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxFifoLth_ft(void)
{
    GH_I2S_TXFIFOLTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOLTH);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoLth_ft] --> 0x%08x\n",
                        REG_I2S_TXFIFOLTH,value);
    #endif
    return tmp_value.bitc.ft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_TxFifoFlag'. */
U32  GH_I2S_get_TxFifoFlag(void);
/*! \brief Reads the bit group 'ftv' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ftv(void);
/*! \brief Reads the bit group 'ff' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ff(void);
/*! \brief Reads the bit group 'ti' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_ti(void);
/*! \brief Reads the bit group 'fe' of register 'I2S_TxFifoFlag'. */
U8   GH_I2S_get_TxFifoFlag_fe(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_TxFifoFlag(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ftv(void)
{
    GH_I2S_TXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag_ftv] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ftv;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ff(void)
{
    GH_I2S_TXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag_ff] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ff;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_ti(void)
{
    GH_I2S_TXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag_ti] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ti;
}
GH_INLINE U8   GH_I2S_get_TxFifoFlag_fe(void)
{
    GH_I2S_TXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag_fe] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.fe;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxFifCntr (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_TxFifCntr'. */
U32  GH_I2S_get_TxFifCntr(void);
/*! \brief Reads the bit group 'num' of register 'I2S_TxFifCntr'. */
U8   GH_I2S_get_TxFifCntr_num(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_TxFifCntr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFCNTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifCntr] --> 0x%08x\n",
                        REG_I2S_TXFIFCNTR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_I2S_get_TxFifCntr_num(void)
{
    GH_I2S_TXFIFCNTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFCNTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifCntr_num] --> 0x%08x\n",
                        REG_I2S_TXFIFCNTR,value);
    #endif
    return tmp_value.bitc.num;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxLeftData (write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'I2S_TxLeftData'. */
void GH_I2S_set_TxLeftData(U32 data);
/*! \brief Reads the mirror variable of the register 'I2S_TxLeftData'. */
U32  GH_I2S_getm_TxLeftData(void);
/*! \brief Writes the bit group 'data' of register 'I2S_TxLeftData'. */
void GH_I2S_set_TxLeftData_data(U32 data);
/*! \brief Reads the bit group 'data' from the mirror variable of register 'I2S_TxLeftData'. */
U32  GH_I2S_getm_TxLeftData_data(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_I2S_set_TxLeftData(U32 data)
{
    m_i2s_txleftdata.all = data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxLeftData] <-- 0x%08x\n",
                        REG_I2S_TXLEFTDATA,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_getm_TxLeftData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxLeftData] --> 0x%08x\n",
                        m_i2s_txleftdata.all);
    #endif
    return m_i2s_txleftdata.all;
}
GH_INLINE void GH_I2S_set_TxLeftData_data(U32 data)
{
    m_i2s_txleftdata.bitc.data = data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA = m_i2s_txleftdata.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxLeftData_data] <-- 0x%08x\n",
                        REG_I2S_TXLEFTDATA,m_i2s_txleftdata.all,m_i2s_txleftdata.all);
    #endif
}
GH_INLINE U32  GH_I2S_getm_TxLeftData_data(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxLeftData_data] --> 0x%08x\n",
                        m_i2s_txleftdata.bitc.data);
    #endif
    return m_i2s_txleftdata.bitc.data;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxRightData (write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'I2S_TxRightData'. */
void GH_I2S_set_TxRightData(U32 data);
/*! \brief Reads the mirror variable of the register 'I2S_TxRightData'. */
U32  GH_I2S_getm_TxRightData(void);
/*! \brief Writes the bit group 'data' of register 'I2S_TxRightData'. */
void GH_I2S_set_TxRightData_data(U32 data);
/*! \brief Reads the bit group 'data' from the mirror variable of register 'I2S_TxRightData'. */
U32  GH_I2S_getm_TxRightData_data(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_I2S_set_TxRightData(U32 data)
{
    m_i2s_txrightdata.all = data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxRightData] <-- 0x%08x\n",
                        REG_I2S_TXRIGHTDATA,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_getm_TxRightData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxRightData] --> 0x%08x\n",
                        m_i2s_txrightdata.all);
    #endif
    return m_i2s_txrightdata.all;
}
GH_INLINE void GH_I2S_set_TxRightData_data(U32 data)
{
    m_i2s_txrightdata.bitc.data = data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA = m_i2s_txrightdata.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxRightData_data] <-- 0x%08x\n",
                        REG_I2S_TXRIGHTDATA,m_i2s_txrightdata.all,m_i2s_txrightdata.all);
    #endif
}
GH_INLINE U32  GH_I2S_getm_TxRightData_data(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxRightData_data] --> 0x%08x\n",
                        m_i2s_txrightdata.bitc.data);
    #endif
    return m_i2s_txrightdata.bitc.data;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register I2S_TxIntEnReg (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_TxIntEnReg'. */
void GH_I2S_set_TxIntEnReg(U32 data);
/*! \brief Reads the register 'I2S_TxIntEnReg'. */
U32  GH_I2S_get_TxIntEnReg(void);
/*! \brief Writes the bit group 'ftv' of register 'I2S_TxIntEnReg'. */
void GH_I2S_set_TxIntEnReg_ftv(U8 data);
/*! \brief Reads the bit group 'ftv' of register 'I2S_TxIntEnReg'. */
U8   GH_I2S_get_TxIntEnReg_ftv(void);
/*! \brief Writes the bit group 'ti' of register 'I2S_TxIntEnReg'. */
void GH_I2S_set_TxIntEnReg_ti(U8 data);
/*! \brief Reads the bit group 'ti' of register 'I2S_TxIntEnReg'. */
U8   GH_I2S_get_TxIntEnReg_ti(void);
/*! \brief Writes the bit group 'ff' of register 'I2S_TxIntEnReg'. */
void GH_I2S_set_TxIntEnReg_ff(U8 data);
/*! \brief Reads the bit group 'ff' of register 'I2S_TxIntEnReg'. */
U8   GH_I2S_get_TxIntEnReg_ff(void);
/*! \brief Writes the bit group 'fe' of register 'I2S_TxIntEnReg'. */
void GH_I2S_set_TxIntEnReg_fe(U8 data);
/*! \brief Reads the bit group 'fe' of register 'I2S_TxIntEnReg'. */
U8   GH_I2S_get_TxIntEnReg_fe(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_TxIntEnReg(U32 data)
{
    *(volatile U32 *)REG_I2S_TXINTENREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_TxIntEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_TxIntEnReg_ftv(U8 data)
{
    GH_I2S_TXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINTENREG;
    d.bitc.ftv = data;
    *(volatile U32 *)REG_I2S_TXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg_ftv] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxIntEnReg_ftv(void)
{
    GH_I2S_TXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg_ftv] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return tmp_value.bitc.ftv;
}
GH_INLINE void GH_I2S_set_TxIntEnReg_ti(U8 data)
{
    GH_I2S_TXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINTENREG;
    d.bitc.ti = data;
    *(volatile U32 *)REG_I2S_TXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg_ti] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxIntEnReg_ti(void)
{
    GH_I2S_TXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg_ti] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return tmp_value.bitc.ti;
}
GH_INLINE void GH_I2S_set_TxIntEnReg_ff(U8 data)
{
    GH_I2S_TXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINTENREG;
    d.bitc.ff = data;
    *(volatile U32 *)REG_I2S_TXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg_ff] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxIntEnReg_ff(void)
{
    GH_I2S_TXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg_ff] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return tmp_value.bitc.ff;
}
GH_INLINE void GH_I2S_set_TxIntEnReg_fe(U8 data)
{
    GH_I2S_TXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_TXINTENREG;
    d.bitc.fe = data;
    *(volatile U32 *)REG_I2S_TXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg_fe] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_TxIntEnReg_fe(void)
{
    GH_I2S_TXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg_fe] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return tmp_value.bitc.fe;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_MultipMode (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode(U32 data);
/*! \brief Reads the register 'I2S_MultipMode'. */
U32  GH_I2S_get_MultipMode(void);
/*! \brief Writes the bit group 'fdmaen' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_fdmaen(U8 data);
/*! \brief Reads the bit group 'fdmaen' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_fdmaen(void);
/*! \brief Writes the bit group 'rest' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_rest(U8 data);
/*! \brief Reads the bit group 'rest' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_rest(void);
/*! \brief Writes the bit group 'dma' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_dma(U8 data);
/*! \brief Reads the bit group 'dma' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_dma(void);
/*! \brief Writes the bit group 'en' of register 'I2S_MultipMode'. */
void GH_I2S_set_MultipMode_en(U8 data);
/*! \brief Reads the bit group 'en' of register 'I2S_MultipMode'. */
U8   GH_I2S_get_MultipMode_en(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_MultipMode(U32 data)
{
    *(volatile U32 *)REG_I2S_MULTIPMODE = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_MultipMode(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_MultipMode_fdmaen(U8 data)
{
    GH_I2S_MULTIPMODE_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE;
    d.bitc.fdmaen = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode_fdmaen] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_MultipMode_fdmaen(void)
{
    GH_I2S_MULTIPMODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode_fdmaen] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return tmp_value.bitc.fdmaen;
}
GH_INLINE void GH_I2S_set_MultipMode_rest(U8 data)
{
    GH_I2S_MULTIPMODE_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE;
    d.bitc.rest = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode_rest] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_MultipMode_rest(void)
{
    GH_I2S_MULTIPMODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode_rest] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return tmp_value.bitc.rest;
}
GH_INLINE void GH_I2S_set_MultipMode_dma(U8 data)
{
    GH_I2S_MULTIPMODE_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE;
    d.bitc.dma = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode_dma] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_MultipMode_dma(void)
{
    GH_I2S_MULTIPMODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode_dma] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return tmp_value.bitc.dma;
}
GH_INLINE void GH_I2S_set_MultipMode_en(U8 data)
{
    GH_I2S_MULTIPMODE_S d;
    d.all = *(volatile U32 *)REG_I2S_MULTIPMODE;
    d.bitc.en = data;
    *(volatile U32 *)REG_I2S_MULTIPMODE = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode_en] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_MultipMode_en(void)
{
    GH_I2S_MULTIPMODE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode_en] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxContr (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_RxContr'. */
void GH_I2S_set_RxContr(U32 data);
/*! \brief Reads the register 'I2S_RxContr'. */
U32  GH_I2S_get_RxContr(void);
/*! \brief Writes the bit group 'order' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_order(U8 data);
/*! \brief Reads the bit group 'order' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_order(void);
/*! \brief Writes the bit group 'rwi' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_rwi(U8 data);
/*! \brief Reads the bit group 'rwi' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_rwi(void);
/*! \brief Writes the bit group 'loopback' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_loopback(U8 data);
/*! \brief Reads the bit group 'loopback' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_loopback(void);
/*! \brief Writes the bit group 'rwm' of register 'I2S_RxContr'. */
void GH_I2S_set_RxContr_rwm(U8 data);
/*! \brief Reads the bit group 'rwm' of register 'I2S_RxContr'. */
U8   GH_I2S_get_RxContr_rwm(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_RxContr(U32 data)
{
    *(volatile U32 *)REG_I2S_RXCONTR = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_RxContr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_RxContr_order(U8 data)
{
    GH_I2S_RXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR;
    d.bitc.order = data;
    *(volatile U32 *)REG_I2S_RXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr_order] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxContr_order(void)
{
    GH_I2S_RXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr_order] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return tmp_value.bitc.order;
}
GH_INLINE void GH_I2S_set_RxContr_rwi(U8 data)
{
    GH_I2S_RXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR;
    d.bitc.rwi = data;
    *(volatile U32 *)REG_I2S_RXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr_rwi] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxContr_rwi(void)
{
    GH_I2S_RXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr_rwi] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return tmp_value.bitc.rwi;
}
GH_INLINE void GH_I2S_set_RxContr_loopback(U8 data)
{
    GH_I2S_RXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR;
    d.bitc.loopback = data;
    *(volatile U32 *)REG_I2S_RXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr_loopback] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxContr_loopback(void)
{
    GH_I2S_RXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr_loopback] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return tmp_value.bitc.loopback;
}
GH_INLINE void GH_I2S_set_RxContr_rwm(U8 data)
{
    GH_I2S_RXCONTR_S d;
    d.all = *(volatile U32 *)REG_I2S_RXCONTR;
    d.bitc.rwm = data;
    *(volatile U32 *)REG_I2S_RXCONTR = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr_rwm] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxContr_rwm(void)
{
    GH_I2S_RXCONTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr_rwm] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return tmp_value.bitc.rwm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxData (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_RxData'. */
U32  GH_I2S_get_RxData(void);
/*! \brief Reads the bit group 'data' of register 'I2S_RxData'. */
U32  GH_I2S_get_RxData_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_RxData(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXDATA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxData] --> 0x%08x\n",
                        REG_I2S_RXDATA,value);
    #endif
    return value;
}
GH_INLINE U32  GH_I2S_get_RxData_data(void)
{
    GH_I2S_RXDATA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXDATA);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxData_data] --> 0x%08x\n",
                        REG_I2S_RXDATA,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Rxfifcntr (read)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_Rxfifcntr'. */
U32  GH_I2S_get_Rxfifcntr(void);
/*! \brief Reads the bit group 'num' of register 'I2S_Rxfifcntr'. */
U8   GH_I2S_get_Rxfifcntr_num(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_Rxfifcntr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFCNTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rxfifcntr] --> 0x%08x\n",
                        REG_I2S_RXFIFCNTR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_I2S_get_Rxfifcntr_num(void)
{
    GH_I2S_RXFIFCNTR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFCNTR);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rxfifcntr_num] --> 0x%08x\n",
                        REG_I2S_RXFIFCNTR,value);
    #endif
    return tmp_value.bitc.num;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxIntEnReg (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg(U32 data);
/*! \brief Reads the register 'I2S_RxIntEnReg'. */
U32  GH_I2S_get_RxIntEnReg(void);
/*! \brief Writes the bit group 'fo' of register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg_fo(U8 data);
/*! \brief Reads the bit group 'fo' of register 'I2S_RxIntEnReg'. */
U8   GH_I2S_get_RxIntEnReg_fo(void);
/*! \brief Writes the bit group 'fe' of register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg_fe(U8 data);
/*! \brief Reads the bit group 'fe' of register 'I2S_RxIntEnReg'. */
U8   GH_I2S_get_RxIntEnReg_fe(void);
/*! \brief Writes the bit group 'ftv' of register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg_ftv(U8 data);
/*! \brief Reads the bit group 'ftv' of register 'I2S_RxIntEnReg'. */
U8   GH_I2S_get_RxIntEnReg_ftv(void);
/*! \brief Writes the bit group 'ri' of register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg_ri(U8 data);
/*! \brief Reads the bit group 'ri' of register 'I2S_RxIntEnReg'. */
U8   GH_I2S_get_RxIntEnReg_ri(void);
/*! \brief Writes the bit group 'ff' of register 'I2S_RxIntEnReg'. */
void GH_I2S_set_RxIntEnReg_ff(U8 data);
/*! \brief Reads the bit group 'ff' of register 'I2S_RxIntEnReg'. */
U8   GH_I2S_get_RxIntEnReg_ff(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_RxIntEnReg(U32 data)
{
    *(volatile U32 *)REG_I2S_RXINTENREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_RxIntEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_RxIntEnReg_fo(U8 data)
{
    GH_I2S_RXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINTENREG;
    d.bitc.fo = data;
    *(volatile U32 *)REG_I2S_RXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg_fo] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxIntEnReg_fo(void)
{
    GH_I2S_RXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg_fo] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return tmp_value.bitc.fo;
}
GH_INLINE void GH_I2S_set_RxIntEnReg_fe(U8 data)
{
    GH_I2S_RXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINTENREG;
    d.bitc.fe = data;
    *(volatile U32 *)REG_I2S_RXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg_fe] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxIntEnReg_fe(void)
{
    GH_I2S_RXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg_fe] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return tmp_value.bitc.fe;
}
GH_INLINE void GH_I2S_set_RxIntEnReg_ftv(U8 data)
{
    GH_I2S_RXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINTENREG;
    d.bitc.ftv = data;
    *(volatile U32 *)REG_I2S_RXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg_ftv] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxIntEnReg_ftv(void)
{
    GH_I2S_RXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg_ftv] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return tmp_value.bitc.ftv;
}
GH_INLINE void GH_I2S_set_RxIntEnReg_ri(U8 data)
{
    GH_I2S_RXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINTENREG;
    d.bitc.ri = data;
    *(volatile U32 *)REG_I2S_RXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg_ri] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxIntEnReg_ri(void)
{
    GH_I2S_RXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg_ri] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return tmp_value.bitc.ri;
}
GH_INLINE void GH_I2S_set_RxIntEnReg_ff(U8 data)
{
    GH_I2S_RXINTENREG_S d;
    d.all = *(volatile U32 *)REG_I2S_RXINTENREG;
    d.bitc.ff = data;
    *(volatile U32 *)REG_I2S_RXINTENREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg_ff] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxIntEnReg_ff(void)
{
    GH_I2S_RXINTENREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg_ff] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return tmp_value.bitc.ff;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoGth (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_RxFifoGth'. */
void GH_I2S_set_RxFifoGth(U32 data);
/*! \brief Reads the register 'I2S_RxFifoGth'. */
U32  GH_I2S_get_RxFifoGth(void);
/*! \brief Writes the bit group 'ft' of register 'I2S_RxFifoGth'. */
void GH_I2S_set_RxFifoGth_ft(U8 data);
/*! \brief Reads the bit group 'ft' of register 'I2S_RxFifoGth'. */
U8   GH_I2S_get_RxFifoGth_ft(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_RxFifoGth(U32 data)
{
    *(volatile U32 *)REG_I2S_RXFIFOGTH = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxFifoGth] <-- 0x%08x\n",
                        REG_I2S_RXFIFOGTH,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_RxFifoGth(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOGTH);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoGth] --> 0x%08x\n",
                        REG_I2S_RXFIFOGTH,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_RxFifoGth_ft(U8 data)
{
    GH_I2S_RXFIFOGTH_S d;
    d.all = *(volatile U32 *)REG_I2S_RXFIFOGTH;
    d.bitc.ft = data;
    *(volatile U32 *)REG_I2S_RXFIFOGTH = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxFifoGth_ft] <-- 0x%08x\n",
                        REG_I2S_RXFIFOGTH,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxFifoGth_ft(void)
{
    GH_I2S_RXFIFOGTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOGTH);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoGth_ft] --> 0x%08x\n",
                        REG_I2S_RXFIFOGTH,value);
    #endif
    return tmp_value.bitc.ft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxEcho (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_RxEcho'. */
void GH_I2S_set_RxEcho(U32 data);
/*! \brief Reads the register 'I2S_RxEcho'. */
U32  GH_I2S_get_RxEcho(void);
/*! \brief Writes the bit group 'echo' of register 'I2S_RxEcho'. */
void GH_I2S_set_RxEcho_echo(U8 data);
/*! \brief Reads the bit group 'echo' of register 'I2S_RxEcho'. */
U8   GH_I2S_get_RxEcho_echo(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_RxEcho(U32 data)
{
    *(volatile U32 *)REG_I2S_RXECHO = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxEcho] <-- 0x%08x\n",
                        REG_I2S_RXECHO,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_RxEcho(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXECHO);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxEcho] --> 0x%08x\n",
                        REG_I2S_RXECHO,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_RxEcho_echo(U8 data)
{
    GH_I2S_RXECHO_S d;
    d.all = *(volatile U32 *)REG_I2S_RXECHO;
    d.bitc.echo = data;
    *(volatile U32 *)REG_I2S_RXECHO = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxEcho_echo] <-- 0x%08x\n",
                        REG_I2S_RXECHO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_RxEcho_echo(void)
{
    GH_I2S_RXECHO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXECHO);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxEcho_echo] --> 0x%08x\n",
                        REG_I2S_RXECHO,value);
    #endif
    return tmp_value.bitc.echo;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_WPREG (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_WPREG'. */
void GH_I2S_set_WPREG(U32 data);
/*! \brief Reads the register 'I2S_WPREG'. */
U32  GH_I2S_get_WPREG(void);
/*! \brief Writes the bit group 'Ignbit' of register 'I2S_WPREG'. */
void GH_I2S_set_WPREG_Ignbit(U8 data);
/*! \brief Reads the bit group 'Ignbit' of register 'I2S_WPREG'. */
U8   GH_I2S_get_WPREG_Ignbit(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_WPREG(U32 data)
{
    *(volatile U32 *)REG_I2S_WPREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WPREG] <-- 0x%08x\n",
                        REG_I2S_WPREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_WPREG(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_WPREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WPREG] --> 0x%08x\n",
                        REG_I2S_WPREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_WPREG_Ignbit(U8 data)
{
    GH_I2S_WPREG_S d;
    d.all = *(volatile U32 *)REG_I2S_WPREG;
    d.bitc.ignbit = data;
    *(volatile U32 *)REG_I2S_WPREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WPREG_Ignbit] <-- 0x%08x\n",
                        REG_I2S_WPREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_WPREG_Ignbit(void)
{
    GH_I2S_WPREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_WPREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WPREG_Ignbit] --> 0x%08x\n",
                        REG_I2S_WPREG,value);
    #endif
    return tmp_value.bitc.ignbit;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Shift (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_Shift'. */
void GH_I2S_set_Shift(U32 data);
/*! \brief Reads the register 'I2S_Shift'. */
U32  GH_I2S_get_Shift(void);
/*! \brief Writes the bit group 'rx' of register 'I2S_Shift'. */
void GH_I2S_set_Shift_rx(U8 data);
/*! \brief Reads the bit group 'rx' of register 'I2S_Shift'. */
U8   GH_I2S_get_Shift_rx(void);
/*! \brief Writes the bit group 'tx' of register 'I2S_Shift'. */
void GH_I2S_set_Shift_tx(U8 data);
/*! \brief Reads the bit group 'tx' of register 'I2S_Shift'. */
U8   GH_I2S_get_Shift_tx(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_Shift(U32 data)
{
    *(volatile U32 *)REG_I2S_SHIFT = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Shift] <-- 0x%08x\n",
                        REG_I2S_SHIFT,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_Shift(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Shift] --> 0x%08x\n",
                        REG_I2S_SHIFT,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_Shift_rx(U8 data)
{
    GH_I2S_SHIFT_S d;
    d.all = *(volatile U32 *)REG_I2S_SHIFT;
    d.bitc.rx = data;
    *(volatile U32 *)REG_I2S_SHIFT = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Shift_rx] <-- 0x%08x\n",
                        REG_I2S_SHIFT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Shift_rx(void)
{
    GH_I2S_SHIFT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Shift_rx] --> 0x%08x\n",
                        REG_I2S_SHIFT,value);
    #endif
    return tmp_value.bitc.rx;
}
GH_INLINE void GH_I2S_set_Shift_tx(U8 data)
{
    GH_I2S_SHIFT_S d;
    d.all = *(volatile U32 *)REG_I2S_SHIFT;
    d.bitc.tx = data;
    *(volatile U32 *)REG_I2S_SHIFT = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Shift_tx] <-- 0x%08x\n",
                        REG_I2S_SHIFT,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Shift_tx(void)
{
    GH_I2S_SHIFT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Shift_tx] --> 0x%08x\n",
                        REG_I2S_SHIFT,value);
    #endif
    return tmp_value.bitc.tx;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Initreg (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_Initreg'. */
void GH_I2S_set_Initreg(U32 data);
/*! \brief Reads the register 'I2S_Initreg'. */
U32  GH_I2S_get_Initreg(void);
/*! \brief Writes the bit group 'txfrst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_txfrst(U8 data);
/*! \brief Reads the bit group 'txfrst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_txfrst(void);
/*! \brief Writes the bit group 're' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_re(U8 data);
/*! \brief Reads the bit group 're' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_re(void);
/*! \brief Writes the bit group 'te' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_te(U8 data);
/*! \brief Reads the bit group 'te' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_te(void);
/*! \brief Writes the bit group 'rxfrst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_rxfrst(U8 data);
/*! \brief Reads the bit group 'rxfrst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_rxfrst(void);
/*! \brief Writes the bit group 'frst' of register 'I2S_Initreg'. */
void GH_I2S_set_Initreg_frst(U8 data);
/*! \brief Reads the bit group 'frst' of register 'I2S_Initreg'. */
U8   GH_I2S_get_Initreg_frst(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_Initreg(U32 data)
{
    *(volatile U32 *)REG_I2S_INITREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg] <-- 0x%08x\n",
                        REG_I2S_INITREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_Initreg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_Initreg_txfrst(U8 data)
{
    GH_I2S_INITREG_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG;
    d.bitc.txfrst = data;
    *(volatile U32 *)REG_I2S_INITREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg_txfrst] <-- 0x%08x\n",
                        REG_I2S_INITREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Initreg_txfrst(void)
{
    GH_I2S_INITREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg_txfrst] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return tmp_value.bitc.txfrst;
}
GH_INLINE void GH_I2S_set_Initreg_re(U8 data)
{
    GH_I2S_INITREG_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG;
    d.bitc.re = data;
    *(volatile U32 *)REG_I2S_INITREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg_re] <-- 0x%08x\n",
                        REG_I2S_INITREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Initreg_re(void)
{
    GH_I2S_INITREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg_re] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return tmp_value.bitc.re;
}
GH_INLINE void GH_I2S_set_Initreg_te(U8 data)
{
    GH_I2S_INITREG_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG;
    d.bitc.te = data;
    *(volatile U32 *)REG_I2S_INITREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg_te] <-- 0x%08x\n",
                        REG_I2S_INITREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Initreg_te(void)
{
    GH_I2S_INITREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg_te] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return tmp_value.bitc.te;
}
GH_INLINE void GH_I2S_set_Initreg_rxfrst(U8 data)
{
    GH_I2S_INITREG_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG;
    d.bitc.rxfrst = data;
    *(volatile U32 *)REG_I2S_INITREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg_rxfrst] <-- 0x%08x\n",
                        REG_I2S_INITREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Initreg_rxfrst(void)
{
    GH_I2S_INITREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg_rxfrst] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return tmp_value.bitc.rxfrst;
}
GH_INLINE void GH_I2S_set_Initreg_frst(U8 data)
{
    GH_I2S_INITREG_S d;
    d.all = *(volatile U32 *)REG_I2S_INITREG;
    d.bitc.frst = data;
    *(volatile U32 *)REG_I2S_INITREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg_frst] <-- 0x%08x\n",
                        REG_I2S_INITREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_Initreg_frst(void)
{
    GH_I2S_INITREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg_frst] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return tmp_value.bitc.frst;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_SlotReg (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_SlotReg'. */
void GH_I2S_set_SlotReg(U32 data);
/*! \brief Reads the register 'I2S_SlotReg'. */
U32  GH_I2S_get_SlotReg(void);
/*! \brief Writes the bit group 'slotcont' of register 'I2S_SlotReg'. */
void GH_I2S_set_SlotReg_slotcont(U8 data);
/*! \brief Reads the bit group 'slotcont' of register 'I2S_SlotReg'. */
U8   GH_I2S_get_SlotReg_slotcont(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_SlotReg(U32 data)
{
    *(volatile U32 *)REG_I2S_SLOTREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_SlotReg] <-- 0x%08x\n",
                        REG_I2S_SLOTREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_SlotReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_SLOTREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_SlotReg] --> 0x%08x\n",
                        REG_I2S_SLOTREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_SlotReg_slotcont(U8 data)
{
    GH_I2S_SLOTREG_S d;
    d.all = *(volatile U32 *)REG_I2S_SLOTREG;
    d.bitc.slotcont = data;
    *(volatile U32 *)REG_I2S_SLOTREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_SlotReg_slotcont] <-- 0x%08x\n",
                        REG_I2S_SLOTREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_SlotReg_slotcont(void)
{
    GH_I2S_SLOTREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_SLOTREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_SlotReg_slotcont] --> 0x%08x\n",
                        REG_I2S_SLOTREG,value);
    #endif
    return tmp_value.bitc.slotcont;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_RxFifoFlag (read)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_RxFifoFlag'. */
U32  GH_I2S_get_RxFifoFlag(void);
/*! \brief Reads the bit group 'fo' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_fo(void);
/*! \brief Reads the bit group 'fe' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_fe(void);
/*! \brief Reads the bit group 'ftv' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ftv(void);
/*! \brief Reads the bit group 'ri' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ri(void);
/*! \brief Reads the bit group 'ff' of register 'I2S_RxFifoFlag'. */
U8   GH_I2S_get_RxFifoFlag_ff(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_RxFifoFlag(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_fo(void)
{
    GH_I2S_RXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag_fo] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.fo;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_fe(void)
{
    GH_I2S_RXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag_fe] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.fe;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ftv(void)
{
    GH_I2S_RXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag_ftv] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ftv;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ri(void)
{
    GH_I2S_RXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag_ri] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ri;
}
GH_INLINE U8   GH_I2S_get_RxFifoFlag_ff(void)
{
    GH_I2S_RXFIFOFLAG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag_ff] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return tmp_value.bitc.ff;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_WlReg (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'I2S_WlReg'. */
void GH_I2S_set_WlReg(U32 data);
/*! \brief Reads the register 'I2S_WlReg'. */
U32  GH_I2S_get_WlReg(void);
/*! \brief Writes the bit group 'Wlen' of register 'I2S_WlReg'. */
void GH_I2S_set_WlReg_Wlen(U8 data);
/*! \brief Reads the bit group 'Wlen' of register 'I2S_WlReg'. */
U8   GH_I2S_get_WlReg_Wlen(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_I2S_set_WlReg(U32 data)
{
    *(volatile U32 *)REG_I2S_WLREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WlReg] <-- 0x%08x\n",
                        REG_I2S_WLREG,data,data);
    #endif
}
GH_INLINE U32  GH_I2S_get_WlReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_WLREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WlReg] --> 0x%08x\n",
                        REG_I2S_WLREG,value);
    #endif
    return value;
}
GH_INLINE void GH_I2S_set_WlReg_Wlen(U8 data)
{
    GH_I2S_WLREG_S d;
    d.all = *(volatile U32 *)REG_I2S_WLREG;
    d.bitc.wlen = data;
    *(volatile U32 *)REG_I2S_WLREG = d.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WlReg_Wlen] <-- 0x%08x\n",
                        REG_I2S_WLREG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_I2S_get_WlReg_Wlen(void)
{
    GH_I2S_WLREG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_WLREG);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WlReg_Wlen] --> 0x%08x\n",
                        REG_I2S_WLREG,value);
    #endif
    return tmp_value.bitc.wlen;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Rx_Dma (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_Rx_Dma'. */
U32  GH_I2S_get_Rx_Dma(void);
/*! \brief Reads the bit group 'data' of register 'I2S_Rx_Dma'. */
U32  GH_I2S_get_Rx_Dma_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_Rx_Dma(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RX_DMA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rx_Dma] --> 0x%08x\n",
                        REG_I2S_RX_DMA,value);
    #endif
    return value;
}
GH_INLINE U32  GH_I2S_get_Rx_Dma_data(void)
{
    GH_I2S_RX_DMA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_RX_DMA);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rx_Dma_data] --> 0x%08x\n",
                        REG_I2S_RX_DMA,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2S_Tx_Left_Dma (read)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'I2S_Tx_Left_Dma'. */
U32  GH_I2S_get_Tx_Left_Dma(void);
/*! \brief Reads the bit group 'data' of register 'I2S_Tx_Left_Dma'. */
U32  GH_I2S_get_Tx_Left_Dma_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_I2S_get_Tx_Left_Dma(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TX_LEFT_DMA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Tx_Left_Dma] --> 0x%08x\n",
                        REG_I2S_TX_LEFT_DMA,value);
    #endif
    return value;
}
GH_INLINE U32  GH_I2S_get_Tx_Left_Dma_data(void)
{
    GH_I2S_TX_LEFT_DMA_S tmp_value;
    U32 value = (*(volatile U32 *)REG_I2S_TX_LEFT_DMA);

    tmp_value.all = value;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Tx_Left_Dma_data] --> 0x%08x\n",
                        REG_I2S_TX_LEFT_DMA,value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_I2S_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_I2S_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

