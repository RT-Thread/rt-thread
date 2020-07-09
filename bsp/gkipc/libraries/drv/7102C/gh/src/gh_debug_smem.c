/******************************************************************************
**
** \file      gh_debug_smem.c
**
** \brief     SMEM Debug Registers.
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
#include "gh_debug_smem.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_SMEM_ERROR_STATUS_S            m_debug_smem_error_status;
GH_DEBUG_SMEM_ERROR_INFO_S              m_debug_smem_error_info;

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub0_start (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub0_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_smem_channel_reg_sub0_start] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB0_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub1_start (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub1_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_smem_channel_reg_sub1_start] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB1_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub2_start (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub2_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_smem_channel_reg_sub2_start] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB2_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub3_start (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub3_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_smem_channel_reg_sub3_start] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB3_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_smem_channel_reg_sub4_start (read/write)               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start(U16 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_smem_channel_reg_sub4_start(U16 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_smem_channel_reg_sub4_start] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SMEM_CHANNEL_REG_SUB4_START + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_sync_counter (read/write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_sync_counter(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_sync_counter] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_sync_counter(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_sync_counter] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_sync_counter_max(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.max = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_sync_counter_max] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_sync_counter_max(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_sync_counter_max] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.max;
}
void GH_DEBUG_SMEM_set_sync_counter_count(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.count = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_sync_counter_count] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_sync_counter_count(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_sync_counter_count] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.count;
}
void GH_DEBUG_SMEM_set_sync_counter_max_notchange(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.max_notchange = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_sync_counter_max_notchange] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_sync_counter_max_notchange(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_sync_counter_max_notchange] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.max_notchange;
}
void GH_DEBUG_SMEM_set_sync_counter_value_notchange(U8 index, U8 data)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.value_notchange = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_sync_counter_value_notchange] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_sync_counter_value_notchange(U8 index)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_sync_counter_value_notchange] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_SYNC_COUNTER + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.value_notchange;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub0 (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_dram_channel_sub0(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_dram_channel_sub0(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_dram_channel_sub0_dpitch(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dpitch = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0_dpitch] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub0_dpitch(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0_dpitch] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dpitch;
}
void GH_DEBUG_SMEM_set_dram_channel_sub0_drowmax(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.drowmax = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0_drowmax] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub0_drowmax(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0_drowmax] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.drowmax;
}
void GH_DEBUG_SMEM_set_dram_channel_sub0_dpriority(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dpriority = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0_dpriority] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dpriority(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0_dpriority] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dpriority;
}
void GH_DEBUG_SMEM_set_dram_channel_sub0_dramDisable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dramdisable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0_dramDisable] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_dramDisable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0_dramDisable] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dramdisable;
}
void GH_DEBUG_SMEM_set_dram_channel_sub0_nextDramDisable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.nextdramdisable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub0_nextDramDisable] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub0_nextDramDisable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB0_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub0_nextDramDisable] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB0 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.nextdramdisable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub1 (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_dram_channel_sub1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub1] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_dram_channel_sub1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub1] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_dram_channel_sub1_dcol(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dcol = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub1_dcol] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub1_dcol(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub1_dcol] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dcol;
}
void GH_DEBUG_SMEM_set_dram_channel_sub1_drow(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.drow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub1_drow] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub1_drow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub1_drow] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB1 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.drow;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub2 (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_dram_channel_sub2(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_dram_channel_sub2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_dram_channel_sub2_dsrowcol(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dsrowcol = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2_dsrowcol] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dsrowcol(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2_dsrowcol] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dsrowcol;
}
void GH_DEBUG_SMEM_set_dram_channel_sub2_dscliprow(U8 index, U16 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dscliprow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2_dscliprow] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_dram_channel_sub2_dscliprow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2_dscliprow] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dscliprow;
}
void GH_DEBUG_SMEM_set_dram_channel_sub2_ddrepeatRow(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.ddrepeatrow = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2_ddrepeatRow] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_ddrepeatRow(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2_ddrepeatRow] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.ddrepeatrow;
}
void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileEnable(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dtileenable = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2_dtileEnable] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileEnable(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2_dtileEnable] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dtileenable;
}
void GH_DEBUG_SMEM_set_dram_channel_sub2_dtileField(U8 index, U8 data)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S d;
    d.all = *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004));
    d.bitc.dtilefield = data;
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub2_dtileField] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_dram_channel_sub2_dtileField(U8 index)
{
    GH_DEBUG_SMEM_DRAM_CHANNEL_SUB2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub2_dtileField] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB2 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return tmp_value.bitc.dtilefield;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub3 (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_dram_channel_sub3(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub3] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_dram_channel_sub3(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub3] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB3 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_dram_channel_sub4 (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_dram_channel_sub4(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)) = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_dram_channel_sub4] <-- 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_dram_channel_sub4(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)));

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_dram_channel_sub4] --> 0x%08x\n",
                        (REG_DEBUG_SMEM_DRAM_CHANNEL_SUB4 + index * FIO_MOFFSET(DEBUG_SMEM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM_refresh_value (read/write)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_FMEM_refresh_value(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_FMEM_REFRESH_VALUE = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_FMEM_refresh_value] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_FMEM_REFRESH_VALUE,data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_FMEM_refresh_value(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_FMEM_REFRESH_VALUE);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_FMEM_refresh_value] --> 0x%08x\n",
                        REG_DEBUG_SMEM_FMEM_REFRESH_VALUE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_2nd_lvl_clk_gating_disable (read/write)            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable] --> 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_en(U16 data)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE;
    d.bitc.en = data;
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_en] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,d.all,d.all);
    #endif
}
U16  GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_en(void)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_en] --> 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,value);
    #endif
    return tmp_value.bitc.en;
}
void GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_asserted(U8 data)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE;
    d.bitc.asserted = data;
    *(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable_asserted] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_asserted(void)
{
    GH_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_RMB_2nd_lvl_clk_gating_disable_asserted] --> 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_2ND_LVL_CLK_GATING_DISABLE,value);
    #endif
    return tmp_value.bitc.asserted;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_DRAM_RMB_behavior (read/write)                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_DRAM_RMB_behavior(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return value;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_DRAM_RMB(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.dram_rmb = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_DRAM_RMB] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_DRAM_RMB(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_DRAM_RMB] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.dram_rmb;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_real_purpose(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.no_real_purpose = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_real_purpose] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_real_purpose(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_real_purpose] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.no_real_purpose;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_load_data(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.load_data = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_load_data] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_load_data(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_load_data] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.load_data;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_write_requests(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.no_write_requests = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_no_write_requests] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_write_requests(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_no_write_requests] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.no_write_requests;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_best_left_alone(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.best_left_alone = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_best_left_alone] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_best_left_alone(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_best_left_alone] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.best_left_alone;
}
void GH_DEBUG_SMEM_set_DRAM_RMB_behavior_write_requests(U8 data)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR;
    d.bitc.write_requests = data;
    *(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR = d.all;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_DRAM_RMB_behavior_write_requests] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_SMEM_get_DRAM_RMB_behavior_write_requests(void)
{
    GH_DEBUG_SMEM_DRAM_RMB_BEHAVIOR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_DRAM_RMB_behavior_write_requests] --> 0x%08x\n",
                        REG_DEBUG_SMEM_DRAM_RMB_BEHAVIOR,value);
    #endif
    return tmp_value.bitc.write_requests;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_REQQ_request_queue_status (read)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_REQQ_request_queue_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_REQQ_REQUEST_QUEUE_STATUS);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_REQQ_request_queue_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_REQQ_REQUEST_QUEUE_STATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ONET_dma_status (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_ONET_dma_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_ONET_DMA_STATUS);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_ONET_dma_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_ONET_DMA_STATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status0 (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_RMB_dma_status0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_DMA_STATUS0);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_RMB_dma_status0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_DMA_STATUS0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_RMB_dma_status1 (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_RMB_dma_status1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_RMB_DMA_STATUS1);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_RMB_dma_status1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_RMB_DMA_STATUS1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_XFER_dram_transfer_status (read)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_XFER_dram_transfer_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_XFER_DRAM_TRANSFER_STATUS);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_XFER_dram_transfer_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_XFER_DRAM_TRANSFER_STATUS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status0 (read)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_SYNC_counter_status0(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0,value);
    #endif
    return value;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status0_TH0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0,value);
    #endif
    return tmp_value.bitc.th0;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status0_TH1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0,value);
    #endif
    return tmp_value.bitc.th1;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status0_TH2] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0,value);
    #endif
    return tmp_value.bitc.th2;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status0_TH3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status0_TH3] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS0,value);
    #endif
    return tmp_value.bitc.th3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_status1 (read)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_SYNC_counter_status1(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1,value);
    #endif
    return value;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status1_TH0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1,value);
    #endif
    return tmp_value.bitc.th0;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status1_TH1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1,value);
    #endif
    return tmp_value.bitc.th1;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status1_TH2] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1,value);
    #endif
    return tmp_value.bitc.th2;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_status1_TH3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_STATUS1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_status1_TH3] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_STATUS1,value);
    #endif
    return tmp_value.bitc.th3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_IDSP_status (read)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return value;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id0;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id1;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID2] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id2;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID3] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id3;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID4(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID4] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id4;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID5(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID5] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id5;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID6(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_IDSP_status_ID6] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_IDSP_STATUS,value);
    #endif
    return tmp_value.bitc.id6;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_SYNC_counter_VOUT_status (read)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return value;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID0(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID0] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id0;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID1(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID1] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id1;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID2(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID2] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id2;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID3(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID3] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id3;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID4(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID4] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id4;
}
U8   GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID5(void)
{
    GH_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS);

    tmp_value.all = value;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_SYNC_counter_VOUT_status_ID5] --> 0x%08x\n",
                        REG_DEBUG_SMEM_SYNC_COUNTER_VOUT_STATUS,value);
    #endif
    return tmp_value.bitc.id5;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_status (read/clear)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
U32  GH_DEBUG_SMEM_get_ERROR_status(void)
{
    m_debug_smem_error_status.all = *(volatile U32 *)REG_DEBUG_SMEM_ERROR_STATUS;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_ERROR_status] --> 0x%08x\n",
                        REG_DEBUG_SMEM_ERROR_STATUS,m_debug_smem_error_status.all );
    #endif
    return m_debug_smem_error_status.all;
}
U32  GH_DEBUG_SMEM_getm_ERROR_status(void)
{
    return m_debug_smem_error_status.all;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_left_right(void)
{
    return m_debug_smem_error_status.bitc.left_right;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_top_bottom(void)
{
    return m_debug_smem_error_status.bitc.top_bottom;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_reached(void)
{
    return m_debug_smem_error_status.bitc.reached;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_srows(void)
{
    return m_debug_smem_error_status.bitc.srows;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_vflip(void)
{
    return m_debug_smem_error_status.bitc.vflip;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_wider(void)
{
    return m_debug_smem_error_status.bitc.wider;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_transfers(void)
{
    return m_debug_smem_error_status.bitc.transfers;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_IDSP_sync(void)
{
    return m_debug_smem_error_status.bitc.idsp_sync;
}
U8   GH_DEBUG_SMEM_getm_ERROR_status_VOUT_sync(void)
{
    return m_debug_smem_error_status.bitc.vout_sync;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_info (read/clear)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
U32  GH_DEBUG_SMEM_get_ERROR_info(void)
{
    m_debug_smem_error_info.all = *(volatile U32 *)REG_DEBUG_SMEM_ERROR_INFO;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_ERROR_info] --> 0x%08x\n",
                        REG_DEBUG_SMEM_ERROR_INFO,m_debug_smem_error_info.all );
    #endif
    return m_debug_smem_error_info.all;
}
U32  GH_DEBUG_SMEM_getm_ERROR_info(void)
{
    return m_debug_smem_error_info.all;
}
U16  GH_DEBUG_SMEM_getm_ERROR_info_first_error(void)
{
    return m_debug_smem_error_info.bitc.first_error;
}
U8   GH_DEBUG_SMEM_getm_ERROR_info_id(void)
{
    return m_debug_smem_error_info.bitc.id;
}
U8   GH_DEBUG_SMEM_getm_ERROR_info_valid(void)
{
    return m_debug_smem_error_info.bitc.valid;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_ERROR_mask (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_ERROR_mask(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_ERROR_MASK = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_ERROR_mask] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_ERROR_MASK,data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_ERROR_mask(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_ERROR_MASK);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_ERROR_mask] --> 0x%08x\n",
                        REG_DEBUG_SMEM_ERROR_MASK,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_SMEM_FMEM (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_SMEM_set_FMEM(U32 data)
{
    *(volatile U32 *)REG_DEBUG_SMEM_FMEM = data;
    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_SMEM_set_FMEM] <-- 0x%08x\n",
                        REG_DEBUG_SMEM_FMEM,data,data);
    #endif
}
U32  GH_DEBUG_SMEM_get_FMEM(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_SMEM_FMEM);

    #if GH_DEBUG_SMEM_ENABLE_DEBUG_PRINT
    GH_DEBUG_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_SMEM_get_FMEM] --> 0x%08x\n",
                        REG_DEBUG_SMEM_FMEM,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DEBUG_SMEM_init(void)
{
    int i;

    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub0_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub1_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub2_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub3_start(i, (U32)0x00000000);
    }
    for (i=0; i<256; i++)
    {
        GH_DEBUG_SMEM_set_smem_channel_reg_sub4_start(i, (U32)0x00000000);
    }
    for (i=0; i<32; i++)
    {
        GH_DEBUG_SMEM_set_sync_counter(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub0(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub1(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub2(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub3(i, (U32)0x00000000);
    }
    for (i=0; i<128; i++)
    {
        GH_DEBUG_SMEM_set_dram_channel_sub4(i, (U32)0x00000000);
    }
    GH_DEBUG_SMEM_set_FMEM_refresh_value((U32)0x00000000);
    GH_DEBUG_SMEM_set_RMB_2nd_lvl_clk_gating_disable((U32)0x00000000);
    GH_DEBUG_SMEM_set_DRAM_RMB_behavior((U32)0x00000000);
    GH_DEBUG_SMEM_set_ERROR_mask((U32)0x00000000);
    GH_DEBUG_SMEM_set_FMEM((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
    GH_DEBUG_SMEM_get_ERROR_status();
    GH_DEBUG_SMEM_get_ERROR_info();
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

