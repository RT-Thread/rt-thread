/******************************************************************************
**
** \file      gh_timer.c
**
** \brief     TIMER.
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
#include "gh_timer.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register TIMER_T1CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T1CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T1CNTNSTS,data,data);
    #endif
}
U32  GH_TIMER_get_T1CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1CntnSts] --> 0x%08x\n",
                        REG_TIMER_T1CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T1Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Match1] <-- 0x%08x\n",
                        REG_TIMER_T1MATCH1,data,data);
    #endif
}
U32  GH_TIMER_get_T1Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Match1] --> 0x%08x\n",
                        REG_TIMER_T1MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T1Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Match2] <-- 0x%08x\n",
                        REG_TIMER_T1MATCH2,data,data);
    #endif
}
U32  GH_TIMER_get_T1Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Match2] --> 0x%08x\n",
                        REG_TIMER_T1MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_Control(U32 data)
{
    *(volatile U32 *)REG_TIMER_CONTROL = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,data,data);
    #endif
}
U32  GH_TIMER_get_Control(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return value;
}
void GH_TIMER_set_Control_ClkSel3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_ClkSel3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel3;
}
void GH_TIMER_set_Control_ClkSel2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_ClkSel2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel2;
}
void GH_TIMER_set_Control_ClkSel1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.clksel1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_ClkSel1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_ClkSel1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_ClkSel1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.clksel1;
}
void GH_TIMER_set_Control_OF3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_OF3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of3;
}
void GH_TIMER_set_Control_OF2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_OF2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of2;
}
void GH_TIMER_set_Control_OF1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.of1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_OF1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_OF1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_OF1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.of1;
}
void GH_TIMER_set_Control_Enable3(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable3 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable3] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_Enable3(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable3] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable3;
}
void GH_TIMER_set_Control_Enable2(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable2 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable2] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_Enable2(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable2] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable2;
}
void GH_TIMER_set_Control_Enable1(U8 data)
{
    GH_TIMER_CONTROL_S d;
    d.all = *(volatile U32 *)REG_TIMER_CONTROL;
    d.bitc.enable1 = data;
    *(volatile U32 *)REG_TIMER_CONTROL = d.all;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_Control_Enable1] <-- 0x%08x\n",
                        REG_TIMER_CONTROL,d.all,d.all);
    #endif
}
U8   GH_TIMER_get_Control_Enable1(void)
{
    GH_TIMER_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_TIMER_CONTROL);

    tmp_value.all = value;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_Control_Enable1] --> 0x%08x\n",
                        REG_TIMER_CONTROL,value);
    #endif
    return tmp_value.bitc.enable1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T2CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T2CNTNSTS,data,data);
    #endif
}
U32  GH_TIMER_get_T2CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2CntnSts] --> 0x%08x\n",
                        REG_TIMER_T2CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T2Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Match1] <-- 0x%08x\n",
                        REG_TIMER_T2MATCH1,data,data);
    #endif
}
U32  GH_TIMER_get_T2Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Match1] --> 0x%08x\n",
                        REG_TIMER_T2MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T2Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Match2] <-- 0x%08x\n",
                        REG_TIMER_T2MATCH2,data,data);
    #endif
}
U32  GH_TIMER_get_T2Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Match2] --> 0x%08x\n",
                        REG_TIMER_T2MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3CntnSts (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T3CntnSts(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3CNTNSTS = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3CntnSts] <-- 0x%08x\n",
                        REG_TIMER_T3CNTNSTS,data,data);
    #endif
}
U32  GH_TIMER_get_T3CntnSts(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3CNTNSTS);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3CntnSts] --> 0x%08x\n",
                        REG_TIMER_T3CNTNSTS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Match1 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T3Match1(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3MATCH1 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Match1] <-- 0x%08x\n",
                        REG_TIMER_T3MATCH1,data,data);
    #endif
}
U32  GH_TIMER_get_T3Match1(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3MATCH1);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Match1] --> 0x%08x\n",
                        REG_TIMER_T3MATCH1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Match2 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T3Match2(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3MATCH2 = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Match2] <-- 0x%08x\n",
                        REG_TIMER_T3MATCH2,data,data);
    #endif
}
U32  GH_TIMER_get_T3Match2(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3MATCH2);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Match2] --> 0x%08x\n",
                        REG_TIMER_T3MATCH2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T1Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T1Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T1RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T1Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T1RELOADN,data,data);
    #endif
}
U32  GH_TIMER_get_T1Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T1RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T1Reloadn] --> 0x%08x\n",
                        REG_TIMER_T1RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T2Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T2Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T2RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T2Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T2RELOADN,data,data);
    #endif
}
U32  GH_TIMER_get_T2Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T2RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T2Reloadn] --> 0x%08x\n",
                        REG_TIMER_T2RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register TIMER_T3Reloadn (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_TIMER_set_T3Reloadn(U32 data)
{
    *(volatile U32 *)REG_TIMER_T3RELOADN = data;
    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_TIMER_set_T3Reloadn] <-- 0x%08x\n",
                        REG_TIMER_T3RELOADN,data,data);
    #endif
}
U32  GH_TIMER_get_T3Reloadn(void)
{
    U32 value = (*(volatile U32 *)REG_TIMER_T3RELOADN);

    #if GH_TIMER_ENABLE_DEBUG_PRINT
    GH_TIMER_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_TIMER_get_T3Reloadn] --> 0x%08x\n",
                        REG_TIMER_T3RELOADN,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_TIMER_init(void)
{
    GH_TIMER_set_T1CntnSts((U32)0x00000000);
    GH_TIMER_set_T1Match1((U32)0x00000000);
    GH_TIMER_set_T1Match2((U32)0x00000000);
    GH_TIMER_set_Control((U32)0x00000000);
    GH_TIMER_set_T2CntnSts((U32)0x00000000);
    GH_TIMER_set_T2Match1((U32)0x00000000);
    GH_TIMER_set_T2Match2((U32)0x00000000);
    GH_TIMER_set_T3CntnSts((U32)0x00000000);
    GH_TIMER_set_T3Match1((U32)0x00000000);
    GH_TIMER_set_T3Match2((U32)0x00000000);
    GH_TIMER_set_T1Reloadn((U32)0x00000000);
    GH_TIMER_set_T2Reloadn((U32)0x00000000);
    GH_TIMER_set_T3Reloadn((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

