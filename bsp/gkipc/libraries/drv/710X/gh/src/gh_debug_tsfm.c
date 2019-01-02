/******************************************************************************
**
** \file      gh_debug_tsfm.c
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
#ifndef SRC_INLINE
#include "gh_debug_tsfm.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL      FIO_ADDRESS(DEBUG_TSFM,0x70128000) /* read */
#define REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL        FIO_ADDRESS(DEBUG_TSFM,0x70128004) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL       FIO_ADDRESS(DEBUG_TSFM,0x70128008) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL      FIO_ADDRESS(DEBUG_TSFM,0x7012800C) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL      FIO_ADDRESS(DEBUG_TSFM,0x70128010) /* read */
#define REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL        FIO_ADDRESS(DEBUG_TSFM,0x70128014) /* read */
#define REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL   FIO_ADDRESS(DEBUG_TSFM,0x70128018) /* read */
#define REG_DEBUG_TSFM_COUNT_NEW_MACRO_REAL                 FIO_ADDRESS(DEBUG_TSFM,0x7012801C) /* read */
#define REG_DEBUG_TSFM_COUNT_JP_DONE_REAL                   FIO_ADDRESS(DEBUG_TSFM,0x70128020) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_4X4_REAL                 FIO_ADDRESS(DEBUG_TSFM,0x70128024) /* read */
#define REG_DEBUG_TSFM_COUNT_INTRA_16_REAL                  FIO_ADDRESS(DEBUG_TSFM,0x70128028) /* read */
#define REG_DEBUG_TSFM_COUNT_INTER_REAL                     FIO_ADDRESS(DEBUG_TSFM,0x7012802C) /* read */
#define REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL        FIO_ADDRESS(DEBUG_TSFM,0x70128030) /* read */
#define REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS_REAL   FIO_ADDRESS(DEBUG_TSFM,0x70128034) /* read */
#define REG_DEBUG_TSFM_LBIST0_DATA_REAL                     FIO_ADDRESS(DEBUG_TSFM,0x70128080) /* read */
#define REG_DEBUG_TSFM_LBIST1_DATA_REAL                     FIO_ADDRESS(DEBUG_TSFM,0x70128084) /* read */
#define REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF_REAL              FIO_ADDRESS(DEBUG_TSFM,0x70129000) /* read */
#define REG_DEBUG_TSFM_DEBUG_TCTRM_REAL                     FIO_ADDRESS(DEBUG_TSFM,0x70129004) /* read */
#define REG_DEBUG_TSFM_DGM_MEMORY_REAL                      FIO_ADDRESS(DEBUG_TSFM,0x7012A000) /* read/write */
#define REG_DEBUG_TSFM_TRM_REF_MEMORY_REAL                  FIO_ADDRESS(DEBUG_TSFM,0x7012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_TGT_MEMORY_REAL                  FIO_ADDRESS(DEBUG_TSFM,0x7012B000) /* read/write */
#define REG_DEBUG_TSFM_TRM_STB_MEMORY_REAL                  FIO_ADDRESS(DEBUG_TSFM,0x7012C000) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DEBUG_TSFM_count_memd_tsfm_inst_valid */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL_S;

typedef union { /* DEBUG_TSFM_count_memd_tsfm_vlc_stop */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL_S;

typedef union { /* DEBUG_TSFM_count_tsfm_memd_inst_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_qcmem_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_qcmem_swap */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL_S;

typedef union { /* DEBUG_TSFM_count_tsfm_code_vlc_stop */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL_S;

typedef union { /* DEBUG_TSFM_count_code_tsfm_vlc_stop_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL_S;

typedef union { /* DEBUG_TSFM_count_new_macro */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_NEW_MACRO_REAL_S;

typedef union { /* DEBUG_TSFM_count_jp_done */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_JP_DONE_REAL_S;

typedef union { /* DEBUG_TSFM_count_intra_4x4 */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTRA_4X4_REAL_S;

typedef union { /* DEBUG_TSFM_count_intra_16 */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTRA_16_REAL_S;

typedef union { /* DEBUG_TSFM_count_inter */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_INTER_REAL_S;

typedef union { /* DEBUG_TSFM_count_pending_inst_valid */
    U32 all;
    struct {
        U32 count                       : 16;
        U32                             : 16;
    } bitc;
} GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_inst_valid (read)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL_S real;
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL_S real;
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count(void)
{
    GH_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_memd_inst_done (read)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL_S real;
    GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_done (read)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL_S real;
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_qcmem_swap (read)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL_S real;
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_tsfm_code_vlc_stop (read)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL_S real;
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count(void)
{
    GH_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_code_tsfm_vlc_stop_done (read)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done(void)
{
    GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL_S real;
    GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_new_macro (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_new_macro(void)
{
    GH_DEBUG_TSFM_COUNT_NEW_MACRO_REAL_S real;
    GH_DEBUG_TSFM_COUNT_NEW_MACRO_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_NEW_MACRO_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_new_macro_count(void)
{
    GH_DEBUG_TSFM_COUNT_NEW_MACRO_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_NEW_MACRO_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_jp_done (read)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_jp_done(void)
{
    GH_DEBUG_TSFM_COUNT_JP_DONE_REAL_S real;
    GH_DEBUG_TSFM_COUNT_JP_DONE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_JP_DONE_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_jp_done_count(void)
{
    GH_DEBUG_TSFM_COUNT_JP_DONE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_JP_DONE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_4x4 (read)                                 */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_intra_4x4(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_4X4_REAL_S real;
    GH_DEBUG_TSFM_COUNT_INTRA_4X4_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_4X4_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_intra_4x4_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_4X4_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_4X4_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_intra_16 (read)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_intra_16(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_16_REAL_S real;
    GH_DEBUG_TSFM_COUNT_INTRA_16_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_16_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_intra_16_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTRA_16_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_16_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_inter (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_inter(void)
{
    GH_DEBUG_TSFM_COUNT_INTER_REAL_S real;
    GH_DEBUG_TSFM_COUNT_INTER_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTER_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_inter_count(void)
{
    GH_DEBUG_TSFM_COUNT_INTER_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTER_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_pending_inst_valid (read)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_count_pending_inst_valid(void)
{
    GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL_S real;
    GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL);

    dummy.bitc.count = real.bitc.count;
    return dummy.all;
}
GH_INLINE U16  GH_DEBUG_TSFM_get_count_pending_inst_valid_count(void)
{
    GH_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.count;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_read_clear_all_debug_counters (read)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_read_clear_all_debug_counters(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_READ_CLEAR_ALL_DEBUG_COUNTERS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist0_data (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_lbist0_data(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_LBIST0_DATA_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_lbist1_data (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_lbist1_data(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_LBIST1_DATA_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_vlc_ci_medif (read)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_debug_vlc_ci_medif(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_DEBUG_VLC_CI_MEDIF_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_debug_tctrm (read)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_DEBUG_TSFM_get_debug_tctrm(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_DEBUG_TCTRM_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_dgm_memory (read/write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TSFM_set_dgm_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_DGM_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_TSFM_get_dgm_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_DGM_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_ref_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TSFM_set_trm_ref_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_REF_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_ref_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_REF_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_tgt_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TSFM_set_trm_tgt_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_TGT_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_tgt_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_TGT_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_trm_stb_memory (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TSFM_set_trm_stb_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_STB_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
}
GH_INLINE U32  GH_DEBUG_TSFM_get_trm_stb_memory(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_DEBUG_TSFM_TRM_STB_MEMORY_REAL + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)));

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_DEBUG_TSFM_init(void)
{
    int i;

    for (i=0; i<124; i++)
    {
        GH_DEBUG_TSFM_set_dgm_memory(i, (U32)0x00000000);
    }
    for (i=0; i<96; i++)
    {
        GH_DEBUG_TSFM_set_trm_ref_memory(i, (U32)0x00000000);
    }
    for (i=0; i<72; i++)
    {
        GH_DEBUG_TSFM_set_trm_tgt_memory(i, (U32)0x00000000);
    }
    for (i=0; i<72; i++)
    {
        GH_DEBUG_TSFM_set_trm_stb_memory(i, (U32)0x00000000);
    }
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

