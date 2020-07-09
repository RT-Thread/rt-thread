/******************************************************************************
**
** \file      gh_debug_idsp.c
**
** \brief     IDSP Debug Registers.
**
**            Copyright:   2012 - 2016 (C) GoKe Microelectronics
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef SRC_INLINE
#include "gh_debug_idsp.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_IDSP_ADDRESS_REAL                         FIO_ADDRESS(DEBUG_IDSP,0x70118000) /* read/write */
#define REG_DEBUG_IDSP_CONFIG_REAL                          FIO_ADDRESS(DEBUG_IDSP,0x70118004) /* read */
#define REG_DEBUG_IDSP_SECTION_RESET_REAL                   FIO_ADDRESS(DEBUG_IDSP,0x7011801C) /* write */
#define REG_DEBUG_IDSP_ERROR_REAL                           FIO_ADDRESS(DEBUG_IDSP,0x70118020) /* read/write */
#define REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL            FIO_ADDRESS(DEBUG_IDSP,0x70118024) /* read/write */
#define REG_DEBUG_IDSP_SECTION_COMMAND_START_REAL           FIO_ADDRESS(DEBUG_IDSP,0x70118040) /* read */
#define REG_DEBUG_IDSP_SECTION_DEBUG1_REAL                  FIO_ADDRESS(DEBUG_IDSP,0x70118078) /* read */
#define REG_DEBUG_IDSP_SECTION_DEBUG2_REAL                  FIO_ADDRESS(DEBUG_IDSP,0x7011807C) /* read */
#define REG_DEBUG_IDSP_FILTER_REAL                          FIO_ADDRESS(DEBUG_IDSP,0x70110000) /* read/write */
#define REG_DEBUG_IDSP_SUSPEND_REG1_REAL                    FIO_ADDRESS(DEBUG_IDSP,0x70101c00) /* read/write */
#define REG_DEBUG_IDSP_SUSPEND_REG2_REAL                    FIO_ADDRESS(DEBUG_IDSP,0x70101c40) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_IDSP_Address */
    U32 all;
    struct {
        U32 filter_address_msb          : 3;
        U32                             : 1;
        U32 filter_number               : 4;
        U32 section_number              : 3;
        U32                             : 21;
    } bitc;
} GH_DEBUG_IDSP_ADDRESS_REAL_S;

typedef union { /* DEBUG_IDSP_Config */
    U32 all;
    struct {
        U32 write_data                  : 1;
        U32 second_half                 : 1;
        U32 data                        : 6;
        U32 section_id                  : 3;
        U32                             : 21;
    } bitc;
} GH_DEBUG_IDSP_CONFIG_REAL_S;

typedef union { /* DEBUG_IDSP_Section_reset */
    U32 all;
    struct {
        U32 reset                       : 7;
        U32                             : 25;
    } bitc;
} GH_DEBUG_IDSP_SECTION_RESET_REAL_S;

typedef union { /* DEBUG_IDSP_error */
    U32 all;
    struct {
        U32                             : 1;
        U32 reset                       : 7;
        U32                             : 24;
    } bitc;
} GH_DEBUG_IDSP_ERROR_REAL_S;

typedef union { /* DEBUG_IDSP_clock_gating_disable */
    U32 all;
    struct {
        U32 smem                        : 1;
        U32 section                     : 7;
        U32 smem_tile                   : 1;
        U32                             : 23;
    } bitc;
} GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S;

typedef union { /* DEBUG_IDSP_Section_debug1 */
    U32 all;
    struct {
        U32 config_fsm_state            : 4;
        U32 config_fsm_done             : 1;
        U32 pending_secondary_stores    : 3;
        U32 pending_primary_stores      : 3;
        U32 line_sync_needed            : 1;
        U32 line_sync_pending           : 1;
        U32 store_fsm_state             : 3;
        U32 store_fsm_top_state         : 3;
        U32 pending_loads               : 2;
        U32 load_fsm_state              : 4;
        U32 load_fsm_top_state          : 3;
        U32 main_fsm_state              : 4;
    } bitc;
} GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S;

typedef union { /* DEBUG_IDSP_Section_debug2 */
    U32 all;
    struct {
        U32 store_count0                : 8;
        U32 store_count1                : 8;
        U32 store_count2                : 8;
        U32 last_half                   : 1;
        U32 last_word                   : 1;
        U32 more                        : 1;
        U32 filter                      : 4;
        U32 section                     : 1;
    } bitc;
} GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_DEBUG_IDSP_SECTION_RESET_S           m_debug_idsp_section_reset;

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_Address(U32 data)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S real;
    GH_DEBUG_IDSP_ADDRESS_S dummy;
    dummy.all = data ;
    real.bitc.filter_address_msb = dummy.bitc.filter_address_msb;
    real.bitc.filter_number = dummy.bitc.filter_number;
    real.bitc.section_number = dummy.bitc.section_number;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Address(void)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S real;
    GH_DEBUG_IDSP_ADDRESS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL);

    dummy.bitc.filter_address_msb = real.bitc.filter_address_msb;
    dummy.bitc.filter_number = real.bitc.filter_number;
    dummy.bitc.section_number = real.bitc.section_number;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_IDSP_set_Address_filter_address_MSB(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL;
    d.bitc.filter_address_msb = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_filter_address_MSB(void)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.filter_address_msb;
}
GH_INLINE void GH_DEBUG_IDSP_set_Address_filter_number(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL;
    d.bitc.filter_number = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_filter_number(void)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.filter_number;
}
GH_INLINE void GH_DEBUG_IDSP_set_Address_section_number(U8 data)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL;
    d.bitc.section_number = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_section_number(void)
{
    GH_DEBUG_IDSP_ADDRESS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.section_number;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Config (read)                                          */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_IDSP_get_Config(void)
{
    GH_DEBUG_IDSP_CONFIG_REAL_S real;
    GH_DEBUG_IDSP_CONFIG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG_REAL);

    dummy.bitc.write_data = real.bitc.write_data;
    dummy.bitc.second_half = real.bitc.second_half;
    dummy.bitc.data = real.bitc.data;
    dummy.bitc.section_id = real.bitc.section_id;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_write_data(void)
{
    GH_DEBUG_IDSP_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.write_data;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_second_half(void)
{
    GH_DEBUG_IDSP_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.second_half;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_data(void)
{
    GH_DEBUG_IDSP_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_section_ID(void)
{
    GH_DEBUG_IDSP_CONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.section_id;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_reset (write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_Section_reset(U32 data)
{
    m_debug_idsp_section_reset.all = data;
    GH_DEBUG_IDSP_SECTION_RESET_REAL_S real;
    GH_DEBUG_IDSP_SECTION_RESET_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_IDSP_getm_Section_reset(void)
{
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_IDSP_getm_Section_reset] --> 0x%08x\n",
                        m_debug_idsp_section_reset.all);
    #endif
    return m_debug_idsp_section_reset.all;
}
GH_INLINE void GH_DEBUG_IDSP_set_Section_reset_reset(U8 data)
{
    m_debug_idsp_section_reset.bitc.reset = data;
    GH_DEBUG_IDSP_SECTION_RESET_REAL_S real;
    real.bitc.reset = m_debug_idsp_section_reset.bitc.reset;
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET_REAL = real.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_getm_Section_reset_reset(void)
{
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "[GH_DEBUG_IDSP_getm_Section_reset_reset] --> 0x%08x\n",
                        m_debug_idsp_section_reset.bitc.reset);
    #endif
    return m_debug_idsp_section_reset.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_error (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_error(U32 data)
{
    GH_DEBUG_IDSP_ERROR_REAL_S real;
    GH_DEBUG_IDSP_ERROR_S dummy;
    dummy.all = data ;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_DEBUG_IDSP_ERROR_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_error(void)
{
    GH_DEBUG_IDSP_ERROR_REAL_S real;
    GH_DEBUG_IDSP_ERROR_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_IDSP_ERROR_REAL);

    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_IDSP_set_error_reset(U8 data)
{
    GH_DEBUG_IDSP_ERROR_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_ERROR_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_DEBUG_IDSP_ERROR_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_error_reset(void)
{
    GH_DEBUG_IDSP_ERROR_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ERROR_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_clock_gating_disable (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable(U32 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S real;
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S dummy;
    dummy.all = data ;
    real.bitc.smem = dummy.bitc.smem;
    real.bitc.section = dummy.bitc.section;
    real.bitc.smem_tile = dummy.bitc.smem_tile;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL = real.all;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_clock_gating_disable(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S real;
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL);

    dummy.bitc.smem = real.bitc.smem;
    dummy.bitc.section = real.bitc.section;
    dummy.bitc.smem_tile = real.bitc.smem_tile;
    return dummy.all;
}
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_smem(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL;
    d.bitc.smem = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.smem;
}
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_section(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL;
    d.bitc.section = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_section(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.section;
}
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_smem_tile(U8 data)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S d;
    d.all = *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL;
    d.bitc.smem_tile = data;
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL = d.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem_tile(void)
{
    GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.smem_tile;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_command_start (read)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_command_start(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_COMMAND_START_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_debug1 (read)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_debug1(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S real;
    GH_DEBUG_IDSP_SECTION_DEBUG1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    dummy.bitc.config_fsm_state = real.bitc.config_fsm_state;
    dummy.bitc.config_fsm_done = real.bitc.config_fsm_done;
    dummy.bitc.pending_secondary_stores = real.bitc.pending_secondary_stores;
    dummy.bitc.pending_primary_stores = real.bitc.pending_primary_stores;
    dummy.bitc.line_sync_needed = real.bitc.line_sync_needed;
    dummy.bitc.line_sync_pending = real.bitc.line_sync_pending;
    dummy.bitc.store_fsm_state = real.bitc.store_fsm_state;
    dummy.bitc.store_fsm_top_state = real.bitc.store_fsm_top_state;
    dummy.bitc.pending_loads = real.bitc.pending_loads;
    dummy.bitc.load_fsm_state = real.bitc.load_fsm_state;
    dummy.bitc.load_fsm_top_state = real.bitc.load_fsm_top_state;
    dummy.bitc.main_fsm_state = real.bitc.main_fsm_state;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.config_fsm_state;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_done(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.config_fsm_done;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_secondary_stores(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.pending_secondary_stores;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_primary_stores(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.pending_primary_stores;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_needed(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.line_sync_needed;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_pending(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.line_sync_pending;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.store_fsm_state;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_top_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.store_fsm_top_state;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_loads(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.pending_loads;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.load_fsm_state;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_top_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.load_fsm_top_state;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_main_FSM_state(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.main_fsm_state;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Section_debug2 (read)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_debug2(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S real;
    GH_DEBUG_IDSP_SECTION_DEBUG2_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    dummy.bitc.store_count0 = real.bitc.store_count0;
    dummy.bitc.store_count1 = real.bitc.store_count1;
    dummy.bitc.store_count2 = real.bitc.store_count2;
    dummy.bitc.last_half = real.bitc.last_half;
    dummy.bitc.last_word = real.bitc.last_word;
    dummy.bitc.more = real.bitc.more;
    dummy.bitc.filter = real.bitc.filter;
    dummy.bitc.section = real.bitc.section;
    return dummy.all;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count0(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.store_count0;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count1(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.store_count1;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count2(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.store_count2;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_last_half(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.last_half;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_last_word(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.last_word;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_more(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.more;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_filter(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.filter;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_section(U8 index)
{
    GH_DEBUG_IDSP_SECTION_DEBUG2_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    tmp_value.all = value;
    return tmp_value.bitc.section;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Filter (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_Filter(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_FILTER_REAL = data;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Filter(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_FILTER_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Suspend_reg1 (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_Suspend_reg1(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_IDSP_SUSPEND_REG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Suspend_reg1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SUSPEND_REG1_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Suspend_reg2 (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_set_Suspend_reg2(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_IDSP_SUSPEND_REG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Suspend_reg2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SUSPEND_REG2_REAL + index * FIO_MOFFSET(DEBUG_IDSP,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_IDSP_init(void)
{
    int i;

    GH_DEBUG_IDSP_set_Address((U32)0x00000000);
    GH_DEBUG_IDSP_set_Section_reset((U32)0x00000000);
    GH_DEBUG_IDSP_set_error((U32)0x00000000);
    GH_DEBUG_IDSP_set_clock_gating_disable((U32)0x00000000);
    GH_DEBUG_IDSP_set_Filter((U32)0x00000000);
    for (i=0; i<16; i++)
    {
        GH_DEBUG_IDSP_set_Suspend_reg1(i, (U32)0x00000000);
    }
    for (i=0; i<16; i++)
    {
        GH_DEBUG_IDSP_set_Suspend_reg2(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

