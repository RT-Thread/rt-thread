/******************************************************************************
**
** \file      gh_vo_top.c
**
** \brief     TOP control Registers.
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
#include "gh_vo_top.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_TOP_RESET_VOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_RESET_VOUT(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_RESET_VOUT] <-- 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,data,data);
    #endif
}
U32  GH_VO_TOP_get_RESET_VOUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_RESET_VOUT] --> 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,value);
    #endif
    return value;
}
void GH_VO_TOP_set_RESET_VOUT_reset(U8 data)
{
    GH_VO_TOP_RESET_VOUT_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_RESET_VOUT;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_TOP_RESET_VOUT = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_RESET_VOUT_reset] <-- 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_RESET_VOUT_reset(void)
{
    GH_VO_TOP_RESET_VOUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_RESET_VOUT);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_RESET_VOUT_reset] --> 0x%08x\n",
                        REG_VO_TOP_RESET_VOUT,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_A (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_ENABLE_CLOCK_A(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_A] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,data,data);
    #endif
}
U32  GH_VO_TOP_get_ENABLE_CLOCK_A(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_A] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,value);
    #endif
    return value;
}
void GH_VO_TOP_set_ENABLE_CLOCK_A_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_A_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_A_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_ENABLE_CLOCK_A_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_A_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_A);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_A_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_A,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_B (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_ENABLE_CLOCK_B(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_B] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,data,data);
    #endif
}
U32  GH_VO_TOP_get_ENABLE_CLOCK_B(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_B] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,value);
    #endif
    return value;
}
void GH_VO_TOP_set_ENABLE_CLOCK_B_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_B_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_B_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_ENABLE_CLOCK_B_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_B_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_B);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_B_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_B,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_OSDR (read/write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_OSDR] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,data,data);
    #endif
}
U32  GH_VO_TOP_get_ENABLE_CLOCK_OSDR(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_OSDR] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,value);
    #endif
    return value;
}
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable(void)
{
    GH_VO_TOP_ENABLE_CLOCK_OSDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CLOCK_OSDR);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CLOCK_OSDR,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,data,data);
    #endif
}
U32  GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,value);
    #endif
    return value;
}
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CONFIG_CLOCK_GATING (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING(U32 data)
{
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING = data;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,data,data);
    #endif
}
U32  GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING(void)
{
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING);

    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,value);
    #endif
    return value;
}
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable(U8 data)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S d;
    d.all = *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING = d.all;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable] <-- 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,d.all,d.all);
    #endif
}
U8   GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable(void)
{
    GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING);

    tmp_value.all = value;
    #if GH_VO_TOP_ENABLE_DEBUG_PRINT
    GH_VO_TOP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable] --> 0x%08x\n",
                        REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_TOP_init(void)
{
    GH_VO_TOP_set_RESET_VOUT((U32)0x00000000);
    GH_VO_TOP_set_ENABLE_CLOCK_A((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_CLOCK_B((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_CLOCK_OSDR((U32)0x00000001);
    GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING((U32)0x00000000);
    GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

