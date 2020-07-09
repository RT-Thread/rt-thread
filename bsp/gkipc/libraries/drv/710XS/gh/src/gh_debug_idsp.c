/******************************************************************************
**
** \file      gh_debug_idsp.c
**
** \brief     IDSP Debug Registers.
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
#include "gh_debug_idsp.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_IDSP_SECTION_RESET_S           m_debug_idsp_section_reset;

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_IDSP_set_Address(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Address] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,data,data);
    #endif
}
U32  GH_DEBUG_IDSP_get_Address(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Address] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,value);
    #endif
    return value;
}
void GH_DEBUG_IDSP_set_Address_filter_address_MSB(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS;
    d.bitc.filter_address_msb = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Address_filter_address_MSB] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_Address_filter_address_MSB(void)
{
    GH_DEBUG_IDSP_ADDRESS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Address_filter_address_MSB] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,value);
    #endif
    return tmp_value.bitc.filter_address_msb;
}
void GH_DEBUG_IDSP_set_Address_filter_number(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS;
    d.bitc.filter_number = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Address_filter_number] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_Address_filter_number(void)
{
    GH_DEBUG_IDSP_ADDRESS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Address_filter_number] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,value);
    #endif
    return tmp_value.bitc.filter_number;
}
void GH_DEBUG_IDSP_set_Address_section_number(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS;
    d.bitc.section_number = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Address_section_number] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_Address_section_number(void)
{
    GH_DEBUG_IDSP_ADDRESS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Address_section_number] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,value);
    #endif
    return tmp_value.bitc.section_number;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Config (read)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_IDSP_get_Config(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return value;
}
U8   GH_DEBUG_IDSP_get_Config_write_data(void)
{
    GH_DEBUG_IDSP_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config_write_data] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return tmp_value.bitc.write_data;
}
U8   GH_DEBUG_IDSP_get_Config_second_half(void)
{
    GH_DEBUG_IDSP_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config_second_half] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return tmp_value.bitc.second_half;
}
U8   GH_DEBUG_IDSP_get_Config_data(void)
{
    GH_DEBUG_IDSP_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config_data] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return tmp_value.bitc.data;
}
U8   GH_DEBUG_IDSP_get_Config_section_ID(void)
{
    GH_DEBUG_IDSP_CONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config_section_ID] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return tmp_value.bitc.section_id;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_reset (write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_DEBUG_IDSP_set_Section_reset(U32 data)
{
    m_debug_idsp_section_reset.all = data;
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Section_reset] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_SECTION_RESET,data,data);
    #endif
}
U32  GH_DEBUG_IDSP_getm_Section_reset(void)
{
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_IDSP_getm_Section_reset] --> 0x%08x\n",
                        m_debug_idsp_section_reset.all);
    #endif
    return m_debug_idsp_section_reset.all;
}
void GH_DEBUG_IDSP_set_Section_reset_reset(U8 data)
{
    m_debug_idsp_section_reset.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET = m_debug_idsp_section_reset.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Section_reset_reset] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_SECTION_RESET,m_debug_idsp_section_reset.all,m_debug_idsp_section_reset.all);
    #endif
}
U8   GH_DEBUG_IDSP_getm_Section_reset_reset(void)
{
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_IDSP_getm_Section_reset_reset] --> 0x%08x\n",
                        m_debug_idsp_section_reset.bitc.reset);
    #endif
    return m_debug_idsp_section_reset.bitc.reset;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_error (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_IDSP_set_error(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_ERROR = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_error] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,data,data);
    #endif
}
U32  GH_DEBUG_IDSP_get_error(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ERROR);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_error] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,value);
    #endif
    return value;
}
void GH_DEBUG_IDSP_set_error_reset(U8 data)
{
    GH_DEBUG_IDSP_ERROR_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ERROR;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ERROR = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_error_reset] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_error_reset(void)
{
    GH_DEBUG_IDSP_ERROR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ERROR);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_error_reset] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,value);
    #endif
    return tmp_value.bitc.reset;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_clock_gating_disable (read/write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_IDSP_set_clock_gating_disable(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_clock_gating_disable] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,data,data);
    #endif
}
U32  GH_DEBUG_IDSP_get_clock_gating_disable(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_clock_gating_disable] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,value);
    #endif
    return value;
}
void GH_DEBUG_IDSP_set_clock_gating_disable_smem(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE;
    d.bitc.smem = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_clock_gating_disable_smem] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_clock_gating_disable_smem] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,value);
    #endif
    return tmp_value.bitc.smem;
}
void GH_DEBUG_IDSP_set_clock_gating_disable_section(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE;
    d.bitc.section = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_clock_gating_disable_section] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_clock_gating_disable_section(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_clock_gating_disable_section] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,value);
    #endif
    return tmp_value.bitc.section;
}
void GH_DEBUG_IDSP_set_clock_gating_disable_smem_tile(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE;
    d.bitc.smem_tile = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE = d.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_clock_gating_disable_smem_tile] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,d.all,d.all);
    #endif
}
U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem_tile(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE);

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_clock_gating_disable_smem_tile] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,value);
    #endif
    return tmp_value.bitc.smem_tile;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_command_start (read)                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_IDSP_get_Section_command_start(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_COMMAND_START + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_command_start] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_COMMAND_START + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_debug1 (read)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_IDSP_get_Section_debug1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return value;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_config_FSM_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.config_fsm_state;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_done(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_config_FSM_done] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.config_fsm_done;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_secondary_stores(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_pending_secondary_stores] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.pending_secondary_stores;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_primary_stores(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_pending_primary_stores] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.pending_primary_stores;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_needed(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_line_sync_needed] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.line_sync_needed;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_pending(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_line_sync_pending] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.line_sync_pending;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_store_FSM_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.store_fsm_state;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_top_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_store_FSM_top_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.store_fsm_top_state;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_loads(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_pending_loads] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.pending_loads;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_load_FSM_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.load_fsm_state;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_top_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_load_FSM_top_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.load_fsm_top_state;
}
U8   GH_DEBUG_IDSP_get_Section_debug1_main_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1_main_FSM_state] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.main_fsm_state;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_debug2 (read)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_IDSP_get_Section_debug2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return value;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count0(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_store_count0] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.store_count0;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count1(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_store_count1] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.store_count1;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count2(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_store_count2] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.store_count2;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_last_half(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_last_half] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.last_half;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_last_word(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_last_word] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.last_word;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_more(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_more] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.more;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_filter(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_filter] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.filter;
}
U8   GH_DEBUG_IDSP_get_Section_debug2_section(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2_section] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return tmp_value.bitc.section;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Filter (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
void GH_DEBUG_IDSP_set_Filter(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_FILTER = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Filter] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_FILTER,data,data);
    #endif
}
U32  GH_DEBUG_IDSP_get_Filter(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_FILTER);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Filter] --> 0x%08x\n",
                        REG_DEBUG_IDSP_FILTER,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_DEBUG_IDSP_init(void)
{
    GH_DEBUG_IDSP_set_Address((U32)0x00000000);
    GH_DEBUG_IDSP_set_Section_reset((U32)0x00000000);
    GH_DEBUG_IDSP_set_error((U32)0x00000000);
    GH_DEBUG_IDSP_set_clock_gating_disable((U32)0x00000000);
    GH_DEBUG_IDSP_set_Filter((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

