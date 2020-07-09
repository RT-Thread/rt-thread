/******************************************************************************
**
** \file      gh_pwm.c
**
** \brief     Pulse Width Modulator.
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
#include "gh_pwm.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register PWM_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PWM_set_Enable(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Enable] <-- 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
U32  GH_PWM_get_Enable(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Enable] --> 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
void GH_PWM_set_Enable_enb(U8 index, U8 data)
{
    GH_PWM_ENABLE_S d;
    d.all = *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.enb = data;
    *(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Enable_enb] <-- 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_PWM_get_Enable_enb(U8 index)
{
    GH_PWM_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Enable_enb] --> 0x%08x\n",
                        (REG_PWM_ENABLE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.enb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Control0 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PWM_set_Control(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
U32  GH_PWM_get_Control(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
void GH_PWM_set_Control_xon(U8 index, U16 data)
{
    GH_PWM_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xon = data;
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0_HighCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U16  GH_PWM_get_Control_xon(U8 index)
{
    GH_PWM_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0_HighCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.xon;
}
void GH_PWM_set_Control_xoff(U8 index, U16 data)
{
    GH_PWM_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xoff = data;
    *(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control0_LowCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U16  GH_PWM_get_Control_xoff(U8 index)
{
    GH_PWM_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control0_LowCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL0 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.xoff;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Control1 (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PWM_set_Control1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = data;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
U32  GH_PWM_get_Control1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
void GH_PWM_set_Control1_xon(U8 index, U16 data)
{
    GH_PWM_CONTROL1_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xon = data;
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1_HighCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U16  GH_PWM_get_Control1_xon(U8 index)
{
    GH_PWM_CONTROL1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1_HighCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.xon;
}
void GH_PWM_set_Control1_xoff(U8 index, U16 data)
{
    GH_PWM_CONTROL1_S d;
    d.all = *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.xoff = data;
    *(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Control1_LowCnt] <-- 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U16  GH_PWM_get_Control1_xoff(U8 index)
{
    GH_PWM_CONTROL1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Control1_LowCnt] --> 0x%08x\n",
                        (REG_PWM_CONTROL1 + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.xoff;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register PWM_Mode (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_PWM_set_Mode(U8 index, U32 data)
{
    GH_PWM_MODE_S d;
    d.all = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));
    d.bitc.mode = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),data,data);
    #endif
}
U32  GH_PWM_get_Mode(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return value;
}
void GH_PWM_set_Mode_divider(U8 index, U16 data)
{
    GH_PWM_MODE_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.divider = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode_divider] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U16  GH_PWM_get_Mode_divider(U8 index)
{
    GH_PWM_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode_divider] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.divider;
}
void GH_PWM_set_Mode_mode(U8 index, U8 data)
{
    GH_PWM_MODE_S d;
    d.all = *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000));
    d.bitc.mode = data;
    *(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)) = d.all;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_PWM_set_Mode_mode] <-- 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_PWM_get_Mode_mode(U8 index)
{
    GH_PWM_MODE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)));

    tmp_value.all = value;
    #if GH_PWM_ENABLE_DEBUG_PRINT
    GH_PWM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_PWM_get_Mode_mode] --> 0x%08x\n",
                        (REG_PWM_MODE + index * FIO_MOFFSET(PWM,0x00001000)),value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_PWM_init(void)
{
    int i;

    for (i=0; i<8; i++)
    {
        GH_PWM_set_Enable(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_PWM_set_Control(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_PWM_set_Control1(i, (U32)0x00000000);
    }
    for (i=0; i<8; i++)
    {
        GH_PWM_set_Mode(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

