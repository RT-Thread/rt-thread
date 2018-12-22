/******************************************************************************
**
** \file      gh_dma.c
**
** \brief     DMA Engine Subsystem.
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
#include "gh_dma.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DMA_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DMA_set_Control(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = data;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),data,data);
    #endif
}
U32  GH_DMA_get_Control(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return value;
}
void GH_DMA_set_Control_count(U8 index, U32 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_count] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U32  GH_DMA_get_Control_count(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_count] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.count;
}
void GH_DMA_set_Control_ts(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ts = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_ts] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_ts(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_ts] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.ts;
}
void GH_DMA_set_Control_blk(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.blk = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_blk] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_blk(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_blk] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.blk;
}
void GH_DMA_set_Control_ni(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ni = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_ni] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_ni(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_ni] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.ni;
}
void GH_DMA_set_Control_rm(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.rm = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_rm] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_rm(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_rm] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.rm;
}
void GH_DMA_set_Control_wm(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.wm = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_wm] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_wm(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_wm] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.wm;
}
void GH_DMA_set_Control_d(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.d = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_d] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_d(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_d] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.d;
}
void GH_DMA_set_Control_en(U8 index, U8 data)
{
    GH_DMA_CONTROL_S d;
    d.all = *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.en = data;
    *(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Control_en] <-- 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Control_en(U8 index)
{
    GH_DMA_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Control_en] --> 0x%08x\n",
                        (REG_DMA_CONTROL + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.en;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DMA_Source_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DMA_set_Source_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_SOURCE_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)) = data;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Source_Address] <-- 0x%08x\n",
                        (REG_DMA_SOURCE_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)),data,data);
    #endif
}
U32  GH_DMA_get_Source_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_SOURCE_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)));

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Source_Address] --> 0x%08x\n",
                        (REG_DMA_SOURCE_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DMA_Destination_Address (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DMA_set_Destination_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_DESTINATION_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)) = data;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Destination_Address] <-- 0x%08x\n",
                        (REG_DMA_DESTINATION_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)),data,data);
    #endif
}
U32  GH_DMA_get_Destination_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_DESTINATION_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)));

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Destination_Address] --> 0x%08x\n",
                        (REG_DMA_DESTINATION_ADDRESS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DMA_Status (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DMA_set_Status(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = data;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),data,data);
    #endif
}
U32  GH_DMA_get_Status(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return value;
}
void GH_DMA_set_Status_count(U8 index, U32 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_count] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U32  GH_DMA_get_Status_count(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_count] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.count;
}
void GH_DMA_set_Status_dn(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dn = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_dn] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_dn(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_dn] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.dn;
}
void GH_DMA_set_Status_ae(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.ae = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_ae] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_ae(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_ae] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.ae;
}
void GH_DMA_set_Status_rwe(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.rwe = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_rwe] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_rwe(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_rwe] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.rwe;
}
void GH_DMA_set_Status_be(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.be = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_be] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_be(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_be] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.be;
}
void GH_DMA_set_Status_me(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.me = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_me] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_me(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_me] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.me;
}
void GH_DMA_set_Status_od(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.od = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_od] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_od(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_od] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.od;
}
void GH_DMA_set_Status_dd(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dd = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_dd] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_dd(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_dd] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.dd;
}
void GH_DMA_set_Status_da(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.da = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_da] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_da(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_da] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.da;
}
void GH_DMA_set_Status_oe(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.oe = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_oe] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_oe(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_oe] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.oe;
}
void GH_DMA_set_Status_dm(U8 index, U8 data)
{
    GH_DMA_STATUS_S d;
    d.all = *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010));
    d.bitc.dm = data;
    *(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)) = d.all;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Status_dm] <-- 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),d.all,d.all);
    #endif
}
U8   GH_DMA_get_Status_dm(U8 index)
{
    GH_DMA_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)));

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Status_dm] --> 0x%08x\n",
                        (REG_DMA_STATUS + index * FIO_MOFFSET(DMA,0x00000010)),value);
    #endif
    return tmp_value.bitc.dm;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DMA_Descriptor_Address (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DMA_set_Descriptor_Address(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DMA_DESCRIPTOR_ADDRESS + index * FIO_MOFFSET(DMA,0x00000004)) = data;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DMA_set_Descriptor_Address] <-- 0x%08x\n",
                        (REG_DMA_DESCRIPTOR_ADDRESS + index * FIO_MOFFSET(DMA,0x00000004)),data,data);
    #endif
}
U32  GH_DMA_get_Descriptor_Address(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DMA_DESCRIPTOR_ADDRESS + index * FIO_MOFFSET(DMA,0x00000004)));

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_Descriptor_Address] --> 0x%08x\n",
                        (REG_DMA_DESCRIPTOR_ADDRESS + index * FIO_MOFFSET(DMA,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DMA_IR (read)                                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DMA_get_IR(void)
{
    U32 value = (*(volatile U32 *)REG_DMA_IR);

    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_IR] --> 0x%08x\n",
                        REG_DMA_IR,value);
    #endif
    return value;
}
U8   GH_DMA_get_IR_i0(void)
{
    GH_DMA_IR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR);

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_IR_i0] --> 0x%08x\n",
                        REG_DMA_IR,value);
    #endif
    return tmp_value.bitc.i0;
}
U8   GH_DMA_get_IR_i1(void)
{
    GH_DMA_IR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR);

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_IR_i1] --> 0x%08x\n",
                        REG_DMA_IR,value);
    #endif
    return tmp_value.bitc.i1;
}
U8   GH_DMA_get_IR_i2(void)
{
    GH_DMA_IR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR);

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_IR_i2] --> 0x%08x\n",
                        REG_DMA_IR,value);
    #endif
    return tmp_value.bitc.i2;
}
U8   GH_DMA_get_IR_i3(void)
{
    GH_DMA_IR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DMA_IR);

    tmp_value.all = value;
    #if GH_DMA_ENABLE_DEBUG_PRINT
    GH_DMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DMA_get_IR_i3] --> 0x%08x\n",
                        REG_DMA_IR,value);
    #endif
    return tmp_value.bitc.i3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DMA_init(void)
{
    int i;

    for (i=0; i<4; i++)
    {
        GH_DMA_set_Control(i, (U32)0x38000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Source_Address(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Destination_Address(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Status(i, (U32)0x00000000);
    }
    for (i=0; i<4; i++)
    {
        GH_DMA_set_Descriptor_Address(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

