/******************************************************************************
**
** \file      gh_vo_mixer1.c
**
** \brief     VO Mixer B access function.
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
#include "gh_vo_mixer1.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_CONTROL (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_CONTROL = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_CONTROL] <-- 0x%08x\n",
                        REG_VO_MIXER1_CONTROL,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_CONTROL);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_CONTROL] --> 0x%08x\n",
                        REG_VO_MIXER1_CONTROL,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_CONTROL_Reset(U8 data)
{
    GH_VO_MIXER1_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_CONTROL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_MIXER1_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_CONTROL_Reset] <-- 0x%08x\n",
                        REG_VO_MIXER1_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_CONTROL_Reset(void)
{
    GH_VO_MIXER1_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_CONTROL_Reset] --> 0x%08x\n",
                        REG_VO_MIXER1_CONTROL,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_STATUS (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_VO_MIXER1_get_STATUS(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_STATUS);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_STATUS] --> 0x%08x\n",
                        REG_VO_MIXER1_STATUS,value);
    #endif
    return value;
}
U8   GH_VO_MIXER1_get_STATUS_Reset(void)
{
    GH_VO_MIXER1_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_STATUS);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_STATUS_Reset] --> 0x%08x\n",
                        REG_VO_MIXER1_STATUS,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_ACTIVE_SIZE (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_ACTIVE_SIZE(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ACTIVE_SIZE] <-- 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_ACTIVE_SIZE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ACTIVE_SIZE] --> 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_ACTIVE_SIZE_Vertical(U16 data)
{
    GH_VO_MIXER1_ACTIVE_SIZE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ACTIVE_SIZE_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_ACTIVE_SIZE_Vertical(void)
{
    GH_VO_MIXER1_ACTIVE_SIZE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ACTIVE_SIZE_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,value);
    #endif
    return tmp_value.bitc.vertical;
}
void GH_VO_MIXER1_set_ACTIVE_SIZE_Horizontal(U16 data)
{
    GH_VO_MIXER1_ACTIVE_SIZE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ACTIVE_SIZE_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_ACTIVE_SIZE_Horizontal(void)
{
    GH_VO_MIXER1_ACTIVE_SIZE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ACTIVE_SIZE);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ACTIVE_SIZE_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER1_ACTIVE_SIZE,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_VIDEO_START (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_VIDEO_START(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_START = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_START] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_VIDEO_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_START);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_START] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_VIDEO_START_Vertical(U16 data)
{
    GH_VO_MIXER1_VIDEO_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_VIDEO_START;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_START = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_START_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_VIDEO_START_Vertical(void)
{
    GH_VO_MIXER1_VIDEO_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_START);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_START_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,value);
    #endif
    return tmp_value.bitc.vertical;
}
void GH_VO_MIXER1_set_VIDEO_START_Horizontal(U16 data)
{
    GH_VO_MIXER1_VIDEO_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_VIDEO_START;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_START = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_START_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_VIDEO_START_Horizontal(void)
{
    GH_VO_MIXER1_VIDEO_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_START);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_START_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_START,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_VIDEO_END (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_VIDEO_END(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_END = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_END] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_VIDEO_END(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_END);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_END] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_VIDEO_END_Vertical(U16 data)
{
    GH_VO_MIXER1_VIDEO_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_VIDEO_END;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_END = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_END_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_VIDEO_END_Vertical(void)
{
    GH_VO_MIXER1_VIDEO_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_END);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_END_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,value);
    #endif
    return tmp_value.bitc.vertical;
}
void GH_VO_MIXER1_set_VIDEO_END_Horizontal(U16 data)
{
    GH_VO_MIXER1_VIDEO_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_VIDEO_END;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER1_VIDEO_END = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_VIDEO_END_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_VIDEO_END_Horizontal(void)
{
    GH_VO_MIXER1_VIDEO_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_VIDEO_END);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_VIDEO_END_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER1_VIDEO_END,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_OSD_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_OSD_START(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_OSD_START = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_START] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_OSD_START(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_START);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_START] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_OSD_START_Vertical(U16 data)
{
    GH_VO_MIXER1_OSD_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_START;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_START = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_START_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_OSD_START_Vertical(void)
{
    GH_VO_MIXER1_OSD_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_START);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_START_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,value);
    #endif
    return tmp_value.bitc.vertical;
}
void GH_VO_MIXER1_set_OSD_START_Horizontal(U16 data)
{
    GH_VO_MIXER1_OSD_START_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_START;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_START = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_START_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_OSD_START_Horizontal(void)
{
    GH_VO_MIXER1_OSD_START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_START);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_START_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_START,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_OSD_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_OSD_END(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_OSD_END = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_END] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_OSD_END(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_END);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_END] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_OSD_END_Vertical(U16 data)
{
    GH_VO_MIXER1_OSD_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_END;
    d.bitc.vertical = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_END = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_END_Vertical] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_OSD_END_Vertical(void)
{
    GH_VO_MIXER1_OSD_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_END);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_END_Vertical] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,value);
    #endif
    return tmp_value.bitc.vertical;
}
void GH_VO_MIXER1_set_OSD_END_Horizontal(U16 data)
{
    GH_VO_MIXER1_OSD_END_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_END;
    d.bitc.horizontal = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_END = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_END_Horizontal] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_OSD_END_Horizontal(void)
{
    GH_VO_MIXER1_OSD_END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_END);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_END_Horizontal] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_END,value);
    #endif
    return tmp_value.bitc.horizontal;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_BACKGROUND (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_BACKGROUND(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_BACKGROUND = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_BACKGROUND] <-- 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_BACKGROUND(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_BACKGROUND);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_BACKGROUND] --> 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_BACKGROUND_V(U8 data)
{
    GH_VO_MIXER1_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_BACKGROUND;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER1_BACKGROUND = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_BACKGROUND_V] <-- 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_BACKGROUND_V(void)
{
    GH_VO_MIXER1_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_BACKGROUND_V] --> 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,value);
    #endif
    return tmp_value.bitc.v;
}
void GH_VO_MIXER1_set_BACKGROUND_U(U8 data)
{
    GH_VO_MIXER1_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_BACKGROUND;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER1_BACKGROUND = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_BACKGROUND_U] <-- 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_BACKGROUND_U(void)
{
    GH_VO_MIXER1_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_BACKGROUND_U] --> 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,value);
    #endif
    return tmp_value.bitc.u;
}
void GH_VO_MIXER1_set_BACKGROUND_Y(U8 data)
{
    GH_VO_MIXER1_BACKGROUND_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_BACKGROUND;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER1_BACKGROUND = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_BACKGROUND_Y] <-- 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_BACKGROUND_Y(void)
{
    GH_VO_MIXER1_BACKGROUND_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_BACKGROUND);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_BACKGROUND_Y] --> 0x%08x\n",
                        REG_VO_MIXER1_BACKGROUND,value);
    #endif
    return tmp_value.bitc.y;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_HIGHLIGHT (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_HIGHLIGHT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_HIGHLIGHT] <-- 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_HIGHLIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_HIGHLIGHT] --> 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_HIGHLIGHT_V(U8 data)
{
    GH_VO_MIXER1_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT;
    d.bitc.v = data;
    *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_HIGHLIGHT_V] <-- 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_HIGHLIGHT_V(void)
{
    GH_VO_MIXER1_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_HIGHLIGHT_V] --> 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.v;
}
void GH_VO_MIXER1_set_HIGHLIGHT_U(U8 data)
{
    GH_VO_MIXER1_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT;
    d.bitc.u = data;
    *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_HIGHLIGHT_U] <-- 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_HIGHLIGHT_U(void)
{
    GH_VO_MIXER1_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_HIGHLIGHT_U] --> 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.u;
}
void GH_VO_MIXER1_set_HIGHLIGHT_Y(U8 data)
{
    GH_VO_MIXER1_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT;
    d.bitc.y = data;
    *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_HIGHLIGHT_Y] <-- 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_HIGHLIGHT_Y(void)
{
    GH_VO_MIXER1_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_HIGHLIGHT_Y] --> 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.y;
}
void GH_VO_MIXER1_set_HIGHLIGHT_threshold(U8 data)
{
    GH_VO_MIXER1_HIGHLIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT;
    d.bitc.threshold = data;
    *(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_HIGHLIGHT_threshold] <-- 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_HIGHLIGHT_threshold(void)
{
    GH_VO_MIXER1_HIGHLIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_HIGHLIGHT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_HIGHLIGHT_threshold] --> 0x%08x\n",
                        REG_VO_MIXER1_HIGHLIGHT,value);
    #endif
    return tmp_value.bitc.threshold;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_OSD_CONTROL (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_OSD_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_OSD_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_OSD_CONTROL_Global_Blend(U8 data)
{
    GH_VO_MIXER1_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL;
    d.bitc.global_blend = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL_Global_Blend] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OSD_CONTROL_Global_Blend(void)
{
    GH_VO_MIXER1_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL_Global_Blend] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.global_blend;
}
void GH_VO_MIXER1_set_OSD_CONTROL_Premultiplied(U8 data)
{
    GH_VO_MIXER1_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL;
    d.bitc.premultiplied = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL_Premultiplied] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OSD_CONTROL_Premultiplied(void)
{
    GH_VO_MIXER1_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL_Premultiplied] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.premultiplied;
}
void GH_VO_MIXER1_set_OSD_CONTROL_Mode(U8 data)
{
    GH_VO_MIXER1_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL_Mode] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OSD_CONTROL_Mode(void)
{
    GH_VO_MIXER1_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL_Mode] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.mode;
}
void GH_VO_MIXER1_set_OSD_CONTROL_Enable_Transparent_Color(U8 data)
{
    GH_VO_MIXER1_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL;
    d.bitc.enable_transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL_Enable_Transparent_Color] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OSD_CONTROL_Enable_Transparent_Color(void)
{
    GH_VO_MIXER1_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL_Enable_Transparent_Color] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.enable_transparent_color;
}
void GH_VO_MIXER1_set_OSD_CONTROL_Transparent_Color(U16 data)
{
    GH_VO_MIXER1_OSD_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL;
    d.bitc.transparent_color = data;
    *(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OSD_CONTROL_Transparent_Color] <-- 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,d.all,d.all);
    #endif
}
U16  GH_VO_MIXER1_get_OSD_CONTROL_Transparent_Color(void)
{
    GH_VO_MIXER1_OSD_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OSD_CONTROL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OSD_CONTROL_Transparent_Color] --> 0x%08x\n",
                        REG_VO_MIXER1_OSD_CONTROL,value);
    #endif
    return tmp_value.bitc.transparent_color;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_ENABLE_CTRL (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_ENABLE_CTRL(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ENABLE_CTRL] <-- 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_ENABLE_CTRL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ENABLE_CTRL] --> 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_ENABLE_CTRL_enable(U8 data)
{
    GH_VO_MIXER1_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ENABLE_CTRL_enable] <-- 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_ENABLE_CTRL_enable(void)
{
    GH_VO_MIXER1_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ENABLE_CTRL_enable] --> 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.enable;
}
void GH_VO_MIXER1_set_ENABLE_CTRL_mapped_direct(U8 data)
{
    GH_VO_MIXER1_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL;
    d.bitc.mapped_direct = data;
    *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ENABLE_CTRL_mapped_direct] <-- 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_ENABLE_CTRL_mapped_direct(void)
{
    GH_VO_MIXER1_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ENABLE_CTRL_mapped_direct] --> 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.mapped_direct;
}
void GH_VO_MIXER1_set_ENABLE_CTRL_smem(U8 data)
{
    GH_VO_MIXER1_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL;
    d.bitc.smem = data;
    *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ENABLE_CTRL_smem] <-- 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_ENABLE_CTRL_smem(void)
{
    GH_VO_MIXER1_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ENABLE_CTRL_smem] --> 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.smem;
}
void GH_VO_MIXER1_set_ENABLE_CTRL_display(U8 data)
{
    GH_VO_MIXER1_ENABLE_CTRL_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL;
    d.bitc.display = data;
    *(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_ENABLE_CTRL_display] <-- 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_ENABLE_CTRL_display(void)
{
    GH_VO_MIXER1_ENABLE_CTRL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_ENABLE_CTRL);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_ENABLE_CTRL_display] --> 0x%08x\n",
                        REG_VO_MIXER1_ENABLE_CTRL,value);
    #endif
    return tmp_value.bitc.display;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_INPUT_VIDEO_SYNC (read/write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_INPUT_VIDEO_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_INPUT_VIDEO_SYNC] <-- 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_INPUT_VIDEO_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_INPUT_VIDEO_SYNC] --> 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_sync_mode] <-- 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_sync_mode(void)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_sync_mode] --> 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.sync_mode;
}
void GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_line(U8 data)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC;
    d.bitc.line = data;
    *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_line] <-- 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_line(void)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_line] --> 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.line;
}
void GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_video(U8 data)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC;
    d.bitc.video = data;
    *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_video] <-- 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_video(void)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_video] --> 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.video;
}
void GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_decrement(U8 data)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC;
    d.bitc.decrement = data;
    *(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_INPUT_VIDEO_SYNC_decrement] <-- 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_decrement(void)
{
    GH_VO_MIXER1_INPUT_VIDEO_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_INPUT_VIDEO_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_INPUT_VIDEO_SYNC_decrement] --> 0x%08x\n",
                        REG_VO_MIXER1_INPUT_VIDEO_SYNC,value);
    #endif
    return tmp_value.bitc.decrement;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_OUTPUT_SYNC (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_OUTPUT_SYNC(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_OUTPUT_SYNC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_OUTPUT_SYNC_sync_mode(U8 data)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC;
    d.bitc.sync_mode = data;
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC_sync_mode] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OUTPUT_SYNC_sync_mode(void)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC_sync_mode] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.sync_mode;
}
void GH_VO_MIXER1_set_OUTPUT_SYNC_number(U8 data)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC;
    d.bitc.number = data;
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OUTPUT_SYNC_number(void)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC_number] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.number;
}
void GH_VO_MIXER1_set_OUTPUT_SYNC_counter(U8 data)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC;
    d.bitc.counter = data;
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC_counter] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OUTPUT_SYNC_counter(void)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC_counter] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.counter;
}
void GH_VO_MIXER1_set_OUTPUT_SYNC_sync(U8 data)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC;
    d.bitc.sync = data;
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC_sync] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OUTPUT_SYNC_sync(void)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC_sync] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.sync;
}
void GH_VO_MIXER1_set_OUTPUT_SYNC_frame(U8 data)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC;
    d.bitc.frame = data;
    *(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_OUTPUT_SYNC_frame] <-- 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_OUTPUT_SYNC_frame(void)
{
    GH_VO_MIXER1_OUTPUT_SYNC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_OUTPUT_SYNC);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_OUTPUT_SYNC_frame] --> 0x%08x\n",
                        REG_VO_MIXER1_OUTPUT_SYNC,value);
    #endif
    return tmp_value.bitc.frame;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_SMEM_INPUT (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_SMEM_INPUT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_SMEM_INPUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_SMEM_INPUT_luma_number(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_luma_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_luma_number(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_luma_number] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.luma_number;
}
void GH_VO_MIXER1_set_SMEM_INPUT_chroma_number(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_chroma_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_chroma_number(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_chroma_number] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.chroma_number;
}
void GH_VO_MIXER1_set_SMEM_INPUT_osd_number(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.osd_number = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_osd_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_osd_number(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_osd_number] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.osd_number;
}
void GH_VO_MIXER1_set_SMEM_INPUT_priority(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_priority] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_priority(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_priority] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.priority;
}
void GH_VO_MIXER1_set_SMEM_INPUT_video_length(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.video_length = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_video_length] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_video_length(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_video_length] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.video_length;
}
void GH_VO_MIXER1_set_SMEM_INPUT_osd_length(U8 data)
{
    GH_VO_MIXER1_SMEM_INPUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT;
    d.bitc.osd_length = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_INPUT_osd_length] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_INPUT_osd_length(void)
{
    GH_VO_MIXER1_SMEM_INPUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_INPUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_INPUT_osd_length] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_INPUT,value);
    #endif
    return tmp_value.bitc.osd_length;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_SMEM_OUT (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_SMEM_OUT(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_OUT] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_SMEM_OUT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_OUT);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_OUT] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_SMEM_OUT_luma_number(U8 data)
{
    GH_VO_MIXER1_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT;
    d.bitc.luma_number = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_OUT_luma_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_OUT_luma_number(void)
{
    GH_VO_MIXER1_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_OUT_luma_number] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.luma_number;
}
void GH_VO_MIXER1_set_SMEM_OUT_chroma_number(U8 data)
{
    GH_VO_MIXER1_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT;
    d.bitc.chroma_number = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_OUT_chroma_number] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_OUT_chroma_number(void)
{
    GH_VO_MIXER1_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_OUT_chroma_number] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.chroma_number;
}
void GH_VO_MIXER1_set_SMEM_OUT_priority(U8 data)
{
    GH_VO_MIXER1_SMEM_OUT_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT;
    d.bitc.priority = data;
    *(volatile U32 *)REG_VO_MIXER1_SMEM_OUT = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_SMEM_OUT_priority] <-- 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_SMEM_OUT_priority(void)
{
    GH_VO_MIXER1_SMEM_OUT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_SMEM_OUT);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_SMEM_OUT_priority] --> 0x%08x\n",
                        REG_VO_MIXER1_SMEM_OUT,value);
    #endif
    return tmp_value.bitc.priority;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_FRAME_ENABLE (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_FRAME_ENABLE(U32 data)
{
    *(volatile U32 *)REG_VO_MIXER1_FRAME_ENABLE = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_FRAME_ENABLE] <-- 0x%08x\n",
                        REG_VO_MIXER1_FRAME_ENABLE,data,data);
    #endif
}
U32  GH_VO_MIXER1_get_FRAME_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_FRAME_ENABLE);

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_FRAME_ENABLE] --> 0x%08x\n",
                        REG_VO_MIXER1_FRAME_ENABLE,value);
    #endif
    return value;
}
void GH_VO_MIXER1_set_FRAME_ENABLE_enable(U8 data)
{
    GH_VO_MIXER1_FRAME_ENABLE_S d;
    d.all = *(volatile U32 *)REG_VO_MIXER1_FRAME_ENABLE;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_MIXER1_FRAME_ENABLE = d.all;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_FRAME_ENABLE_enable] <-- 0x%08x\n",
                        REG_VO_MIXER1_FRAME_ENABLE,d.all,d.all);
    #endif
}
U8   GH_VO_MIXER1_get_FRAME_ENABLE_enable(void)
{
    GH_VO_MIXER1_FRAME_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_MIXER1_FRAME_ENABLE);

    tmp_value.all = value;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_FRAME_ENABLE_enable] --> 0x%08x\n",
                        REG_VO_MIXER1_FRAME_ENABLE,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_MIXER1_CLUT_B (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_MIXER1_set_CLUT_B(U16 index, U32 data)
{
    *(volatile U32 *)(REG_VO_MIXER1_CLUT_B + index * FIO_MOFFSET(VO_MIXER1,0x00000004)) = data;
    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_MIXER1_set_CLUT_B] <-- 0x%08x\n",
                        (REG_VO_MIXER1_CLUT_B + index * FIO_MOFFSET(VO_MIXER1,0x00000004)),data,data);
    #endif
}
U32  GH_VO_MIXER1_get_CLUT_B(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_VO_MIXER1_CLUT_B + index * FIO_MOFFSET(VO_MIXER1,0x00000004)));

    #if GH_VO_MIXER1_ENABLE_DEBUG_PRINT
    GH_VO_MIXER1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_MIXER1_get_CLUT_B] --> 0x%08x\n",
                        (REG_VO_MIXER1_CLUT_B + index * FIO_MOFFSET(VO_MIXER1,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_MIXER1_init(void)
{
    int i;

    GH_VO_MIXER1_set_CONTROL((U32)0x00000000);
    GH_VO_MIXER1_set_ACTIVE_SIZE((U32)0x00000000);
    GH_VO_MIXER1_set_VIDEO_START((U32)0x00000000);
    GH_VO_MIXER1_set_VIDEO_END((U32)0x00000000);
    GH_VO_MIXER1_set_OSD_START((U32)0x00000000);
    GH_VO_MIXER1_set_OSD_END((U32)0x00000000);
    GH_VO_MIXER1_set_BACKGROUND((U32)0x00000000);
    GH_VO_MIXER1_set_HIGHLIGHT((U32)0xff000000);
    GH_VO_MIXER1_set_OSD_CONTROL((U32)0x000000ff);
    GH_VO_MIXER1_set_ENABLE_CTRL((U32)0x00000000);
    GH_VO_MIXER1_set_INPUT_VIDEO_SYNC((U32)0x00000000);
    GH_VO_MIXER1_set_OUTPUT_SYNC((U32)0x00000000);
    GH_VO_MIXER1_set_SMEM_INPUT((U32)0x00000000);
    GH_VO_MIXER1_set_SMEM_OUT((U32)0x00000000);
    GH_VO_MIXER1_set_FRAME_ENABLE((U32)0x00000000);
    GH_VO_MIXER1_set_CLUT_B(0, (U32)0x00000000);
    for (i=1; i<256; i++)
    {
        GH_VO_MIXER1_set_CLUT_B(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

