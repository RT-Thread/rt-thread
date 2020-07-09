/******************************************************************************
**
** \file      gh_i2c.c
**
** \brief     I2C Interface..
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
#include "gh_i2c.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register I2C_ENABLE (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_ENABLE(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_ENABLE] <-- 0x%08x\n",
                        (REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_ENABLE(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_ENABLE] --> 0x%08x\n",
                        (REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_ENABLE_en(U8 index, U8 data)
{
    GH_I2C_ENABLE_S d;
    d.all = *(volatile U32 *)(REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.en = data;
    *(volatile U32 *)(REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_ENABLE_en] <-- 0x%08x\n",
                        (REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_ENABLE_en(U8 index)
{
    GH_I2C_ENABLE_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_ENABLE_en] --> 0x%08x\n",
                        (REG_I2C_ENABLE + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_CONTROL (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_CONTROL(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_CONTROL(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_CONTROL_stop(U8 index, U8 data)
{
    GH_I2C_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.stop = data;
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL_stop] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_CONTROL_stop(U8 index)
{
    GH_I2C_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL_stop] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.stop;
}
void GH_I2C_set_CONTROL_start(U8 index, U8 data)
{
    GH_I2C_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.start = data;
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL_start] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_CONTROL_start(U8 index)
{
    GH_I2C_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL_start] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.start;
}
void GH_I2C_set_CONTROL_ack(U8 index, U8 data)
{
    GH_I2C_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.ack = data;
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL_ack] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_CONTROL_ack(U8 index)
{
    GH_I2C_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL_ack] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.ack;
}
void GH_I2C_set_CONTROL_IntFlag(U8 index, U8 data)
{
    GH_I2C_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.intflag = data;
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL_IntFlag] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_CONTROL_IntFlag(U8 index)
{
    GH_I2C_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL_IntFlag] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.intflag;
}
void GH_I2C_set_CONTROL_ClrAutoFifo(U8 index, U8 data)
{
    GH_I2C_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.clrautofifo = data;
    *(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_CONTROL_ClrAutoFifo] <-- 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_CONTROL_ClrAutoFifo(U8 index)
{
    GH_I2C_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_CONTROL_ClrAutoFifo] --> 0x%08x\n",
                        (REG_I2C_CONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.clrautofifo;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_DATA (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_DATA(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_DATA] <-- 0x%08x\n",
                        (REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_DATA(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_DATA] --> 0x%08x\n",
                        (REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_DATA_Data(U8 index, U8 data)
{
    GH_I2C_DATA_S d;
    d.all = *(volatile U32 *)(REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.data = data;
    *(volatile U32 *)(REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_DATA_Data] <-- 0x%08x\n",
                        (REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_DATA_Data(U8 index)
{
    GH_I2C_DATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_DATA_Data] --> 0x%08x\n",
                        (REG_I2C_DATA + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_STATUS (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_I2C_get_STATUS(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_STATUS + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_STATUS] --> 0x%08x\n",
                        (REG_I2C_STATUS + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
U8   GH_I2C_get_STATUS_mode(U8 index)
{
    GH_I2C_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_STATUS + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_STATUS_mode] --> 0x%08x\n",
                        (REG_I2C_STATUS + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEL (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_PRESCALEL(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_PRESCALEL] <-- 0x%08x\n",
                        (REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_PRESCALEL(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_PRESCALEL] --> 0x%08x\n",
                        (REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_PRESCALEL_scale(U8 index, U8 data)
{
    GH_I2C_PRESCALEL_S d;
    d.all = *(volatile U32 *)(REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.scale = data;
    *(volatile U32 *)(REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_PRESCALEL_scale] <-- 0x%08x\n",
                        (REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_PRESCALEL_scale(U8 index)
{
    GH_I2C_PRESCALEL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_PRESCALEL_scale] --> 0x%08x\n",
                        (REG_I2C_PRESCALEL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.scale;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_PRESCALEH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_PRESCALEH(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_PRESCALEH] <-- 0x%08x\n",
                        (REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_PRESCALEH(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_PRESCALEH] --> 0x%08x\n",
                        (REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_PRESCALEH_scale(U8 index, U8 data)
{
    GH_I2C_PRESCALEH_S d;
    d.all = *(volatile U32 *)(REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.scale = data;
    *(volatile U32 *)(REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_PRESCALEH_scale] <-- 0x%08x\n",
                        (REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_PRESCALEH_scale(U8 index)
{
    GH_I2C_PRESCALEH_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_PRESCALEH_scale] --> 0x%08x\n",
                        (REG_I2C_PRESCALEH + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.scale;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_FMCONTROL (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_FMCONTROL(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMCONTROL] <-- 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_FMCONTROL(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMCONTROL] --> 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_FMCONTROL_stop(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.stop = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMCONTROL_stop] <-- 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_FMCONTROL_stop(U8 index)
{
    GH_I2C_FMCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMCONTROL_stop] --> 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.stop;
}
void GH_I2C_set_FMCONTROL_start(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.start = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMCONTROL_start] <-- 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_FMCONTROL_start(U8 index)
{
    GH_I2C_FMCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMCONTROL_start] --> 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.start;
}
void GH_I2C_set_FMCONTROL_is(U8 index, U8 data)
{
    GH_I2C_FMCONTROL_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.is = data;
    *(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMCONTROL_is] <-- 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_FMCONTROL_is(U8 index)
{
    GH_I2C_FMCONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMCONTROL_is] --> 0x%08x\n",
                        (REG_I2C_FMCONTROL + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.is;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register I2C_FMDATA (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_I2C_set_FMDATA(U8 index, U32 data)
{
    *(volatile U32 *)(REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)) = data;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMDATA] <-- 0x%08x\n",
                        (REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)),data,data);
    #endif
}
U32  GH_I2C_get_FMDATA(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)));

    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMDATA] --> 0x%08x\n",
                        (REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return value;
}
void GH_I2C_set_FMDATA_Data(U8 index, U8 data)
{
    GH_I2C_FMDATA_S d;
    d.all = *(volatile U32 *)(REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000));
    d.bitc.data = data;
    *(volatile U32 *)(REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)) = d.all;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_I2C_set_FMDATA_Data] <-- 0x%08x\n",
                        (REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)),d.all,d.all);
    #endif
}
U8   GH_I2C_get_FMDATA_Data(U8 index)
{
    GH_I2C_FMDATA_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)));

    tmp_value.all = value;
    #if GH_I2C_ENABLE_DEBUG_PRINT
    GH_I2C_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_I2C_get_FMDATA_Data] --> 0x%08x\n",
                        (REG_I2C_FMDATA + index * FIO_MOFFSET(I2C,0x00001000)),value);
    #endif
    return tmp_value.bitc.data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_I2C_init(void)
{
    int i;

    for (i=0; i<2; i++)
    {
        GH_I2C_set_ENABLE(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_CONTROL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_DATA(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_PRESCALEL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_PRESCALEH(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_FMCONTROL(i, (U32)0x00000000);
    }
    for (i=0; i<2; i++)
    {
        GH_I2C_set_FMDATA(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

