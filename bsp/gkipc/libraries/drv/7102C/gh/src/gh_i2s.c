/******************************************************************************
**
** \file      gh_i2s.c
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
#include "gh_i2s.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_I2S_TXLEFTDATA_S                     m_i2s_txleftdata;
GH_I2S_TXRIGHTDATA_S                    m_i2s_txrightdata;

/*----------------------------------------------------------------------------*/
/* register I2S_Clock (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2S_set_Clock(U32 data)
{
    *(volatile U32 *)REG_I2S_CLOCK = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Clock] <-- 0x%08x\n",
                        REG_I2S_CLOCK,data,data);
    #endif
}
U32  GH_I2S_get_Clock(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_CLOCK);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Clock] --> 0x%08x\n",
                        REG_I2S_CLOCK,value);
    #endif
    return value;
}
void GH_I2S_set_Clock_clk_div(U8 data)
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
U8   GH_I2S_get_Clock_clk_div(void)
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
void GH_I2S_set_Clock_soe(U8 data)
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
U8   GH_I2S_get_Clock_soe(void)
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
void GH_I2S_set_Clock_rsp(U8 data)
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
U8   GH_I2S_get_Clock_rsp(void)
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
void GH_I2S_set_Clock_woe(U8 data)
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
U8   GH_I2S_get_Clock_woe(void)
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
void GH_I2S_set_Clock_ss(U8 data)
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
U8   GH_I2S_get_Clock_ss(void)
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
void GH_I2S_set_Clock_tsp(U8 data)
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
U8   GH_I2S_get_Clock_tsp(void)
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
void GH_I2S_set_ChanSlect(U32 data)
{
    *(volatile U32 *)REG_I2S_CHANSLECT = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_ChanSlect] <-- 0x%08x\n",
                        REG_I2S_CHANSLECT,data,data);
    #endif
}
U32  GH_I2S_get_ChanSlect(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_CHANSLECT);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_ChanSlect] --> 0x%08x\n",
                        REG_I2S_CHANSLECT,value);
    #endif
    return value;
}
void GH_I2S_set_ChanSlect_chan(U8 data)
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
U8   GH_I2S_get_ChanSlect_chan(void)
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
void GH_I2S_set_Mode(U32 data)
{
    *(volatile U32 *)REG_I2S_MODE = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Mode] <-- 0x%08x\n",
                        REG_I2S_MODE,data,data);
    #endif
}
U32  GH_I2S_get_Mode(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_MODE);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Mode] --> 0x%08x\n",
                        REG_I2S_MODE,value);
    #endif
    return value;
}
void GH_I2S_set_Mode_MODE(U8 data)
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
U8   GH_I2S_get_Mode_MODE(void)
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
void GH_I2S_set_TxContr(U32 data)
{
    *(volatile U32 *)REG_I2S_TXCONTR = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxContr] <-- 0x%08x\n",
                        REG_I2S_TXCONTR,data,data);
    #endif
}
U32  GH_I2S_get_TxContr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXCONTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxContr] --> 0x%08x\n",
                        REG_I2S_TXCONTR,value);
    #endif
    return value;
}
void GH_I2S_set_TxContr_mono(U8 data)
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
U8   GH_I2S_get_TxContr_mono(void)
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
void GH_I2S_set_TxContr_twi(U8 data)
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
U8   GH_I2S_get_TxContr_twi(void)
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
void GH_I2S_set_TxContr_order(U8 data)
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
U8   GH_I2S_get_TxContr_order(void)
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
void GH_I2S_set_TxContr_unison(U8 data)
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
U8   GH_I2S_get_TxContr_unison(void)
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
void GH_I2S_set_TxContr_loopback(U8 data)
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
U8   GH_I2S_get_TxContr_loopback(void)
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
void GH_I2S_set_TxContr_twm(U8 data)
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
U8   GH_I2S_get_TxContr_twm(void)
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
void GH_I2S_set_TxContr_mute(U8 data)
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
U8   GH_I2S_get_TxContr_mute(void)
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
void GH_I2S_set_TxFifoLth(U32 data)
{
    *(volatile U32 *)REG_I2S_TXFIFOLTH = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxFifoLth] <-- 0x%08x\n",
                        REG_I2S_TXFIFOLTH,data,data);
    #endif
}
U32  GH_I2S_get_TxFifoLth(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOLTH);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoLth] --> 0x%08x\n",
                        REG_I2S_TXFIFOLTH,value);
    #endif
    return value;
}
void GH_I2S_set_TxFifoLth_ft(U8 data)
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
U8   GH_I2S_get_TxFifoLth_ft(void)
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
U32  GH_I2S_get_TxFifoFlag(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFOFLAG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifoFlag] --> 0x%08x\n",
                        REG_I2S_TXFIFOFLAG,value);
    #endif
    return value;
}
U8   GH_I2S_get_TxFifoFlag_ftv(void)
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
U8   GH_I2S_get_TxFifoFlag_ff(void)
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
U8   GH_I2S_get_TxFifoFlag_ti(void)
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
U8   GH_I2S_get_TxFifoFlag_fe(void)
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
U32  GH_I2S_get_TxFifCntr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXFIFCNTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxFifCntr] --> 0x%08x\n",
                        REG_I2S_TXFIFCNTR,value);
    #endif
    return value;
}
U8   GH_I2S_get_TxFifCntr_num(void)
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
void GH_I2S_set_TxLeftData(U32 data)
{
    m_i2s_txleftdata.all = data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxLeftData] <-- 0x%08x\n",
                        REG_I2S_TXLEFTDATA,data,data);
    #endif
}
U32  GH_I2S_getm_TxLeftData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxLeftData] --> 0x%08x\n",
                        m_i2s_txleftdata.all);
    #endif
    return m_i2s_txleftdata.all;
}
void GH_I2S_set_TxLeftData_data(U32 data)
{
    m_i2s_txleftdata.bitc.data = data;
    *(volatile U32 *)REG_I2S_TXLEFTDATA = m_i2s_txleftdata.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxLeftData_data] <-- 0x%08x\n",
                        REG_I2S_TXLEFTDATA,m_i2s_txleftdata.all,m_i2s_txleftdata.all);
    #endif
}
U32  GH_I2S_getm_TxLeftData_data(void)
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
void GH_I2S_set_TxRightData(U32 data)
{
    m_i2s_txrightdata.all = data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxRightData] <-- 0x%08x\n",
                        REG_I2S_TXRIGHTDATA,data,data);
    #endif
}
U32  GH_I2S_getm_TxRightData(void)
{
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "[GH_I2S_getm_TxRightData] --> 0x%08x\n",
                        m_i2s_txrightdata.all);
    #endif
    return m_i2s_txrightdata.all;
}
void GH_I2S_set_TxRightData_data(U32 data)
{
    m_i2s_txrightdata.bitc.data = data;
    *(volatile U32 *)REG_I2S_TXRIGHTDATA = m_i2s_txrightdata.all;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxRightData_data] <-- 0x%08x\n",
                        REG_I2S_TXRIGHTDATA,m_i2s_txrightdata.all,m_i2s_txrightdata.all);
    #endif
}
U32  GH_I2S_getm_TxRightData_data(void)
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
void GH_I2S_set_TxIntEnReg(U32 data)
{
    *(volatile U32 *)REG_I2S_TXINTENREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_TxIntEnReg] <-- 0x%08x\n",
                        REG_I2S_TXINTENREG,data,data);
    #endif
}
U32  GH_I2S_get_TxIntEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TXINTENREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_TxIntEnReg] --> 0x%08x\n",
                        REG_I2S_TXINTENREG,value);
    #endif
    return value;
}
void GH_I2S_set_TxIntEnReg_ftv(U8 data)
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
U8   GH_I2S_get_TxIntEnReg_ftv(void)
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
void GH_I2S_set_TxIntEnReg_ti(U8 data)
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
U8   GH_I2S_get_TxIntEnReg_ti(void)
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
void GH_I2S_set_TxIntEnReg_ff(U8 data)
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
U8   GH_I2S_get_TxIntEnReg_ff(void)
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
void GH_I2S_set_TxIntEnReg_fe(U8 data)
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
U8   GH_I2S_get_TxIntEnReg_fe(void)
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
void GH_I2S_set_MultipMode(U32 data)
{
    *(volatile U32 *)REG_I2S_MULTIPMODE = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_MultipMode] <-- 0x%08x\n",
                        REG_I2S_MULTIPMODE,data,data);
    #endif
}
U32  GH_I2S_get_MultipMode(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_MULTIPMODE);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_MultipMode] --> 0x%08x\n",
                        REG_I2S_MULTIPMODE,value);
    #endif
    return value;
}
void GH_I2S_set_MultipMode_fdmaen(U8 data)
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
U8   GH_I2S_get_MultipMode_fdmaen(void)
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
void GH_I2S_set_MultipMode_rest(U8 data)
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
U8   GH_I2S_get_MultipMode_rest(void)
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
void GH_I2S_set_MultipMode_dma(U8 data)
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
U8   GH_I2S_get_MultipMode_dma(void)
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
void GH_I2S_set_MultipMode_en(U8 data)
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
U8   GH_I2S_get_MultipMode_en(void)
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
void GH_I2S_set_RxContr(U32 data)
{
    *(volatile U32 *)REG_I2S_RXCONTR = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxContr] <-- 0x%08x\n",
                        REG_I2S_RXCONTR,data,data);
    #endif
}
U32  GH_I2S_get_RxContr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXCONTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxContr] --> 0x%08x\n",
                        REG_I2S_RXCONTR,value);
    #endif
    return value;
}
void GH_I2S_set_RxContr_order(U8 data)
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
U8   GH_I2S_get_RxContr_order(void)
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
void GH_I2S_set_RxContr_rwi(U8 data)
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
U8   GH_I2S_get_RxContr_rwi(void)
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
void GH_I2S_set_RxContr_loopback(U8 data)
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
U8   GH_I2S_get_RxContr_loopback(void)
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
void GH_I2S_set_RxContr_rwm(U8 data)
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
U8   GH_I2S_get_RxContr_rwm(void)
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
U32  GH_I2S_get_RxData(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXDATA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxData] --> 0x%08x\n",
                        REG_I2S_RXDATA,value);
    #endif
    return value;
}
U32  GH_I2S_get_RxData_data(void)
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
U32  GH_I2S_get_Rxfifcntr(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFCNTR);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rxfifcntr] --> 0x%08x\n",
                        REG_I2S_RXFIFCNTR,value);
    #endif
    return value;
}
U8   GH_I2S_get_Rxfifcntr_num(void)
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
void GH_I2S_set_RxIntEnReg(U32 data)
{
    *(volatile U32 *)REG_I2S_RXINTENREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxIntEnReg] <-- 0x%08x\n",
                        REG_I2S_RXINTENREG,data,data);
    #endif
}
U32  GH_I2S_get_RxIntEnReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXINTENREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxIntEnReg] --> 0x%08x\n",
                        REG_I2S_RXINTENREG,value);
    #endif
    return value;
}
void GH_I2S_set_RxIntEnReg_fo(U8 data)
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
U8   GH_I2S_get_RxIntEnReg_fo(void)
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
void GH_I2S_set_RxIntEnReg_fe(U8 data)
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
U8   GH_I2S_get_RxIntEnReg_fe(void)
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
void GH_I2S_set_RxIntEnReg_ftv(U8 data)
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
U8   GH_I2S_get_RxIntEnReg_ftv(void)
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
void GH_I2S_set_RxIntEnReg_ri(U8 data)
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
U8   GH_I2S_get_RxIntEnReg_ri(void)
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
void GH_I2S_set_RxIntEnReg_ff(U8 data)
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
U8   GH_I2S_get_RxIntEnReg_ff(void)
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
void GH_I2S_set_RxFifoGth(U32 data)
{
    *(volatile U32 *)REG_I2S_RXFIFOGTH = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxFifoGth] <-- 0x%08x\n",
                        REG_I2S_RXFIFOGTH,data,data);
    #endif
}
U32  GH_I2S_get_RxFifoGth(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOGTH);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoGth] --> 0x%08x\n",
                        REG_I2S_RXFIFOGTH,value);
    #endif
    return value;
}
void GH_I2S_set_RxFifoGth_ft(U8 data)
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
U8   GH_I2S_get_RxFifoGth_ft(void)
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
void GH_I2S_set_RxEcho(U32 data)
{
    *(volatile U32 *)REG_I2S_RXECHO = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_RxEcho] <-- 0x%08x\n",
                        REG_I2S_RXECHO,data,data);
    #endif
}
U32  GH_I2S_get_RxEcho(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXECHO);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxEcho] --> 0x%08x\n",
                        REG_I2S_RXECHO,value);
    #endif
    return value;
}
void GH_I2S_set_RxEcho_echo(U8 data)
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
U8   GH_I2S_get_RxEcho_echo(void)
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
void GH_I2S_set_WPREG(U32 data)
{
    *(volatile U32 *)REG_I2S_WPREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WPREG] <-- 0x%08x\n",
                        REG_I2S_WPREG,data,data);
    #endif
}
U32  GH_I2S_get_WPREG(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_WPREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WPREG] --> 0x%08x\n",
                        REG_I2S_WPREG,value);
    #endif
    return value;
}
void GH_I2S_set_WPREG_Ignbit(U8 data)
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
U8   GH_I2S_get_WPREG_Ignbit(void)
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
void GH_I2S_set_Shift(U32 data)
{
    *(volatile U32 *)REG_I2S_SHIFT = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Shift] <-- 0x%08x\n",
                        REG_I2S_SHIFT,data,data);
    #endif
}
U32  GH_I2S_get_Shift(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_SHIFT);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Shift] --> 0x%08x\n",
                        REG_I2S_SHIFT,value);
    #endif
    return value;
}
void GH_I2S_set_Shift_rx(U8 data)
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
U8   GH_I2S_get_Shift_rx(void)
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
void GH_I2S_set_Shift_tx(U8 data)
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
U8   GH_I2S_get_Shift_tx(void)
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
void GH_I2S_set_Initreg(U32 data)
{
    *(volatile U32 *)REG_I2S_INITREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_Initreg] <-- 0x%08x\n",
                        REG_I2S_INITREG,data,data);
    #endif
}
U32  GH_I2S_get_Initreg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_INITREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Initreg] --> 0x%08x\n",
                        REG_I2S_INITREG,value);
    #endif
    return value;
}
void GH_I2S_set_Initreg_txfrst(U8 data)
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
U8   GH_I2S_get_Initreg_txfrst(void)
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
void GH_I2S_set_Initreg_re(U8 data)
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
U8   GH_I2S_get_Initreg_re(void)
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
void GH_I2S_set_Initreg_te(U8 data)
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
U8   GH_I2S_get_Initreg_te(void)
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
void GH_I2S_set_Initreg_rxfrst(U8 data)
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
U8   GH_I2S_get_Initreg_rxfrst(void)
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
void GH_I2S_set_Initreg_frst(U8 data)
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
U8   GH_I2S_get_Initreg_frst(void)
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
void GH_I2S_set_SlotReg(U32 data)
{
    *(volatile U32 *)REG_I2S_SLOTREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_SlotReg] <-- 0x%08x\n",
                        REG_I2S_SLOTREG,data,data);
    #endif
}
U32  GH_I2S_get_SlotReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_SLOTREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_SlotReg] --> 0x%08x\n",
                        REG_I2S_SLOTREG,value);
    #endif
    return value;
}
void GH_I2S_set_SlotReg_slotcont(U8 data)
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
U8   GH_I2S_get_SlotReg_slotcont(void)
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
U32  GH_I2S_get_RxFifoFlag(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RXFIFOFLAG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_RxFifoFlag] --> 0x%08x\n",
                        REG_I2S_RXFIFOFLAG,value);
    #endif
    return value;
}
U8   GH_I2S_get_RxFifoFlag_fo(void)
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
U8   GH_I2S_get_RxFifoFlag_fe(void)
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
U8   GH_I2S_get_RxFifoFlag_ftv(void)
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
U8   GH_I2S_get_RxFifoFlag_ri(void)
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
U8   GH_I2S_get_RxFifoFlag_ff(void)
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
void GH_I2S_set_WlReg(U32 data)
{
    *(volatile U32 *)REG_I2S_WLREG = data;
    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2S_set_WlReg] <-- 0x%08x\n",
                        REG_I2S_WLREG,data,data);
    #endif
}
U32  GH_I2S_get_WlReg(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_WLREG);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_WlReg] --> 0x%08x\n",
                        REG_I2S_WLREG,value);
    #endif
    return value;
}
void GH_I2S_set_WlReg_Wlen(U8 data)
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
U8   GH_I2S_get_WlReg_Wlen(void)
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
U32  GH_I2S_get_Rx_Dma(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_RX_DMA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Rx_Dma] --> 0x%08x\n",
                        REG_I2S_RX_DMA,value);
    #endif
    return value;
}
U32  GH_I2S_get_Rx_Dma_data(void)
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
U32  GH_I2S_get_Tx_Left_Dma(void)
{
    U32 value = (*(volatile U32 *)REG_I2S_TX_LEFT_DMA);

    #if GH_I2S_ENABLE_DEBUG_PRINT
    GH_I2S_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2S_get_Tx_Left_Dma] --> 0x%08x\n",
                        REG_I2S_TX_LEFT_DMA,value);
    #endif
    return value;
}
U32  GH_I2S_get_Tx_Left_Dma_data(void)
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
void GH_I2S_init(void)
{
    GH_I2S_set_Clock((U32)0x00000100);
    GH_I2S_set_ChanSlect((U32)0x00000000);
    GH_I2S_set_Mode((U32)0x00000004);
    GH_I2S_set_TxContr((U32)0x00000000);
    GH_I2S_set_TxFifoLth((U32)0x00000000);
    GH_I2S_set_TxLeftData((U32)0x00000000);
    GH_I2S_set_TxRightData((U32)0x00000000);
    GH_I2S_set_TxIntEnReg((U32)0x00000001);
    GH_I2S_set_MultipMode((U32)0x00000004);
    GH_I2S_set_RxContr((U32)0x00000000);
    GH_I2S_set_RxIntEnReg((U32)0x00000004);
    GH_I2S_set_RxFifoGth((U32)0x0000003f);
    GH_I2S_set_RxEcho((U32)0x00000000);
    GH_I2S_set_WPREG((U32)0x00000000);
    GH_I2S_set_Shift((U32)0x00000000);
    GH_I2S_set_Initreg((U32)0x00000000);
    GH_I2S_set_SlotReg((U32)0x00000000);
    GH_I2S_set_WlReg((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

