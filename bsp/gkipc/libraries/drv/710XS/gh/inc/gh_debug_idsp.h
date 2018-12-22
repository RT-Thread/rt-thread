/*!
*******************************************************************************
**
** \file      gh_debug_idsp.h
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
#ifndef _GH_DEBUG_IDSP_H
#define _GH_DEBUG_IDSP_H

#ifdef __LINUX__
#include "reg4linux.h"
#else
#define FIO_ADDRESS(block,address) (address)
#define FIO_MOFFSET(block,moffset) (moffset)
#endif

#ifndef __LINUX__
#include "gtypes.h" /* global type definitions */
#include "gh_lib_cfg.h" /* configuration */
#endif

#define GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/* check configuration */
#ifndef GH_INLINE_LEVEL
  #error "GH_INLINE_LEVEL is not defined!"
#endif
#if GH_INLINE_LEVEL > 2
  #error "GH_INLINE_LEVEL must be set 0, 1 or 2!"
#endif
#ifndef GH_INLINE
  #error "GH_INLINE is not defined!"
#endif

/* disable inlining for debugging */
#ifdef DEBUG
  #undef GH_INLINE_LEVEL
  #define GH_INLINE_LEVEL 0
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_IDSP_ADDRESS                              FIO_ADDRESS(DEBUG_IDSP,0x70118000) /* read/write */
#define REG_DEBUG_IDSP_CONFIG                               FIO_ADDRESS(DEBUG_IDSP,0x70118004) /* read */
#define REG_DEBUG_IDSP_SECTION_RESET                        FIO_ADDRESS(DEBUG_IDSP,0x7011801C) /* write */
#define REG_DEBUG_IDSP_ERROR                                FIO_ADDRESS(DEBUG_IDSP,0x70118020) /* read/write */
#define REG_DEBUG_IDSP_CLOCK_GATING_DISABLE                 FIO_ADDRESS(DEBUG_IDSP,0x70118024) /* read/write */
#define REG_DEBUG_IDSP_SECTION_COMMAND_START                FIO_ADDRESS(DEBUG_IDSP,0x70118040) /* read */
#define REG_DEBUG_IDSP_SECTION_DEBUG1                       FIO_ADDRESS(DEBUG_IDSP,0x70118078) /* read */
#define REG_DEBUG_IDSP_SECTION_DEBUG2                       FIO_ADDRESS(DEBUG_IDSP,0x7011807C) /* read */
#define REG_DEBUG_IDSP_FILTER                               FIO_ADDRESS(DEBUG_IDSP,0xA011FF00) /* read/write */

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
} GH_DEBUG_IDSP_ADDRESS_S;

typedef union { /* DEBUG_IDSP_Config */
    U32 all;
    struct {
        U32 write_data                  : 1;
        U32 second_half                 : 1;
        U32 data                        : 6;
        U32 section_id                  : 3;
        U32                             : 21;
    } bitc;
} GH_DEBUG_IDSP_CONFIG_S;

typedef union { /* DEBUG_IDSP_Section_reset */
    U32 all;
    struct {
        U32 reset                       : 7;
        U32                             : 25;
    } bitc;
} GH_DEBUG_IDSP_SECTION_RESET_S;

typedef union { /* DEBUG_IDSP_error */
    U32 all;
    struct {
        U32                             : 1;
        U32 reset                       : 7;
        U32                             : 24;
    } bitc;
} GH_DEBUG_IDSP_ERROR_S;

typedef union { /* DEBUG_IDSP_clock_gating_disable */
    U32 all;
    struct {
        U32 smem                        : 1;
        U32 section                     : 7;
        U32 smem_tile                   : 1;
        U32                             : 23;
    } bitc;
} GH_DEBUG_IDSP_CLOCK_GATING_DISABLE_S;

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
} GH_DEBUG_IDSP_SECTION_DEBUG1_S;

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
} GH_DEBUG_IDSP_SECTION_DEBUG2_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_DEBUG_IDSP_SECTION_RESET_S           m_debug_idsp_section_reset;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_IDSP_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_IDSP_Address'. */
void GH_DEBUG_IDSP_set_Address(U32 data);
/*! \brief Reads the register 'DEBUG_IDSP_Address'. */
U32  GH_DEBUG_IDSP_get_Address(void);
/*! \brief Writes the bit group 'filter_address_MSB' of register 'DEBUG_IDSP_Address'. */
void GH_DEBUG_IDSP_set_Address_filter_address_MSB(U8 data);
/*! \brief Reads the bit group 'filter_address_MSB' of register 'DEBUG_IDSP_Address'. */
U8   GH_DEBUG_IDSP_get_Address_filter_address_MSB(void);
/*! \brief Writes the bit group 'filter_number' of register 'DEBUG_IDSP_Address'. */
void GH_DEBUG_IDSP_set_Address_filter_number(U8 data);
/*! \brief Reads the bit group 'filter_number' of register 'DEBUG_IDSP_Address'. */
U8   GH_DEBUG_IDSP_get_Address_filter_number(void);
/*! \brief Writes the bit group 'section_number' of register 'DEBUG_IDSP_Address'. */
void GH_DEBUG_IDSP_set_Address_section_number(U8 data);
/*! \brief Reads the bit group 'section_number' of register 'DEBUG_IDSP_Address'. */
U8   GH_DEBUG_IDSP_get_Address_section_number(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_IDSP_set_Address(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_ADDRESS = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Address] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Address(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ADDRESS);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Address] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ADDRESS,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_IDSP_set_Address_filter_address_MSB(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_filter_address_MSB(void)
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
GH_INLINE void GH_DEBUG_IDSP_set_Address_filter_number(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_filter_number(void)
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
GH_INLINE void GH_DEBUG_IDSP_set_Address_section_number(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Address_section_number(void)
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
/*! \brief Reads the register 'DEBUG_IDSP_Config'. */
U32  GH_DEBUG_IDSP_get_Config(void);
/*! \brief Reads the bit group 'write_data' of register 'DEBUG_IDSP_Config'. */
U8   GH_DEBUG_IDSP_get_Config_write_data(void);
/*! \brief Reads the bit group 'second_half' of register 'DEBUG_IDSP_Config'. */
U8   GH_DEBUG_IDSP_get_Config_second_half(void);
/*! \brief Reads the bit group 'data' of register 'DEBUG_IDSP_Config'. */
U8   GH_DEBUG_IDSP_get_Config_data(void);
/*! \brief Reads the bit group 'section_ID' of register 'DEBUG_IDSP_Config'. */
U8   GH_DEBUG_IDSP_get_Config_section_ID(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_IDSP_get_Config(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CONFIG);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Config] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CONFIG,value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_write_data(void)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_second_half(void)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_data(void)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Config_section_ID(void)
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
/*! \brief Writes the register 'DEBUG_IDSP_Section_reset'. */
void GH_DEBUG_IDSP_set_Section_reset(U32 data);
/*! \brief Reads the mirror variable of the register 'DEBUG_IDSP_Section_reset'. */
U32  GH_DEBUG_IDSP_getm_Section_reset(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_IDSP_Section_reset'. */
void GH_DEBUG_IDSP_set_Section_reset_reset(U8 data);
/*! \brief Reads the bit group 'reset' from the mirror variable of register 'DEBUG_IDSP_Section_reset'. */
U8   GH_DEBUG_IDSP_getm_Section_reset_reset(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_DEBUG_IDSP_set_Section_reset(U32 data)
{
    m_debug_idsp_section_reset.all = data;
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Section_reset] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_SECTION_RESET,data,data);
    #endif
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
    *(volatile U32 *)REG_DEBUG_IDSP_SECTION_RESET = m_debug_idsp_section_reset.all;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Section_reset_reset] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_SECTION_RESET,m_debug_idsp_section_reset.all,m_debug_idsp_section_reset.all);
    #endif
}
GH_INLINE U8   GH_DEBUG_IDSP_getm_Section_reset_reset(void)
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
/*! \brief Writes the register 'DEBUG_IDSP_error'. */
void GH_DEBUG_IDSP_set_error(U32 data);
/*! \brief Reads the register 'DEBUG_IDSP_error'. */
U32  GH_DEBUG_IDSP_get_error(void);
/*! \brief Writes the bit group 'reset' of register 'DEBUG_IDSP_error'. */
void GH_DEBUG_IDSP_set_error_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'DEBUG_IDSP_error'. */
U8   GH_DEBUG_IDSP_get_error_reset(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_IDSP_set_error(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_ERROR = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_error] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_IDSP_get_error(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_ERROR);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_error] --> 0x%08x\n",
                        REG_DEBUG_IDSP_ERROR,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_IDSP_set_error_reset(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_error_reset(void)
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
/*! \brief Writes the register 'DEBUG_IDSP_clock_gating_disable'. */
void GH_DEBUG_IDSP_set_clock_gating_disable(U32 data);
/*! \brief Reads the register 'DEBUG_IDSP_clock_gating_disable'. */
U32  GH_DEBUG_IDSP_get_clock_gating_disable(void);
/*! \brief Writes the bit group 'smem' of register 'DEBUG_IDSP_clock_gating_disable'. */
void GH_DEBUG_IDSP_set_clock_gating_disable_smem(U8 data);
/*! \brief Reads the bit group 'smem' of register 'DEBUG_IDSP_clock_gating_disable'. */
U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem(void);
/*! \brief Writes the bit group 'section' of register 'DEBUG_IDSP_clock_gating_disable'. */
void GH_DEBUG_IDSP_set_clock_gating_disable_section(U8 data);
/*! \brief Reads the bit group 'section' of register 'DEBUG_IDSP_clock_gating_disable'. */
U8   GH_DEBUG_IDSP_get_clock_gating_disable_section(void);
/*! \brief Writes the bit group 'smem_tile' of register 'DEBUG_IDSP_clock_gating_disable'. */
void GH_DEBUG_IDSP_set_clock_gating_disable_smem_tile(U8 data);
/*! \brief Reads the bit group 'smem_tile' of register 'DEBUG_IDSP_clock_gating_disable'. */
U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem_tile(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_clock_gating_disable] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_IDSP_get_clock_gating_disable(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_IDSP_CLOCK_GATING_DISABLE);

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_clock_gating_disable] --> 0x%08x\n",
                        REG_DEBUG_IDSP_CLOCK_GATING_DISABLE,value);
    #endif
    return value;
}
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_smem(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem(void)
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
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_section(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_section(void)
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
GH_INLINE void GH_DEBUG_IDSP_set_clock_gating_disable_smem_tile(U8 data)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_clock_gating_disable_smem_tile(void)
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
/*! \brief Reads the register 'DEBUG_IDSP_Section_command_start'. */
U32  GH_DEBUG_IDSP_get_Section_command_start(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_command_start(U8 index)
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
/*! \brief Reads the register 'DEBUG_IDSP_Section_debug1'. */
U32  GH_DEBUG_IDSP_get_Section_debug1(U8 index);
/*! \brief Reads the bit group 'config_FSM_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_state(U8 index);
/*! \brief Reads the bit group 'config_FSM_done' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_done(U8 index);
/*! \brief Reads the bit group 'pending_secondary_stores' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_secondary_stores(U8 index);
/*! \brief Reads the bit group 'pending_primary_stores' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_primary_stores(U8 index);
/*! \brief Reads the bit group 'line_sync_needed' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_needed(U8 index);
/*! \brief Reads the bit group 'line_sync_pending' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_pending(U8 index);
/*! \brief Reads the bit group 'store_FSM_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_state(U8 index);
/*! \brief Reads the bit group 'store_FSM_top_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_top_state(U8 index);
/*! \brief Reads the bit group 'pending_loads' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_pending_loads(U8 index);
/*! \brief Reads the bit group 'load_FSM_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_state(U8 index);
/*! \brief Reads the bit group 'load_FSM_top_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_top_state(U8 index);
/*! \brief Reads the bit group 'main_FSM_state' of register 'DEBUG_IDSP_Section_debug1'. */
U8   GH_DEBUG_IDSP_get_Section_debug1_main_FSM_state(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_debug1(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug1] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG1 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_state(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_config_FSM_done(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_secondary_stores(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_primary_stores(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_needed(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_line_sync_pending(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_state(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_store_FSM_top_state(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_pending_loads(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_state(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_load_FSM_top_state(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug1_main_FSM_state(U8 index)
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
/*! \brief Reads the register 'DEBUG_IDSP_Section_debug2'. */
U32  GH_DEBUG_IDSP_get_Section_debug2(U8 index);
/*! \brief Reads the bit group 'store_count0' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count0(U8 index);
/*! \brief Reads the bit group 'store_count1' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count1(U8 index);
/*! \brief Reads the bit group 'store_count2' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_store_count2(U8 index);
/*! \brief Reads the bit group 'last_half' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_last_half(U8 index);
/*! \brief Reads the bit group 'last_word' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_last_word(U8 index);
/*! \brief Reads the bit group 'more' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_more(U8 index);
/*! \brief Reads the bit group 'filter' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_filter(U8 index);
/*! \brief Reads the bit group 'section' of register 'DEBUG_IDSP_Section_debug2'. */
U8   GH_DEBUG_IDSP_get_Section_debug2_section(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_IDSP_get_Section_debug2(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)));

    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_IDSP_get_Section_debug2] --> 0x%08x\n",
                        (REG_DEBUG_IDSP_SECTION_DEBUG2 + index * FIO_MOFFSET(DEBUG_IDSP,0x00000040)),value);
    #endif
    return value;
}
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count0(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count1(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_store_count2(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_last_half(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_last_word(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_more(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_filter(U8 index)
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
GH_INLINE U8   GH_DEBUG_IDSP_get_Section_debug2_section(U8 index)
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
/*! \brief Writes the register 'DEBUG_IDSP_Filter'. */
void GH_DEBUG_IDSP_set_Filter(U32 data);
/*! \brief Reads the register 'DEBUG_IDSP_Filter'. */
U32  GH_DEBUG_IDSP_get_Filter(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_IDSP_set_Filter(U32 data)
{
    *(volatile U32 *)REG_DEBUG_IDSP_FILTER = data;
    #if GH_DEBUG_IDSP_ENABLE_DEBUG_PRINT
    GH_DEBUG_IDSP_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_IDSP_set_Filter] <-- 0x%08x\n",
                        REG_DEBUG_IDSP_FILTER,data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_IDSP_get_Filter(void)
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
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_IDSP_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_IDSP_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

