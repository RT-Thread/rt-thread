/******************************************************************************
**
** \file      gh_debug_tsfm.c
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
#include "gh_debug_tsfm.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register DEBUG_TSFM_count_memd_tsfm_inst_valid (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_INST_VALID,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_inst_valid_count(void)
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
U32  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_MEMD_TSFM_VLC_STOP,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_memd_tsfm_vlc_stop_count(void)
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
U32  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_MEMD_INST_DONE,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_tsfm_memd_inst_done_count(void)
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
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_DONE,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_done_count(void)
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
U32  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_QCMEM_SWAP,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_tsfm_code_qcmem_swap_count(void)
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
U32  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_TSFM_CODE_VLC_STOP,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_tsfm_code_vlc_stop_count(void)
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
U32  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_CODE_TSFM_VLC_STOP_DONE,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_code_tsfm_vlc_stop_done_count(void)
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
U32  GH_DEBUG_TSFM_get_count_new_macro(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_NEW_MACRO);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_new_macro] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_NEW_MACRO,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_new_macro_count(void)
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
U32  GH_DEBUG_TSFM_get_count_jp_done(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_JP_DONE);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_jp_done] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_JP_DONE,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_jp_done_count(void)
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
U32  GH_DEBUG_TSFM_get_count_intra_4x4(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_4X4);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_4x4] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_4X4,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_intra_4x4_count(void)
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
U32  GH_DEBUG_TSFM_get_count_intra_16(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTRA_16);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_intra_16] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTRA_16,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_intra_16_count(void)
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
U32  GH_DEBUG_TSFM_get_count_inter(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_INTER);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_inter] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_INTER,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_inter_count(void)
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
U32  GH_DEBUG_TSFM_get_count_pending_inst_valid(void)
{
    U32 value = (*(volatile U32 *)REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID);

    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_DEBUG_TSFM_get_count_pending_inst_valid] --> 0x%08x\n",
                        REG_DEBUG_TSFM_COUNT_PENDING_INST_VALID,value);
    #endif
    return value;
}
U16  GH_DEBUG_TSFM_get_count_pending_inst_valid_count(void)
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
U32  GH_DEBUG_TSFM_get_read_clear_all_debug_counters(void)
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
U32  GH_DEBUG_TSFM_get_lbist0_data(void)
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
U32  GH_DEBUG_TSFM_get_lbist1_data(void)
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
U32  GH_DEBUG_TSFM_get_debug_vlc_ci_medif(void)
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
U32  GH_DEBUG_TSFM_get_debug_tctrm(void)
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
void GH_DEBUG_TSFM_set_dgm_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_dgm_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_DGM_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_TSFM_get_dgm_memory(U8 index)
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
void GH_DEBUG_TSFM_set_trm_ref_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_ref_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_REF_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_TSFM_get_trm_ref_memory(U8 index)
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
void GH_DEBUG_TSFM_set_trm_tgt_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_tgt_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_TGT_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_TSFM_get_trm_tgt_memory(U8 index)
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
void GH_DEBUG_TSFM_set_trm_stb_memory(U8 index, U32 data)
{
    *(volatile U32 *)(REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)) = data;
    #if GH_DEBUG_TSFM_ENABLE_DEBUG_PRINT
    GH_DEBUG_TSFM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_DEBUG_TSFM_set_trm_stb_memory] <-- 0x%08x\n",
                        (REG_DEBUG_TSFM_TRM_STB_MEMORY + index * FIO_MOFFSET(DEBUG_TSFM,0x00000004)),data,data);
    #endif
}
U32  GH_DEBUG_TSFM_get_trm_stb_memory(U8 index)
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
void GH_DEBUG_TSFM_init(void)
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

