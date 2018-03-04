/******************************************************************************
**
** \file      gh_adc.c
**
** \brief     ADC.
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
#include "gh_adc.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG0 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_AUX_ATOP_REG0(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,data,data);
    #endif
}
U32  GH_ADC_get_AUX_ATOP_REG0(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return value;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_maxsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_maxsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_maxsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_maxsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_maxsel;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_maxnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_maxnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_maxnsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_maxnsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_maxnsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_maxnsel;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_pd(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_pd = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_pd] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_pd(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_pd] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_pd;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_oneshot(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_oneshot = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_oneshot] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_oneshot(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_oneshot] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_oneshot;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_freerun(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_freerun = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_freerun] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_freerun(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_freerun] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_freerun;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_refnsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_refnsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_refnsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_refnsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_refnsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_refnsel;
}
void GH_ADC_set_AUX_ATOP_REG0_sar_refsel(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.sar_refsel = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_sar_refsel] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_sar_refsel(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_sar_refsel] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.sar_refsel;
}
void GH_ADC_set_AUX_ATOP_REG0_pd_tsi(U8 data)
{
    GH_ADC_AUX_ATOP_REG0_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG0;
    d.bitc.pd_tsi = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG0 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG0_pd_tsi] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG0_pd_tsi(void)
{
    GH_ADC_AUX_ATOP_REG0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG0);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG0_pd_tsi] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG0,value);
    #endif
    return tmp_value.bitc.pd_tsi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG1 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_AUX_ATOP_REG1(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,data,data);
    #endif
}
U32  GH_ADC_get_AUX_ATOP_REG1(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return value;
}
void GH_ADC_set_AUX_ATOP_REG1_i_sar_key(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.i_sar_key = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_i_sar_key] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG1_i_sar_key(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_i_sar_key] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.i_sar_key;
}
void GH_ADC_set_AUX_ATOP_REG1_sar_key_pge(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.sar_key_pge = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_sar_key_pge] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_pge(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_sar_key_pge] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.sar_key_pge;
}
void GH_ADC_set_AUX_ATOP_REG1_sar_key_aie(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.sar_key_aie = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_sar_key_aie] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG1_sar_key_aie(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_sar_key_aie] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.sar_key_aie;
}
void GH_ADC_set_AUX_ATOP_REG1_oen_sar_key(U8 data)
{
    GH_ADC_AUX_ATOP_REG1_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG1;
    d.bitc.oen_sar_key = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG1 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG1_oen_sar_key] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG1_oen_sar_key(void)
{
    GH_ADC_AUX_ATOP_REG1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG1);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG1_oen_sar_key] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG1,value);
    #endif
    return tmp_value.bitc.oen_sar_key;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_AUX_ATOP_REG2 (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_AUX_ATOP_REG2(U32 data)
{
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,data,data);
    #endif
}
U32  GH_ADC_get_AUX_ATOP_REG2(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return value;
}
void GH_ADC_set_AUX_ATOP_REG2_sar_test(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.sar_test = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_sar_test] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_sar_test(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_sar_test] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.sar_test;
}
void GH_ADC_set_AUX_ATOP_REG2_TSI_RCTRL12(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.tsi_rctrl12 = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_TSI_RCTRL12] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_TSI_RCTRL12(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_TSI_RCTRL12] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.tsi_rctrl12;
}
void GH_ADC_set_AUX_ATOP_REG2_ENZYR(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzyr = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZYR] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENZYR(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZYR] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzyr;
}
void GH_ADC_set_AUX_ATOP_REG2_ENZYP(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzyp = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZYP] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENZYP(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZYP] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzyp;
}
void GH_ADC_set_AUX_ATOP_REG2_ENZXR(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzxr = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZXR] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENZXR(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZXR] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzxr;
}
void GH_ADC_set_AUX_ATOP_REG2_ENZXP(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzxp = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZXP] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENZXP(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZXP] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzxp;
}
void GH_ADC_set_AUX_ATOP_REG2_ENYN(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enyn = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENYN] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENYN(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENYN] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enyn;
}
void GH_ADC_set_AUX_ATOP_REG2_ENXN(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enxn = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENXN] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENXN(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENXN] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enxn;
}
void GH_ADC_set_AUX_ATOP_REG2_ENZOINT(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.enzoint = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_ENZOINT] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_ENZOINT(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_ENZOINT] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.enzoint;
}
void GH_ADC_set_AUX_ATOP_REG2_TSI_IS(U8 data)
{
    GH_ADC_AUX_ATOP_REG2_S d;
    d.all = *(volatile U32 *)REG_ADC_AUX_ATOP_REG2;
    d.bitc.tsi_is = data;
    *(volatile U32 *)REG_ADC_AUX_ATOP_REG2 = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_AUX_ATOP_REG2_TSI_IS] <-- 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,d.all,d.all);
    #endif
}
U8   GH_ADC_get_AUX_ATOP_REG2_TSI_IS(void)
{
    GH_ADC_AUX_ATOP_REG2_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_AUX_ATOP_REG2);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_AUX_ATOP_REG2_TSI_IS] --> 0x%08x\n",
                        REG_ADC_AUX_ATOP_REG2,value);
    #endif
    return tmp_value.bitc.tsi_is;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_Control(U32 data)
{
    *(volatile U32 *)REG_ADC_CONTROL = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control] <-- 0x%08x\n",
                        REG_ADC_CONTROL,data,data);
    #endif
}
U32  GH_ADC_get_Control(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return value;
}
void GH_ADC_set_Control_status(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.status = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_status] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
U8   GH_ADC_get_Control_status(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_status] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.status;
}
void GH_ADC_set_Control_start(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.start = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_start] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
U8   GH_ADC_get_Control_start(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_start] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.start;
}
void GH_ADC_set_Control_channel(U8 data)
{
    GH_ADC_CONTROL_S d;
    d.all = *(volatile U32 *)REG_ADC_CONTROL;
    d.bitc.channel = data;
    *(volatile U32 *)REG_ADC_CONTROL = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Control_channel] <-- 0x%08x\n",
                        REG_ADC_CONTROL,d.all,d.all);
    #endif
}
U8   GH_ADC_get_Control_channel(void)
{
    GH_ADC_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_ADC_CONTROL);

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Control_channel] --> 0x%08x\n",
                        REG_ADC_CONTROL,value);
    #endif
    return tmp_value.bitc.channel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_ReadData (read)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_ADC_get_ReadData(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_ADC_READDATA + index * FIO_MOFFSET(ADC,0x00000004)));

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_ReadData] --> 0x%08x\n",
                        (REG_ADC_READDATA + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_Enable(U32 data)
{
    *(volatile U32 *)REG_ADC_ENABLE = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_Enable] <-- 0x%08x\n",
                        REG_ADC_ENABLE,data,data);
    #endif
}
U32  GH_ADC_get_Enable(void)
{
    U32 value = (*(volatile U32 *)REG_ADC_ENABLE);

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_Enable] --> 0x%08x\n",
                        REG_ADC_ENABLE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register ADC_IntControl (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_ADC_set_IntControl(U8 index, U32 data)
{
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = data;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),data,data);
    #endif
}
U32  GH_ADC_get_IntControl(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return value;
}
void GH_ADC_set_IntControl_val_lo(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_val_lo] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_ADC_get_IntControl_val_lo(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_val_lo] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.val_lo;
}
void GH_ADC_set_IntControl_val_hi(U8 index, U16 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.val_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_val_hi] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_ADC_get_IntControl_val_hi(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_val_hi] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.val_hi;
}
void GH_ADC_set_IntControl_en_lo(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_lo = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_en_lo] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_ADC_get_IntControl_en_lo(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_en_lo] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.en_lo;
}
void GH_ADC_set_IntControl_en_hi(U8 index, U8 data)
{
    GH_ADC_INTCONTROL_S d;
    d.all = *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004));
    d.bitc.en_hi = data;
    *(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)) = d.all;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_ADC_set_IntControl_en_hi] <-- 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_ADC_get_IntControl_en_hi(U8 index)
{
    GH_ADC_INTCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)));

    tmp_value.all = value;
    #if GH_ADC_ENABLE_DEBUG_PRINT
    GH_ADC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_ADC_get_IntControl_en_hi] --> 0x%08x\n",
                        (REG_ADC_INTCONTROL + index * FIO_MOFFSET(ADC,0x00000004)),value);
    #endif
    return tmp_value.bitc.en_hi;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_ADC_init(void)
{
    int i;

    GH_ADC_set_AUX_ATOP_REG0((U32)0x00000000);
    GH_ADC_set_AUX_ATOP_REG1((U32)0x0000fff0);
    GH_ADC_set_AUX_ATOP_REG2((U32)0x00000075);
    GH_ADC_set_Control((U32)0x00000000);
    GH_ADC_set_Enable((U32)0x00000000);
    for (i=0; i<2; i++)
    {
        GH_ADC_set_IntControl(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

