/******************************************************************************
**
** \file      gh_vo_dve.c
**
** \brief     Digital Video Effect.
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
#include "gh_vo_dve.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_INC_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B0] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B0,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_INC_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B0] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_INC_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B1] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B1,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_INC_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B1] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_INC_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B2] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B2,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_INC_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B2] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_INC_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B3] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B3,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_INC_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B3] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B0 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_OFFSET_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B0] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B0,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_OFFSET_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B0] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B1 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_OFFSET_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B1] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B1,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_OFFSET_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B1] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B2 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_OFFSET_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B2] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B2,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_OFFSET_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B2] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B3 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PHASE_OFFSET_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B3] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B3,data,data);
    #endif
}
U8   GH_VO_DVE_get_PHASE_OFFSET_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B3] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CNFG_F(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_F = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,data,data);
    #endif
}
U8   GH_VO_DVE_get_CNFG_F(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return value;
}
void GH_VO_DVE_set_CNFG_F_reset(U8 data)
{
    GH_VO_DVE_CNFG_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F;
    d.bitc.reset = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F_reset] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_F_reset(void)
{
    GH_VO_DVE_CNFG_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F_reset] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return tmp_value.bitc.reset;
}
void GH_VO_DVE_set_CNFG_F_config(U8 data)
{
    GH_VO_DVE_CNFG_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F;
    d.bitc.config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F_config] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_F_config(void)
{
    GH_VO_DVE_CNFG_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F_config] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return tmp_value.bitc.config;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLACK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_BLACK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLACK_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BLACK_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_BLACK_LVL,data,data);
    #endif
}
U8   GH_VO_DVE_get_BLACK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLACK_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BLACK_LVL] --> 0x%08x\n",
                        REG_VO_DVE_BLACK_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLANK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_BLANK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLANK_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BLANK_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_BLANK_LVL,data,data);
    #endif
}
U8   GH_VO_DVE_get_BLANK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLANK_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BLANK_LVL] --> 0x%08x\n",
                        REG_VO_DVE_BLANK_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLAMP_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CLAMP_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CLAMP_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CLAMP_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_CLAMP_LVL,data,data);
    #endif
}
U8   GH_VO_DVE_get_CLAMP_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLAMP_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLAMP_LVL] --> 0x%08x\n",
                        REG_VO_DVE_CLAMP_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_LVL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_SYNC_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_LVL,data,data);
    #endif
}
U8   GH_VO_DVE_get_SYNC_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_LVL] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_Y (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CNFG_Y(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,data,data);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return value;
}
void GH_VO_DVE_set_CNFG_Y_gain(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_gain] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y_gain(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_gain] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.gain;
}
void GH_VO_DVE_set_CNFG_Y_LPF_select(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.lpf_select = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_LPF_select] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y_LPF_select(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_LPF_select] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.lpf_select;
}
void GH_VO_DVE_set_CNFG_Y_delay_config(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.delay_config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_delay_config] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y_delay_config(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_delay_config] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.delay_config;
}
void GH_VO_DVE_set_CNFG_Y_colorbar_en(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.colorbar_en = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_colorbar_en] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y_colorbar_en(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_colorbar_en] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.colorbar_en;
}
void GH_VO_DVE_set_CNFG_Y_interpolation_mode(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.interpolation_mode = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_interpolation_mode] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_Y_interpolation_mode(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_interpolation_mode] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.interpolation_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_O (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CNFG_O(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_O = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_O] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_O,data,data);
    #endif
}
U8   GH_VO_DVE_get_CNFG_O(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_O);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_O] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_O,value);
    #endif
    return value;
}
void GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV(U8 data)
{
    GH_VO_DVE_CNFG_O_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_O;
    d.bitc.y_tsel_yuv = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_O = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_O,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV(void)
{
    GH_VO_DVE_CNFG_O_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_O);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_O,value);
    #endif
    return tmp_value.bitc.y_tsel_yuv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_NBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_NBA = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBA] <-- 0x%08x\n",
                        REG_VO_DVE_NBA,data,data);
    #endif
}
U32  GH_VO_DVE_get_NBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_NBA);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBA] --> 0x%08x\n",
                        REG_VO_DVE_NBA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_PBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_PBA = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PBA] <-- 0x%08x\n",
                        REG_VO_DVE_PBA,data,data);
    #endif
}
U32  GH_VO_DVE_get_PBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_PBA);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PBA] --> 0x%08x\n",
                        REG_VO_DVE_PBA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CNFG_C(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_C = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_C] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_C,data,data);
    #endif
}
U8   GH_VO_DVE_get_CNFG_C(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_C);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_C] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_C,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INOUT_MODE (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_INOUT_MODE(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,data,data);
    #endif
}
U8   GH_VO_DVE_get_INOUT_MODE(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return value;
}
void GH_VO_DVE_set_INOUT_MODE_tencd_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.tencd_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_tencd_mode] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INOUT_MODE_tencd_mode(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_tencd_mode] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.tencd_mode;
}
void GH_VO_DVE_set_INOUT_MODE_tsync_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.tsync_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_tsync_mode] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INOUT_MODE_tsync_mode(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_tsync_mode] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.tsync_mode;
}
void GH_VO_DVE_set_INOUT_MODE_vsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.vsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_vsync] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INOUT_MODE_vsync(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_vsync] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.vsync;
}
void GH_VO_DVE_set_INOUT_MODE_hsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.hsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_hsync] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INOUT_MODE_hsync(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_hsync] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.hsync;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INPUT_SEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_INPUT_SEL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,data,data);
    #endif
}
U8   GH_VO_DVE_get_INPUT_SEL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return value;
}
void GH_VO_DVE_set_INPUT_SEL_delay(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_delay] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INPUT_SEL_delay(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_delay] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.delay;
}
void GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.t_fsync_phs = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.t_fsync_phs;
}
void GH_VO_DVE_set_INPUT_SEL_vsync_in(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.vsync_in = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_vsync_in] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INPUT_SEL_vsync_in(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_vsync_in] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.vsync_in;
}
void GH_VO_DVE_set_INPUT_SEL_clk_div(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.clk_div = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_clk_div] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_INPUT_SEL_clk_div(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_clk_div] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.clk_div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSYNC_OFF (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_VSYNC_OFF(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_VSYNC_OFF = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSYNC_OFF] <-- 0x%08x\n",
                        REG_VO_DVE_VSYNC_OFF,data,data);
    #endif
}
U8   GH_VO_DVE_get_VSYNC_OFF(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSYNC_OFF);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSYNC_OFF] --> 0x%08x\n",
                        REG_VO_DVE_VSYNC_OFF,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_H (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HSYNC_OFF_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_H] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_HSYNC_OFF_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_H] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_HSYNC_OFF_H_delay(U8 data)
{
    GH_VO_DVE_HSYNC_OFF_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_H_delay] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_HSYNC_OFF_H_delay(void)
{
    GH_VO_DVE_HSYNC_OFF_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_H_delay] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,value);
    #endif
    return tmp_value.bitc.delay;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_L (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HSYNC_OFF_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_L] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_HSYNC_OFF_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_L] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_H (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HLINE_LNGTH_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_H] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_HLINE_LNGTH_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_H] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_HLINE_LNGTH_H_HLC(U8 data)
{
    GH_VO_DVE_HLINE_LNGTH_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H;
    d.bitc.hlc = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_H_HLC] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_HLINE_LNGTH_H_HLC(void)
{
    GH_VO_DVE_HLINE_LNGTH_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_H_HLC] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,value);
    #endif
    return tmp_value.bitc.hlc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_L (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HLINE_LNGTH_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_L] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_HLINE_LNGTH_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_L] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CC_DATA_H(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_DATA_H] <-- 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)),data,data);
    #endif
}
U8   GH_VO_DVE_get_CC_DATA_H(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_DATA_H] --> 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CC_DATA_L(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_DATA_L] <-- 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)),data,data);
    #endif
}
U8   GH_VO_DVE_get_CC_DATA_L(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_DATA_L] --> 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_EN (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_CC_EN(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CC_EN = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,data,data);
    #endif
}
U8   GH_VO_DVE_get_CC_EN(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return value;
}
void GH_VO_DVE_set_CC_EN_odd(U8 data)
{
    GH_VO_DVE_CC_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN;
    d.bitc.odd = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN_odd] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CC_EN_odd(void)
{
    GH_VO_DVE_CC_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN_odd] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return tmp_value.bitc.odd;
}
void GH_VO_DVE_set_CC_EN_even(U8 data)
{
    GH_VO_DVE_CC_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN;
    d.bitc.even = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN_even] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_CC_EN_even(void)
{
    GH_VO_DVE_CC_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN_even] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return tmp_value.bitc.even;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N0 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N0] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N0,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N0] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N1 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N1] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N1,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N1] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N2 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N2] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N2,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N2] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N2,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N2_spacing(U8 data)
{
    GH_VO_DVE_MVP_N2_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N2;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N2 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N2_spacing] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N2,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N2_spacing(void)
{
    GH_VO_DVE_MVP_N2_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N2);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N2_spacing] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N2,value);
    #endif
    return tmp_value.bitc.spacing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N3 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N3] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N3,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N3] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N4 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N4(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N4 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N4] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N4,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N4(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N4);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N4] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N4,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N4_spacing(U8 data)
{
    GH_VO_DVE_MVP_N4_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N4;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N4 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N4_spacing] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N4,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N4_spacing(void)
{
    GH_VO_DVE_MVP_N4_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N4);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N4_spacing] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N4,value);
    #endif
    return tmp_value.bitc.spacing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N567 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N567(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N567(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N567_CSLN(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.csln = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSLN] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N567_CSLN(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSLN] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.csln;
}
void GH_VO_DVE_set_MVP_N567_CSNUM(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.csnum = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSNUM] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N567_CSNUM(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSNUM] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.csnum;
}
void GH_VO_DVE_set_MVP_N567_CSSP(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.cssp = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSSP] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N567_CSSP(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSSP] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.cssp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N8 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N8(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N8 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N8] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N8,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N8(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N8);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N8] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N8,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N8_PSD(U8 data)
{
    GH_VO_DVE_MVP_N8_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N8;
    d.bitc.psd = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N8 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N8_PSD] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N8,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N8_PSD(void)
{
    GH_VO_DVE_MVP_N8_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N8);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N8_PSD] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N8,value);
    #endif
    return tmp_value.bitc.psd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N9 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N9(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N9 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N9] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N9,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N9(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N9);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N9] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N9,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N9_PSL(U8 data)
{
    GH_VO_DVE_MVP_N9_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N9;
    d.bitc.psl = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N9 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N9_PSL] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N9,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N9_PSL(void)
{
    GH_VO_DVE_MVP_N9_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N9);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N9_PSL] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N9,value);
    #endif
    return tmp_value.bitc.psl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N10 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N10(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N10 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N10] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N10,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N10(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N10);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N10] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N10,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N10_PSS(U8 data)
{
    GH_VO_DVE_MVP_N10_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N10;
    d.bitc.pss = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N10 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N10_PSS] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N10,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N10_PSS(void)
{
    GH_VO_DVE_MVP_N10_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N10);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N10_PSS] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N10,value);
    #endif
    return tmp_value.bitc.pss;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N11_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N11_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N11_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N11_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N11_H;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_H_sync_line] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N11_H_sync_line(void)
{
    GH_VO_DVE_MVP_N11_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_H_sync_line] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,value);
    #endif
    return tmp_value.bitc.sync_line;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N11_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N11_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N11_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N12_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N12_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N12_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N12_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N12_H;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_H_sync_line] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N12_H_sync_line(void)
{
    GH_VO_DVE_MVP_N12_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_H_sync_line] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,value);
    #endif
    return tmp_value.bitc.sync_line;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N12_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N12_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N12_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N13 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N13(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N13 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N13] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N13,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N13(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N13);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N13] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N13,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N14 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N14(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N14 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N14] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N14,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N14(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N14);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N14] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N14,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N15 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N15(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N15 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N15] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N15,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N15(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N15);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N15] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N15,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_12 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_BURST_ZONE_12(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,data,data);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_12(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return value;
}
void GH_VO_DVE_set_BURST_ZONE_12_zone2(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12;
    d.bitc.zone2 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12_zone2] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_12_zone2(void)
{
    GH_VO_DVE_BURST_ZONE_12_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12_zone2] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return tmp_value.bitc.zone2;
}
void GH_VO_DVE_set_BURST_ZONE_12_zone1(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12;
    d.bitc.zone1 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12_zone1] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_12_zone1(void)
{
    GH_VO_DVE_BURST_ZONE_12_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12_zone1] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return tmp_value.bitc.zone1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_EN (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_BURST_ZONE_EN(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,data,data);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_EN(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return value;
}
void GH_VO_DVE_set_BURST_ZONE_EN_invert(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_invert] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_EN_invert(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_invert] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.invert;
}
void GH_VO_DVE_set_BURST_ZONE_EN_advanced(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.advanced = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_advanced] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_EN_advanced(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_advanced] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.advanced;
}
void GH_VO_DVE_set_BURST_ZONE_EN_zone3(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.zone3 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_zone3] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_BURST_ZONE_EN_zone3(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_zone3] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.zone3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N21_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N21_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N21_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MVP_N21_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_MVP_N21_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_MVP_N21_H_invert(U8 data)
{
    GH_VO_DVE_MVP_N21_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N21_H;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_H_invert] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_MVP_N21_H_invert(void)
{
    GH_VO_DVE_MVP_N21_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_H_invert] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,value);
    #endif
    return tmp_value.bitc.invert;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_TEST_F(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_F = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_F] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_F,data,data);
    #endif
}
U8   GH_VO_DVE_get_TEST_F(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_F);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_F] --> 0x%08x\n",
                        REG_VO_DVE_TEST_F,value);
    #endif
    return value;
}
void GH_VO_DVE_set_TEST_F_enable(U8 data)
{
    GH_VO_DVE_TEST_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_F;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DVE_TEST_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_F_enable] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_F,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_TEST_F_enable(void)
{
    GH_VO_DVE_TEST_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_F_enable] --> 0x%08x\n",
                        REG_VO_DVE_TEST_F,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_YO (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_TEST_YO(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_YO = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,data,data);
    #endif
}
U8   GH_VO_DVE_get_TEST_YO(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return value;
}
void GH_VO_DVE_set_TEST_YO_ou(U8 data)
{
    GH_VO_DVE_TEST_YO_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO;
    d.bitc.ou = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO_ou] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_TEST_YO_ou(void)
{
    GH_VO_DVE_TEST_YO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO_ou] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return tmp_value.bitc.ou;
}
void GH_VO_DVE_set_TEST_YO_yu(U8 data)
{
    GH_VO_DVE_TEST_YO_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO;
    d.bitc.yu = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO_yu] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_TEST_YO_yu(void)
{
    GH_VO_DVE_TEST_YO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO_yu] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return tmp_value.bitc.yu;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_TEST_C(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_C = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_C] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_C,data,data);
    #endif
}
U8   GH_VO_DVE_get_TEST_C(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_C);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_C] --> 0x%08x\n",
                        REG_VO_DVE_TEST_C,value);
    #endif
    return value;
}
void GH_VO_DVE_set_TEST_C_channel(U8 data)
{
    GH_VO_DVE_TEST_C_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_C;
    d.bitc.channel = data;
    *(volatile U8 *)REG_VO_DVE_TEST_C = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_C_channel] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_C,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_TEST_C_channel(void)
{
    GH_VO_DVE_TEST_C_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_C);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_C_channel] --> 0x%08x\n",
                        REG_VO_DVE_TEST_C,value);
    #endif
    return tmp_value.bitc.channel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MACV_TEST (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_MACV_TEST(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MACV_TEST = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MACV_TEST] <-- 0x%08x\n",
                        REG_VO_DVE_MACV_TEST,data,data);
    #endif
}
U8   GH_VO_DVE_get_MACV_TEST(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MACV_TEST);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MACV_TEST] --> 0x%08x\n",
                        REG_VO_DVE_MACV_TEST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_H (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HLINE_VRST_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_H] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,data,data);
    #endif
}
U8   GH_VO_DVE_get_HLINE_VRST_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_H] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,value);
    #endif
    return value;
}
void GH_VO_DVE_set_HLINE_VRST_H_HLR(U8 data)
{
    GH_VO_DVE_HLINE_VRST_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H;
    d.bitc.hlr = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_H_HLR] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_HLINE_VRST_H_HLR(void)
{
    GH_VO_DVE_HLINE_VRST_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_H_HLR] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,value);
    #endif
    return tmp_value.bitc.hlr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_L (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_HLINE_VRST_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_L] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_L,data,data);
    #endif
}
U8   GH_VO_DVE_get_HLINE_VRST_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_L] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSM_VRST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_VSM_VRST(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_VSM_VRST = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSM_VRST] <-- 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,data,data);
    #endif
}
U8   GH_VO_DVE_get_VSM_VRST(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSM_VRST);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSM_VRST] --> 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,value);
    #endif
    return value;
}
void GH_VO_DVE_set_VSM_VRST_VSMR(U8 data)
{
    GH_VO_DVE_VSM_VRST_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_VSM_VRST;
    d.bitc.vsmr = data;
    *(volatile U8 *)REG_VO_DVE_VSM_VRST = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSM_VRST_VSMR] <-- 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_VSM_VRST_VSMR(void)
{
    GH_VO_DVE_VSM_VRST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSM_VRST);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSM_VRST_VSMR] --> 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,value);
    #endif
    return tmp_value.bitc.vsmr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_START (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_SYNC_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_START] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_START,data,data);
    #endif
}
U8   GH_VO_DVE_get_SYNC_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_START] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_START,value);
    #endif
    return value;
}
void GH_VO_DVE_set_SYNC_START_start(U8 data)
{
    GH_VO_DVE_SYNC_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_START,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_SYNC_START_start(void)
{
    GH_VO_DVE_SYNC_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_START_start] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_END (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_SYNC_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_END] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_END,data,data);
    #endif
}
U8   GH_VO_DVE_get_SYNC_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_END] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_END,value);
    #endif
    return value;
}
void GH_VO_DVE_set_SYNC_END_end(U8 data)
{
    GH_VO_DVE_SYNC_END_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_END;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_END = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_END_end] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_END,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_SYNC_END_end(void)
{
    GH_VO_DVE_SYNC_END_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_END);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_END_end] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_END,value);
    #endif
    return tmp_value.bitc.end;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_SREND (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_SYNC_SREND(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_SREND = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_SREND] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_SREND,data,data);
    #endif
}
U8   GH_VO_DVE_get_SYNC_SREND(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_SREND);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_SREND] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_SREND,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_EQEND (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_SYNC_EQEND(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_EQEND] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,data,data);
    #endif
}
U8   GH_VO_DVE_get_SYNC_EQEND(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_EQEND] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,value);
    #endif
    return value;
}
void GH_VO_DVE_set_SYNC_EQEND_end(U8 data)
{
    GH_VO_DVE_SYNC_EQEND_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_EQEND;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_EQEND_end] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_SYNC_EQEND_end(void)
{
    GH_VO_DVE_SYNC_EQEND_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_EQEND_end] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,value);
    #endif
    return tmp_value.bitc.end;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_ACTIVE_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_ACTIVE_START] <-- 0x%08x\n",
                        REG_VO_DVE_ACTIVE_START,data,data);
    #endif
}
U8   GH_VO_DVE_get_ACTIVE_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_ACTIVE_START] --> 0x%08x\n",
                        REG_VO_DVE_ACTIVE_START,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_ACTIVE_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_ACTIVE_END] <-- 0x%08x\n",
                        REG_VO_DVE_ACTIVE_END,data,data);
    #endif
}
U8   GH_VO_DVE_get_ACTIVE_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_ACTIVE_END] --> 0x%08x\n",
                        REG_VO_DVE_ACTIVE_END,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_WBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_WBRST_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_WBRST_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_WBRST_START] <-- 0x%08x\n",
                        REG_VO_DVE_WBRST_START,data,data);
    #endif
}
U8   GH_VO_DVE_get_WBRST_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_WBRST_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_WBRST_START] --> 0x%08x\n",
                        REG_VO_DVE_WBRST_START,value);
    #endif
    return value;
}
void GH_VO_DVE_set_WBRST_START_start(U8 data)
{
    GH_VO_DVE_WBRST_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_WBRST_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_WBRST_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_WBRST_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_WBRST_START,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_WBRST_START_start(void)
{
    GH_VO_DVE_WBRST_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_WBRST_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_WBRST_START_start] --> 0x%08x\n",
                        REG_VO_DVE_WBRST_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_NBRST_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_NBRST_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_START] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_START,data,data);
    #endif
}
U8   GH_VO_DVE_get_NBRST_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_START] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_START,value);
    #endif
    return value;
}
void GH_VO_DVE_set_NBRST_START_start(U8 data)
{
    GH_VO_DVE_NBRST_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_NBRST_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_NBRST_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_START,d.all,d.all);
    #endif
}
U8   GH_VO_DVE_get_NBRST_START_start(void)
{
    GH_VO_DVE_NBRST_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_START_start] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_DVE_set_NBRST_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_NBRST_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_END] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_END,data,data);
    #endif
}
U8   GH_VO_DVE_get_NBRST_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_END] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_END,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLOSED_CAPTION (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U8   GH_VO_DVE_get_CLOSED_CAPTION(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return value;
}
U8   GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return tmp_value.bitc.edstat;
}
U8   GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return tmp_value.bitc.ccstat;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_DVE_init(void)
{
    int i;

    GH_VO_DVE_set_PHASE_INC_B0((U8)0x0000001f);
    GH_VO_DVE_set_PHASE_INC_B1((U8)0x0000007c);
    GH_VO_DVE_set_PHASE_INC_B2((U8)0x000000f0);
    GH_VO_DVE_set_PHASE_INC_B3((U8)0x00000021);
    GH_VO_DVE_set_PHASE_OFFSET_B0((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B1((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B2((U8)0x00000000);
    GH_VO_DVE_set_PHASE_OFFSET_B3((U8)0x00000000);
    GH_VO_DVE_set_CNFG_F((U8)0x00000000);
    GH_VO_DVE_set_BLACK_LVL((U8)0x00000000);
    GH_VO_DVE_set_BLANK_LVL((U8)0x00000000);
    GH_VO_DVE_set_CLAMP_LVL((U8)0x00000000);
    GH_VO_DVE_set_SYNC_LVL((U8)0x00000000);
    GH_VO_DVE_set_CNFG_Y((U8)0x00000010);
    GH_VO_DVE_set_CNFG_O((U8)0x00000000);
    GH_VO_DVE_set_NBA((U32)0x000000c8);
    GH_VO_DVE_set_PBA((U32)0x00000000);
    GH_VO_DVE_set_CNFG_C((U8)0x00000000);
    GH_VO_DVE_set_INOUT_MODE((U8)0x00000030);
    GH_VO_DVE_set_INPUT_SEL((U8)0x00000000);
    GH_VO_DVE_set_VSYNC_OFF((U8)0x00000000);
    GH_VO_DVE_set_HSYNC_OFF_H((U8)0x00000000);
    GH_VO_DVE_set_HSYNC_OFF_L((U8)0x00000000);
    GH_VO_DVE_set_HLINE_LNGTH_H((U8)0x00000000);
    GH_VO_DVE_set_HLINE_LNGTH_L((U8)0x00000000);
    for (i=0; i<2; i++)
    {
        GH_VO_DVE_set_CC_DATA_H(i, (U8)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_VO_DVE_set_CC_DATA_L(i, (U8)0x00000000);
    }
    GH_VO_DVE_set_CC_EN((U8)0x00000000);
    GH_VO_DVE_set_MVP_N0((U8)0x0000003e);
    GH_VO_DVE_set_MVP_N1((U8)0x0000002e);
    GH_VO_DVE_set_MVP_N2((U8)0x00000015);
    GH_VO_DVE_set_MVP_N3((U8)0x0000002e);
    GH_VO_DVE_set_MVP_N4((U8)0x00000015);
    GH_VO_DVE_set_MVP_N567((U8)0x000000b6);
    GH_VO_DVE_set_MVP_N8((U8)0x0000001b);
    GH_VO_DVE_set_MVP_N9((U8)0x0000001b);
    GH_VO_DVE_set_MVP_N10((U8)0x00000024);
    GH_VO_DVE_set_MVP_N11_H((U8)0x00000024);
    GH_VO_DVE_set_MVP_N11_L((U8)0x000000e0);
    GH_VO_DVE_set_MVP_N12_H((U8)0x00000000);
    GH_VO_DVE_set_MVP_N12_L((U8)0x00000000);
    GH_VO_DVE_set_MVP_N13((U8)0x0000000f);
    GH_VO_DVE_set_MVP_N14((U8)0x0000000f);
    GH_VO_DVE_set_MVP_N15((U8)0x00000060);
    GH_VO_DVE_set_BURST_ZONE_12((U8)0x000000a0);
    GH_VO_DVE_set_BURST_ZONE_EN((U8)0x0000005c);
    GH_VO_DVE_set_MVP_N21_L((U8)0x000000ff);
    GH_VO_DVE_set_MVP_N21_H((U8)0x00000003);
    GH_VO_DVE_set_TEST_F((U8)0x00000000);
    GH_VO_DVE_set_TEST_YO((U8)0x00000000);
    GH_VO_DVE_set_TEST_C((U8)0x00000000);
    GH_VO_DVE_set_MACV_TEST((U8)0x00000000);
    GH_VO_DVE_set_HLINE_VRST_H((U8)0x00000000);
    GH_VO_DVE_set_HLINE_VRST_L((U8)0x00000000);
    GH_VO_DVE_set_VSM_VRST((U8)0x00000010);
    GH_VO_DVE_set_SYNC_START((U8)0x0000000c);
    GH_VO_DVE_set_SYNC_END((U8)0x0000004c);
    GH_VO_DVE_set_SYNC_SREND((U8)0x00000079);
    GH_VO_DVE_set_SYNC_EQEND((U8)0x0000002c);
    GH_VO_DVE_set_ACTIVE_START((U8)0x00000089);
    GH_VO_DVE_set_ACTIVE_END((U8)0x000000a4);
    GH_VO_DVE_set_WBRST_START((U8)0x0000005a);
    GH_VO_DVE_set_NBRST_START((U8)0x00000062);
    GH_VO_DVE_set_NBRST_END((U8)0x00000084);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

