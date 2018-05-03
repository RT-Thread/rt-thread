/*!
*******************************************************************************
**
** \file      gh_debug_tsfm.h
**
** \brief     TSFM Debug Registers.
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
#ifndef _GH_DEBUG_TSFM_H
#define _GH_DEBUG_TSFM_H

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

#define GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
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
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID           FIO_ADDRESS(DEBUG_TSFM,0x70128000) /* read */
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP             FIO_ADDRESS(DEBUG_TSFM,0x70128004) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE            FIO_ADDRESS(DEBUG_TSFM,0x70128008) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE           FIO_ADDRESS(DEBUG_TSFM,0x7012800C) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP           FIO_ADDRESS(DEBUG_TSFM,0x70128010) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP             FIO_ADDRESS(DEBUG_TSFM,0x70128014) /* read */
#define REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE        FIO_ADDRESS(DEBUG_TSFM,0x70128018) /* read */
#define REG_DEBUG_TSFM_COUNT_NEW_MACRO                      FIO_ADDRESS(DEBUG_TSFM,0x7012801C) /* read */
#define REG_DEBUG_TSFM_COUNT_JP_DONE                        FIO_ADDRESS(DEBUG_TSFM,0x70128020) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_4X4                      FIO_ADDRESS(DEBUG_TSFM,0x70128024) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_16                       FIO_ADDRESS(DEBUG_TSFM,0x70128028) /* read */
#define REG_DEBUG_TSFM_COUNT_INTER                          FIO_ADDRESS(DEBUG_TSFM,0x7012802C) /* read */
#define REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID             FIO_ADDRESS(DEBUG_TSFM,0x70128030) /* read */
#define REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS        FIO_ADDRESS(DEBUG_TSFM,0x70128034) /* read */
#define REG_DEBUG_TSFM_LBIST0_DATA                          FIO_ADDRESS(DEBUG_TSFM,0x70128080) /* read */
#define REG_DEBUG_TSFM_LBIST1_DATA                          FIO_ADDRESS(DEBUG_TSFM,0x70128084) /* read */
#define REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF                   FIO_ADDRESS(DEBUG_TSFM,0x70129000) /* read */
#define REG_DEBUG_TSFM_DEBUG_TCTRM                          FIO_ADDRESS(DEBUG_TSFM,0x70129004) /* read */
#define REG_DEBUG_TSFM_DGM_MEMORY                           FIO_ADDRESS(DEBUG_TSFM,0x7012A000) /* read/write */
#define REG_DEBUG_TSFM_TRM_REF_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0x7012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_TGT_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0x7012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_STB_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0x7012C000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_TSFM_count_memd_tsfm_inst_valid */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_S;

typedef union { /* DEBUG_TSFM_count_memd_tsfm_vlc_stop */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_S;

typedef union { /* DEBUG_TSFM_count_tsfm_memd_inst_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_qcmem_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_qcmem_swap */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_vlc_stop */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_S;

typedef union { /* DEBUG_TSFM_count_code_tsfm_vlc_stop_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_S;

typedef union { /* DEBUG_TSFM_count_new_macro */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_NEW_MACRO_S;

typedef union { /* DEBUG_TSFM_count_jp_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_JP_DONE_S;

typedef union { /* DEBUG_TSFM_count_intra_4x4 */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTRA_4X4_S;

typedef union { /* DEBUG_TSFM_count_intra_16 */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTRA_16_S;

typedef union { /* DEBUG_TSFM_count_inter */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTER_S;

typedef union { /* DEBUG_TSFM_count_pending_inst_valid */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_inst_valid (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_memd_tsfm_inst_valid'. */
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_memd_tsfm_inst_valid'. */
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_memd_tsfm_vlc_stop'. */
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_memd_tsfm_vlc_stop'. */
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_memd_inst_done (read)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_memd_inst_done'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_memd_inst_done'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_done (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_qcmem_done'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_qcmem_done'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_swap (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_qcmem_swap'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_qcmem_swap'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_vlc_stop'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_vlc_stop'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_code_tsfm_vlc_stop_done (read)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_code_tsfm_vlc_stop_done'. */
U32  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_code_tsfm_vlc_stop_done'. */
U16  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_new_macro (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_new_macro'. */
U32  GH_DEBUG_TSFM_get_count_new_macro(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_new_macro'. */
U16  GH_DEBUG_TSFM_get_count_new_macro_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_new_macro(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_NEW_MACRO);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_new_macro] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_NEW_MACRO,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_new_macro_count(void)
{
    GH_DEBUG_TSFM_COUNT_NEW_MACRO_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_NEW_MACRO);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_new_macro_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_NEW_MACRO,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_jp_done (read)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_jp_done'. */
U32  GH_DEBUG_TSFM_get_count_jp_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_jp_done'. */
U16  GH_DEBUG_TSFM_get_count_jp_done_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_jp_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_JP_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_jp_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_JP_DONE,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_jp_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_JP_DONE_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_JP_DONE);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_jp_done_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_JP_DONE,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_4x4 (read)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_intra_4x4'. */
U32  GH_DEBUG_TSFM_get_count_intra_4x4(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_intra_4x4'. */
U16  GH_DEBUG_TSFM_get_count_intra_4x4_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_intra_4x4(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_4X4);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_4x4] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_4X4,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_intra_4x4_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_4X4_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_4X4);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_4x4_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_4X4,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_16 (read)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_intra_16'. */
U32  GH_DEBUG_TSFM_get_count_intra_16(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_intra_16'. */
U16  GH_DEBUG_TSFM_get_count_intra_16_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_intra_16(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_16);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_16] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_16,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_intra_16_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_16_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_16);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_16_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_16,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_inter (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_inter'. */
U32  GH_DEBUG_TSFM_get_count_inter(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_inter'. */
U16  GH_DEBUG_TSFM_get_count_inter_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_inter(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTER);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_inter] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTER,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_inter_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTER);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_inter_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTER,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_pending_inst_valid (read)                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_count_pending_inst_valid'. */
U32  GH_DEBUG_TSFM_get_count_pending_inst_valid(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_pending_inst_valid'. */
U16  GH_DEBUG_TSFM_get_count_pending_inst_valid_count(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_count_pending_inst_valid(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_pending_inst_valid] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID,value);
    #endif
    return value;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_pending_inst_valid_count(void)
{
    GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID);

    tmp_value.all = value;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_pending_inst_valid_count] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID,value);
    #endif
    return tmp_value.bitc.count;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_read_clear_all_debug_counters (read)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_read_clear_all_debug_counters'. */
U32  GH_DEBUG_TSFM_get_read_clear_all_debug_counters(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_read_clear_all_debug_counters(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_read_clear_all_debug_counters] --> 0x%08x\n",
                        REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist0_data (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_lbist0_data'. */
U32  GH_DEBUG_TSFM_get_lbist0_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_lbist0_data(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_LBIST0_DATA);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_lbist0_data] --> 0x%08x\n",
                        REG_DEBUG_TSFM_LBIST0_DATA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist1_data (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_lbist1_data'. */
U32  GH_DEBUG_TSFM_get_lbist1_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_lbist1_data(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_LBIST1_DATA);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_lbist1_data] --> 0x%08x\n",
                        REG_DEBUG_TSFM_LBIST1_DATA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_vlc_ci_medif (read)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_debug_vlc_ci_medif'. */
U32  GH_DEBUG_TSFM_get_debug_vlc_ci_medif(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_debug_vlc_ci_medif(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_debug_vlc_ci_medif] --> 0x%08x\n",
                        REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_tctrm (read)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'DEBUG_TSFM_debug_tctrm'. */
U32  GH_DEBUG_TSFM_get_debug_tctrm(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_DEBUG_TSFM_get_debug_tctrm(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_DEBUG_TCTRM);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_debug_tctrm] --> 0x%08x\n",
                        REG_DEBUG_TSFM_DEBUG_TCTRM,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_dgm_memory (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TSFM_dgm_memory'. */
void GH_DEBUG_TSFM_set_dgm_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_dgm_memory'. */
U32  GH_DEBUG_TSFM_get_dgm_memory(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TSFM_set_dgm_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_dgm_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TSFM_get_dgm_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_dgm_memory] --> 0x%08x\n",
                        (REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_ref_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TSFM_trm_ref_memory'. */
void GH_DEBUG_TSFM_set_trm_ref_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_ref_memory'. */
U32  GH_DEBUG_TSFM_get_trm_ref_memory(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TSFM_set_trm_ref_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_ref_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_ref_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_trm_ref_memory] --> 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_tgt_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TSFM_trm_tgt_memory'. */
void GH_DEBUG_TSFM_set_trm_tgt_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_tgt_memory'. */
U32  GH_DEBUG_TSFM_get_trm_tgt_memory(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TSFM_set_trm_tgt_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_tgt_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_tgt_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_trm_tgt_memory] --> 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_stb_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'DEBUG_TSFM_trm_stb_memory'. */
void GH_DEBUG_TSFM_set_trm_stb_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_stb_memory'. */
U32  GH_DEBUG_TSFM_get_trm_stb_memory(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_DEBUG_TSFM_set_trm_stb_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_stb_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_stb_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_trm_stb_memory] --> 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_TSFM_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_TSFM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

