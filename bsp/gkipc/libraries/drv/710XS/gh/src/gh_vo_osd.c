/******************************************************************************
**
** \file      gh_vo_osd.c
**
** \brief     OSD Rescale Registers.
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
#include "gh_vo_osd.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_VO_OSD_RESCALE_HORIZONTAL_COEFF_S    m_vo_osd_rescale_horizontal_coeff[32];
GH_VO_OSD_RESCALE_VERTICAL_COEFF_S      m_vo_osd_rescale_vertical_coeff[32];

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_CONTROL (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_CONTROL] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_CONTROL] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_CONTROL_Enable(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_CONTROL_Enable] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_OSD_get_RESCALE_CONTROL_Enable(void)
{
    GH_VO_OSD_RESCALE_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_CONTROL_Enable] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,value);
    #endif
    return tmp_value.bitc.enable;
}
void GH_VO_OSD_set_RESCALE_CONTROL_Vertical_shift(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL;
    d.bitc.vertical_shift = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_CONTROL_Vertical_shift] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_OSD_get_RESCALE_CONTROL_Vertical_shift(void)
{
    GH_VO_OSD_RESCALE_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_CONTROL_Vertical_shift] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,value);
    #endif
    return tmp_value.bitc.vertical_shift;
}
void GH_VO_OSD_set_RESCALE_CONTROL_Horizontal_shift(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL;
    d.bitc.horizontal_shift = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_CONTROL_Horizontal_shift] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_OSD_get_RESCALE_CONTROL_Horizontal_shift(void)
{
    GH_VO_OSD_RESCALE_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_CONTROL_Horizontal_shift] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,value);
    #endif
    return tmp_value.bitc.horizontal_shift;
}
void GH_VO_OSD_set_RESCALE_CONTROL_Input(U8 data)
{
    GH_VO_OSD_RESCALE_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL;
    d.bitc.input = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_CONTROL_Input] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,d.all,d.all);
    #endif
}
U8   GH_VO_OSD_get_RESCALE_CONTROL_Input(void)
{
    GH_VO_OSD_RESCALE_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_CONTROL);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_CONTROL_Input] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_CONTROL,value);
    #endif
    return tmp_value.bitc.input;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_WIDTH (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_WIDTH(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_WIDTH] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_WIDTH,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_WIDTH(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_WIDTH] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_WIDTH,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_WIDTH_width(U16 data)
{
    GH_VO_OSD_RESCALE_WIDTH_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_WIDTH_width] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_WIDTH,d.all,d.all);
    #endif
}
U16  GH_VO_OSD_get_RESCALE_WIDTH_width(void)
{
    GH_VO_OSD_RESCALE_WIDTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_WIDTH);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_WIDTH_width] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_WIDTH,value);
    #endif
    return tmp_value.bitc.width;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INC (read/write)                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC_inc(U16 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC;
    d.bitc.inc = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC_inc] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC,d.all,d.all);
    #endif
}
U16  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC_inc(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INC_inc] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INC,value);
    #endif
    return tmp_value.bitc.inc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN (read/write)            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN,d.all,d.all);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_EVEN_init] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_EVEN,value);
    #endif
    return tmp_value.bitc.init;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD (read/write)             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(U32 data)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD,d.all,d.all);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init(void)
{
    GH_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HORIZONTAL_PHASE_INIT_ODD_init] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HORIZONTAL_PHASE_INIT_ODD,value);
    #endif
    return tmp_value.bitc.init;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HEIGHT (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_HEIGHT(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HEIGHT] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HEIGHT,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_HEIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HEIGHT] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HEIGHT,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_HEIGHT_height(U16 data)
{
    GH_VO_OSD_RESCALE_HEIGHT_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HEIGHT_height] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_HEIGHT,d.all,d.all);
    #endif
}
U16  GH_VO_OSD_get_RESCALE_HEIGHT_height(void)
{
    GH_VO_OSD_RESCALE_HEIGHT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_HEIGHT);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_HEIGHT_height] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_HEIGHT,value);
    #endif
    return tmp_value.bitc.height;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INC (read/write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC_inc(U16 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC;
    d.bitc.inc = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC_inc] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC,d.all,d.all);
    #endif
}
U16  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC_inc(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INC_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INC_inc] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INC,value);
    #endif
    return tmp_value.bitc.inc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_PHASE_INIT (read/write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT(U32 data)
{
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT,data,data);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT(void)
{
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT);

    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT,value);
    #endif
    return value;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT_init(U32 data)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_S d;
    d.all = *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT;
    d.bitc.init = data;
    *(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT = d.all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT_init] <-- 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT,d.all,d.all);
    #endif
}
U32  GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT_init(void)
{
    GH_VO_OSD_RESCALE_VERTICAL_PHASE_INIT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT);

    tmp_value.all = value;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_OSD_get_RESCALE_VERTICAL_PHASE_INIT_init] --> 0x%08x\n",
                        REG_VO_OSD_RESCALE_VERTICAL_PHASE_INIT,value);
    #endif
    return tmp_value.bitc.init;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_HORIZONTAL_COEFF (write)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(U8 index, U32 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].all = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),data,data);
    #endif
}
U32  GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].all;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_horizontal_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_0_odd_4] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_horizontal_coeff[index].all,m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_0_odd_4(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_0_odd_4] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_0_odd_4;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_horizontal_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_1_odd_5] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_horizontal_coeff[index].all,m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_1_odd_5(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_1_odd_5] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_1_odd_5;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_2(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_horizontal_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_2] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_horizontal_coeff[index].all,m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_2(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_2] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_2;
}
void GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_3(U8 index, U8 data)
{
    m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_horizontal_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF_even_3] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_HORIZONTAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_horizontal_coeff[index].all,m_vo_osd_rescale_horizontal_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_3(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_HORIZONTAL_COEFF_even_3] --> 0x%08x\n",
                        m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3);
    #endif
    return m_vo_osd_rescale_horizontal_coeff[index].bitc.even_3;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_OSD_RESCALE_VERTICAL_COEFF (write)                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(U8 index, U32 data)
{
    m_vo_osd_rescale_vertical_coeff[index].all = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = data;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_COEFF] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),data,data);
    #endif
}
U32  GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].all;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_vertical_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_0_odd_4] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_vertical_coeff[index].all,m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_0_odd_4(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_0_odd_4] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_0_odd_4;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_vertical_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_1_odd_5] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_vertical_coeff[index].all,m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_1_odd_5(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_1_odd_5] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_1_odd_5;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_2(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_2 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_vertical_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_2] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_vertical_coeff[index].all,m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_2(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_2] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_2);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_2;
}
void GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_3(U8 index, U8 data)
{
    m_vo_osd_rescale_vertical_coeff[index].bitc.even_3 = data;
    *(volatile U32 *)(REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)) = m_vo_osd_rescale_vertical_coeff[index].all;
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_OSD_set_RESCALE_VERTICAL_COEFF_even_3] <-- 0x%08x\n",
                        (REG_VO_OSD_RESCALE_VERTICAL_COEFF + index * FIO_MOFFSET(VO_OSD,0x00000004)),m_vo_osd_rescale_vertical_coeff[index].all,m_vo_osd_rescale_vertical_coeff[index].all);
    #endif
}
U8   GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_3(U8 index)
{
    #if GH_VO_OSD_ENABLE_DEBUG_PRINT
    GH_VO_OSD_DEBUG_PRINT_FUNCTION( "[GH_VO_OSD_getm_RESCALE_VERTICAL_COEFF_even_3] --> 0x%08x\n",
                        m_vo_osd_rescale_vertical_coeff[index].bitc.even_3);
    #endif
    return m_vo_osd_rescale_vertical_coeff[index].bitc.even_3;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_OSD_init(void)
{
    int i;

    GH_VO_OSD_set_RESCALE_CONTROL((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_WIDTH((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INC((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_EVEN((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_PHASE_INIT_ODD((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HEIGHT((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INC((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_VERTICAL_PHASE_INIT((U32)0x00000000);
    GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(0, (U32)0x00000000);
    for (i=1; i<32; i++)
    {
        GH_VO_OSD_set_RESCALE_HORIZONTAL_COEFF(i, (U32)0x00000000);
    }
    GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(0, (U32)0x00000000);
    for (i=1; i<32; i++)
    {
        GH_VO_OSD_set_RESCALE_VERTICAL_COEFF(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

