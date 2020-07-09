/*!
*******************************************************************************
**
** \file      gh_debug_tsfm.h
**
** \brief     TSFM Debug Registers.
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID           FIO_ADDRESS(DEBUG_TSFM,0xa0128000) /* read */
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP             FIO_ADDRESS(DEBUG_TSFM,0xa0128004) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE            FIO_ADDRESS(DEBUG_TSFM,0xa0128008) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE           FIO_ADDRESS(DEBUG_TSFM,0xa012800C) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP           FIO_ADDRESS(DEBUG_TSFM,0xa0128010) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP             FIO_ADDRESS(DEBUG_TSFM,0xa0128014) /* read */
#define REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE        FIO_ADDRESS(DEBUG_TSFM,0xa0128018) /* read */
#define REG_DEBUG_TSFM_COUNT_NEW_MACRO                      FIO_ADDRESS(DEBUG_TSFM,0xa012801C) /* read */
#define REG_DEBUG_TSFM_COUNT_JP_DONE                        FIO_ADDRESS(DEBUG_TSFM,0xa0128020) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_4X4                      FIO_ADDRESS(DEBUG_TSFM,0xa0128024) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_16                       FIO_ADDRESS(DEBUG_TSFM,0xa0128028) /* read */
#define REG_DEBUG_TSFM_COUNT_INTER                          FIO_ADDRESS(DEBUG_TSFM,0xa012802C) /* read */
#define REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID             FIO_ADDRESS(DEBUG_TSFM,0xa0128030) /* read */
#define REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS        FIO_ADDRESS(DEBUG_TSFM,0xa0128034) /* read */
#define REG_DEBUG_TSFM_LBIST0_DATA                          FIO_ADDRESS(DEBUG_TSFM,0xa0128080) /* read */
#define REG_DEBUG_TSFM_LBIST1_DATA                          FIO_ADDRESS(DEBUG_TSFM,0xa0128084) /* read */
#define REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF                   FIO_ADDRESS(DEBUG_TSFM,0xa0129000) /* read */
#define REG_DEBUG_TSFM_DEBUG_TCTRM                          FIO_ADDRESS(DEBUG_TSFM,0xa0129004) /* read */
#define REG_DEBUG_TSFM_DGM_MEMORY                           FIO_ADDRESS(DEBUG_TSFM,0xa012A000) /* read/write */
#define REG_DEBUG_TSFM_TRM_REF_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0xa012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_TGT_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0xa012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_STB_MEMORY                       FIO_ADDRESS(DEBUG_TSFM,0xa012C000) /* read/write */

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
/*! \brief Reads the register 'DEBUG_TSFM_count_memd_tsfm_inst_valid'. */
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_memd_tsfm_inst_valid'. */
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_memd_tsfm_vlc_stop'. */
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_memd_tsfm_vlc_stop'. */
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_memd_inst_done (read)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_memd_inst_done'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_memd_inst_done'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_done (read)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_qcmem_done'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_qcmem_done'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_swap (read)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_qcmem_swap'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_qcmem_swap'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_tsfm_code_vlc_stop'. */
U32  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_tsfm_code_vlc_stop'. */
U16  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_code_tsfm_vlc_stop_done (read)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_code_tsfm_vlc_stop_done'. */
U32  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_code_tsfm_vlc_stop_done'. */
U16  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_new_macro (read)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_new_macro'. */
U32  GH_DEBUG_TSFM_get_count_new_macro(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_new_macro'. */
U16  GH_DEBUG_TSFM_get_count_new_macro_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_jp_done (read)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_jp_done'. */
U32  GH_DEBUG_TSFM_get_count_jp_done(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_jp_done'. */
U16  GH_DEBUG_TSFM_get_count_jp_done_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_4x4 (read)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_intra_4x4'. */
U32  GH_DEBUG_TSFM_get_count_intra_4x4(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_intra_4x4'. */
U16  GH_DEBUG_TSFM_get_count_intra_4x4_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_16 (read)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_intra_16'. */
U32  GH_DEBUG_TSFM_get_count_intra_16(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_intra_16'. */
U16  GH_DEBUG_TSFM_get_count_intra_16_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_inter (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_inter'. */
U32  GH_DEBUG_TSFM_get_count_inter(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_inter'. */
U16  GH_DEBUG_TSFM_get_count_inter_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_pending_inst_valid (read)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_count_pending_inst_valid'. */
U32  GH_DEBUG_TSFM_get_count_pending_inst_valid(void);
/*! \brief Reads the bit group 'count' of register 'DEBUG_TSFM_count_pending_inst_valid'. */
U16  GH_DEBUG_TSFM_get_count_pending_inst_valid_count(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_read_clear_all_debug_counters (read)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_read_clear_all_debug_counters'. */
U32  GH_DEBUG_TSFM_get_read_clear_all_debug_counters(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist0_data (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_lbist0_data'. */
U32  GH_DEBUG_TSFM_get_lbist0_data(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist1_data (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_lbist1_data'. */
U32  GH_DEBUG_TSFM_get_lbist1_data(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_vlc_ci_medif (read)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_debug_vlc_ci_medif'. */
U32  GH_DEBUG_TSFM_get_debug_vlc_ci_medif(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_tctrm (read)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DEBUG_TSFM_debug_tctrm'. */
U32  GH_DEBUG_TSFM_get_debug_tctrm(void);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_dgm_memory (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_TSFM_dgm_memory'. */
void GH_DEBUG_TSFM_set_dgm_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_dgm_memory'. */
U32  GH_DEBUG_TSFM_get_dgm_memory(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_ref_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_TSFM_trm_ref_memory'. */
void GH_DEBUG_TSFM_set_trm_ref_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_ref_memory'. */
U32  GH_DEBUG_TSFM_get_trm_ref_memory(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_tgt_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_TSFM_trm_tgt_memory'. */
void GH_DEBUG_TSFM_set_trm_tgt_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_tgt_memory'. */
U32  GH_DEBUG_TSFM_get_trm_tgt_memory(U8 index);

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_stb_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DEBUG_TSFM_trm_stb_memory'. */
void GH_DEBUG_TSFM_set_trm_stb_memory(U8 index, U32 data);
/*! \brief Reads the register 'DEBUG_TSFM_trm_stb_memory'. */
U32  GH_DEBUG_TSFM_get_trm_stb_memory(U8 index);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DEBUG_TSFM_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_debug_tsfm.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_DEBUG_TSFM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

