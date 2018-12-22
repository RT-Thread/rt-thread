/******************************************************************************
**
** \file      gh_spi1.c
**
** \brief     Master interface and supports up to 1 external SPI slave devices. SSI2.
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
#include "gh_spi1.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_SPI1_DW_S                            m_spi1_dw;

/*----------------------------------------------------------------------------*/
/* register SPI1_CTRLR0 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_CTRLR0(U32 data)
{
    *(volatile U32 *)REG_SPI1_CTRLR0 = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,data,data);
    #endif
}
U32  GH_SPI1_get_CTRLR0(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return value;
}
void GH_SPI1_set_CTRLR0_DFS(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.dfs = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_DFS] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_DFS(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_DFS] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.dfs;
}
void GH_SPI1_set_CTRLR0_FRF(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.frf = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_FRF] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_FRF(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_FRF] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.frf;
}
void GH_SPI1_set_CTRLR0_SCPH(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.scph = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SCPH] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_SCPH(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SCPH] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.scph;
}
void GH_SPI1_set_CTRLR0_SCPOL(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.scpol = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SCPOL] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_SCPOL(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SCPOL] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.scpol;
}
void GH_SPI1_set_CTRLR0_TMOD(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.tmod = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_TMOD] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_TMOD(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_TMOD] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.tmod;
}
void GH_SPI1_set_CTRLR0_SLV_OE(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.slv_oe = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SLV_OE] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_SLV_OE(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SLV_OE] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.slv_oe;
}
void GH_SPI1_set_CTRLR0_SRL(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.srl = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SRL] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_SRL(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SRL] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.srl;
}
void GH_SPI1_set_CTRLR0_CFS(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.cfs = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_CFS] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_CTRLR0_CFS(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_CFS] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.cfs;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_CTRLR1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_CTRLR1(U32 data)
{
    *(volatile U32 *)REG_SPI1_CTRLR1 = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR1] <-- 0x%08x\n",
                        REG_SPI1_CTRLR1,data,data);
    #endif
}
U32  GH_SPI1_get_CTRLR1(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR1);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR1] --> 0x%08x\n",
                        REG_SPI1_CTRLR1,value);
    #endif
    return value;
}
void GH_SPI1_set_CTRLR1_NDF(U16 data)
{
    GH_SPI1_CTRLR1_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR1;
    d.bitc.ndf = data;
    *(volatile U32 *)REG_SPI1_CTRLR1 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR1_NDF] <-- 0x%08x\n",
                        REG_SPI1_CTRLR1,d.all,d.all);
    #endif
}
U16  GH_SPI1_get_CTRLR1_NDF(void)
{
    GH_SPI1_CTRLR1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR1);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR1_NDF] --> 0x%08x\n",
                        REG_SPI1_CTRLR1,value);
    #endif
    return tmp_value.bitc.ndf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SSIENR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_SSIENR(U32 data)
{
    *(volatile U32 *)REG_SPI1_SSIENR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SSIENR] <-- 0x%08x\n",
                        REG_SPI1_SSIENR,data,data);
    #endif
}
U32  GH_SPI1_get_SSIENR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SSIENR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SSIENR] --> 0x%08x\n",
                        REG_SPI1_SSIENR,value);
    #endif
    return value;
}
void GH_SPI1_set_SSIENR_ssi_enb(U8 data)
{
    GH_SPI1_SSIENR_S d;
    d.all = *(volatile U32 *)REG_SPI1_SSIENR;
    d.bitc.ssi_enb = data;
    *(volatile U32 *)REG_SPI1_SSIENR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SSIENR_ssi_enb] <-- 0x%08x\n",
                        REG_SPI1_SSIENR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_SSIENR_ssi_enb(void)
{
    GH_SPI1_SSIENR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SSIENR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SSIENR_ssi_enb] --> 0x%08x\n",
                        REG_SPI1_SSIENR,value);
    #endif
    return tmp_value.bitc.ssi_enb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SER (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_SER(U32 data)
{
    *(volatile U32 *)REG_SPI1_SER = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER] <-- 0x%08x\n",
                        REG_SPI1_SER,data,data);
    #endif
}
U32  GH_SPI1_get_SER(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return value;
}
void GH_SPI1_set_SER_SER_L(U8 data)
{
    GH_SPI1_SER_S d;
    d.all = *(volatile U32 *)REG_SPI1_SER;
    d.bitc.ser_l = data;
    *(volatile U32 *)REG_SPI1_SER = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER_SER_L] <-- 0x%08x\n",
                        REG_SPI1_SER,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_SER_SER_L(void)
{
    GH_SPI1_SER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER_SER_L] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return tmp_value.bitc.ser_l;
}
void GH_SPI1_set_SER_SER_H(U8 data)
{
    GH_SPI1_SER_S d;
    d.all = *(volatile U32 *)REG_SPI1_SER;
    d.bitc.ser_h = data;
    *(volatile U32 *)REG_SPI1_SER = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER_SER_H] <-- 0x%08x\n",
                        REG_SPI1_SER,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_SER_SER_H(void)
{
    GH_SPI1_SER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER_SER_H] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return tmp_value.bitc.ser_h;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_BAUDR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_BAUDR(U32 data)
{
    *(volatile U32 *)REG_SPI1_BAUDR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_BAUDR] <-- 0x%08x\n",
                        REG_SPI1_BAUDR,data,data);
    #endif
}
U32  GH_SPI1_get_BAUDR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_BAUDR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_BAUDR] --> 0x%08x\n",
                        REG_SPI1_BAUDR,value);
    #endif
    return value;
}
void GH_SPI1_set_BAUDR_SCKDV(U16 data)
{
    GH_SPI1_BAUDR_S d;
    d.all = *(volatile U32 *)REG_SPI1_BAUDR;
    d.bitc.sckdv = data;
    *(volatile U32 *)REG_SPI1_BAUDR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_BAUDR_SCKDV] <-- 0x%08x\n",
                        REG_SPI1_BAUDR,d.all,d.all);
    #endif
}
U16  GH_SPI1_get_BAUDR_SCKDV(void)
{
    GH_SPI1_BAUDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_BAUDR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_BAUDR_SCKDV] --> 0x%08x\n",
                        REG_SPI1_BAUDR,value);
    #endif
    return tmp_value.bitc.sckdv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_TXFTLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_TXFTLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFTLR] <-- 0x%08x\n",
                        REG_SPI1_TXFTLR,data,data);
    #endif
}
U32  GH_SPI1_get_TXFTLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXFTLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFTLR] --> 0x%08x\n",
                        REG_SPI1_TXFTLR,value);
    #endif
    return value;
}
void GH_SPI1_set_TXFTLR_TFT(U8 data)
{
    GH_SPI1_TXFTLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_TXFTLR;
    d.bitc.tft = data;
    *(volatile U32 *)REG_SPI1_TXFTLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFTLR_TFT] <-- 0x%08x\n",
                        REG_SPI1_TXFTLR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_TXFTLR_TFT(void)
{
    GH_SPI1_TXFTLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXFTLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFTLR_TFT] --> 0x%08x\n",
                        REG_SPI1_TXFTLR,value);
    #endif
    return tmp_value.bitc.tft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_RXFTLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_RXFTLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFTLR] <-- 0x%08x\n",
                        REG_SPI1_RXFTLR,data,data);
    #endif
}
U32  GH_SPI1_get_RXFTLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXFTLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFTLR] --> 0x%08x\n",
                        REG_SPI1_RXFTLR,value);
    #endif
    return value;
}
void GH_SPI1_set_RXFTLR_RFT(U8 data)
{
    GH_SPI1_RXFTLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_RXFTLR;
    d.bitc.rft = data;
    *(volatile U32 *)REG_SPI1_RXFTLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFTLR_RFT] <-- 0x%08x\n",
                        REG_SPI1_RXFTLR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_RXFTLR_RFT(void)
{
    GH_SPI1_RXFTLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXFTLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFTLR_RFT] --> 0x%08x\n",
                        REG_SPI1_RXFTLR,value);
    #endif
    return tmp_value.bitc.rft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_TXFLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_TXFLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFLR] <-- 0x%08x\n",
                        REG_SPI1_TXFLR,data,data);
    #endif
}
U32  GH_SPI1_get_TXFLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXFLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFLR] --> 0x%08x\n",
                        REG_SPI1_TXFLR,value);
    #endif
    return value;
}
void GH_SPI1_set_TXFLR_TXTFL(U8 data)
{
    GH_SPI1_TXFLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_TXFLR;
    d.bitc.txtfl = data;
    *(volatile U32 *)REG_SPI1_TXFLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFLR_TXTFL] <-- 0x%08x\n",
                        REG_SPI1_TXFLR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_TXFLR_TXTFL(void)
{
    GH_SPI1_TXFLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXFLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFLR_TXTFL] --> 0x%08x\n",
                        REG_SPI1_TXFLR,value);
    #endif
    return tmp_value.bitc.txtfl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_RXFLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_RXFLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFLR] <-- 0x%08x\n",
                        REG_SPI1_RXFLR,data,data);
    #endif
}
U32  GH_SPI1_get_RXFLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXFLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFLR] --> 0x%08x\n",
                        REG_SPI1_RXFLR,value);
    #endif
    return value;
}
void GH_SPI1_set_RXFLR_RXTFL(U8 data)
{
    GH_SPI1_RXFLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_RXFLR;
    d.bitc.rxtfl = data;
    *(volatile U32 *)REG_SPI1_RXFLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFLR_RXTFL] <-- 0x%08x\n",
                        REG_SPI1_RXFLR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_RXFLR_RXTFL(void)
{
    GH_SPI1_RXFLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXFLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFLR_RXTFL] --> 0x%08x\n",
                        REG_SPI1_RXFLR,value);
    #endif
    return tmp_value.bitc.rxtfl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SR (read)                                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_SR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_SR_BUSY(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_BUSY] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.busy;
}
U8   GH_SPI1_get_SR_TFNF(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TFNF] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.tfnf;
}
U8   GH_SPI1_get_SR_TFE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TFE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.tfe;
}
U8   GH_SPI1_get_SR_RFNE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_RFNE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.rfne;
}
U8   GH_SPI1_get_SR_RFF(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_RFF] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.rff;
}
U8   GH_SPI1_get_SR_TXE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TXE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.txe;
}
U8   GH_SPI1_get_SR_DCOL(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_DCOL] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.dcol;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_IMR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_SPI1_set_IMR(U32 data)
{
    *(volatile U32 *)REG_SPI1_IMR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR] <-- 0x%08x\n",
                        REG_SPI1_IMR,data,data);
    #endif
}
U32  GH_SPI1_get_IMR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return value;
}
void GH_SPI1_set_IMR_TXEIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.txeim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_TXEIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_TXEIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_TXEIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.txeim;
}
void GH_SPI1_set_IMR_TXOIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.txoim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_TXOIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_TXOIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_TXOIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.txoim;
}
void GH_SPI1_set_IMR_RXUIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxuim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXUIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_RXUIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXUIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxuim;
}
void GH_SPI1_set_IMR_RXOIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxoim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXOIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_RXOIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXOIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxoim;
}
void GH_SPI1_set_IMR_RXFIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxfim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXFIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_RXFIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXFIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxfim;
}
void GH_SPI1_set_IMR_MSTIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.mstim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_MSTIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
U8   GH_SPI1_get_IMR_MSTIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_MSTIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.mstim;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_ISR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_ISR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_ISR_TXEIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_TXEIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.txeis;
}
U8   GH_SPI1_get_ISR_TXOIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_TXOIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.txois;
}
U8   GH_SPI1_get_ISR_RXUIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXUIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxuis;
}
U8   GH_SPI1_get_ISR_RXOIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXOIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxois;
}
U8   GH_SPI1_get_ISR_RXFIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXFIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxfis;
}
U8   GH_SPI1_get_ISR_MSTIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_MSTIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.mstis;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RISR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_RISR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_RISR_TXEIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_TXEIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.txeir;
}
U8   GH_SPI1_get_RISR_TXOIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_TXOIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.txoir;
}
U8   GH_SPI1_get_RISR_RXUIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXUIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxuir;
}
U8   GH_SPI1_get_RISR_RXOIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXOIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxoir;
}
U8   GH_SPI1_get_RISR_RXFIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXFIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxfir;
}
U8   GH_SPI1_get_RISR_MSTIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_MSTIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.mstir;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_TXOICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXOICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXOICR] --> 0x%08x\n",
                        REG_SPI1_TXOICR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_TXOICR_TXOICR(void)
{
    GH_SPI1_TXOICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXOICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXOICR_TXOICR] --> 0x%08x\n",
                        REG_SPI1_TXOICR,value);
    #endif
    return tmp_value.bitc.txoicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_RXOICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXOICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXOICR] --> 0x%08x\n",
                        REG_SPI1_RXOICR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_RXOICR_RXOICR(void)
{
    GH_SPI1_RXOICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXOICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXOICR_RXOICR] --> 0x%08x\n",
                        REG_SPI1_RXOICR,value);
    #endif
    return tmp_value.bitc.rxoicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXUICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_RXUICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXUICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXUICR] --> 0x%08x\n",
                        REG_SPI1_RXUICR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_RXUICR_RXUICR(void)
{
    GH_SPI1_RXUICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXUICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXUICR_RXUICR] --> 0x%08x\n",
                        REG_SPI1_RXUICR,value);
    #endif
    return tmp_value.bitc.rxuicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_MSTICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_MSTICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_MSTICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_MSTICR] --> 0x%08x\n",
                        REG_SPI1_MSTICR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_MSTICR_MSTICR(void)
{
    GH_SPI1_MSTICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_MSTICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_MSTICR_MSTICR] --> 0x%08x\n",
                        REG_SPI1_MSTICR,value);
    #endif
    return tmp_value.bitc.msticr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_ICR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_ICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_ICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ICR] --> 0x%08x\n",
                        REG_SPI1_ICR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_ICR_ICR(void)
{
    GH_SPI1_ICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ICR_ICR] --> 0x%08x\n",
                        REG_SPI1_ICR,value);
    #endif
    return tmp_value.bitc.icr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_IDR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_IDR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_IDR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IDR] --> 0x%08x\n",
                        REG_SPI1_IDR,value);
    #endif
    return value;
}
U8   GH_SPI1_get_IDR_ID(void)
{
    GH_SPI1_IDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IDR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IDR_ID] --> 0x%08x\n",
                        REG_SPI1_IDR,value);
    #endif
    return tmp_value.bitc.id;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_DR (read)                                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_SPI1_get_DR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_DR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_DR] --> 0x%08x\n",
                        REG_SPI1_DR,value);
    #endif
    return value;
}
U16  GH_SPI1_get_DR_DR(void)
{
    GH_SPI1_DR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_DR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_DR_DR] --> 0x%08x\n",
                        REG_SPI1_DR,value);
    #endif
    return tmp_value.bitc.dr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_DW (write)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_SPI1_set_DW(U32 data)
{
    m_spi1_dw.all = data;
    *(volatile U32 *)REG_SPI1_DW = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_DW] <-- 0x%08x\n",
                        REG_SPI1_DW,data,data);
    #endif
}
U32  GH_SPI1_getm_DW(void)
{
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "[GH_SPI1_getm_DW] --> 0x%08x\n",
                        m_spi1_dw.all);
    #endif
    return m_spi1_dw.all;
}
void GH_SPI1_set_DW_DW(U16 data)
{
    m_spi1_dw.bitc.dw = data;
    *(volatile U32 *)REG_SPI1_DW = m_spi1_dw.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_DW_DW] <-- 0x%08x\n",
                        REG_SPI1_DW,m_spi1_dw.all,m_spi1_dw.all);
    #endif
}
U16  GH_SPI1_getm_DW_DW(void)
{
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "[GH_SPI1_getm_DW_DW] --> 0x%08x\n",
                        m_spi1_dw.bitc.dw);
    #endif
    return m_spi1_dw.bitc.dw;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SPI1_init(void)
{
    GH_SPI1_set_CTRLR0((U32)0x00000007);
    GH_SPI1_set_CTRLR1((U32)0x00000000);
    GH_SPI1_set_SSIENR((U32)0x00000000);
    GH_SPI1_set_SER((U32)0x00000000);
    GH_SPI1_set_BAUDR((U32)0x00000000);
    GH_SPI1_set_TXFTLR((U32)0x00000000);
    GH_SPI1_set_RXFTLR((U32)0x00000000);
    GH_SPI1_set_TXFLR((U32)0x00000000);
    GH_SPI1_set_RXFLR((U32)0x00000000);
    GH_SPI1_set_IMR((U32)0x0000003f);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

