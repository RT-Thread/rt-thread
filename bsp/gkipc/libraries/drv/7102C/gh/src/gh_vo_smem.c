/******************************************************************************
**
** \file      gh_vo_smem.c
**
** \brief     SMEM interface Registers.
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
#include "gh_vo_smem.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
U16                                     m_vo_smem_osd_b_mapped_in_debug_read_l;
U16                                     m_vo_smem_osd_b_mapped_in_debug_read_m;
U16                                     m_vo_smem_osd_b_mapped_in_debug_write_l;
U16                                     m_vo_smem_osd_b_mapped_in_debug_write_m;
U16                                     m_vo_smem_display_b_chroma_in_debug_read_l;
U16                                     m_vo_smem_display_b_chroma_in_debug_read_m;
U16                                     m_vo_smem_display_b_chroma_in_debug_write_l;
U16                                     m_vo_smem_display_b_chroma_in_debug_write_m;
U16                                     m_vo_smem_display_b_luma_in_debug_read_l;
U16                                     m_vo_smem_display_b_luma_in_debug_read_m;
U16                                     m_vo_smem_display_b_luma_in_debug_write_l;
U16                                     m_vo_smem_display_b_luma_in_debug_write_m;
U16                                     m_vo_smem_orc_in_debug_read_l;
U16                                     m_vo_smem_orc_in_debug_read_m;
U16                                     m_vo_smem_orc_in_debug_write_l;
U16                                     m_vo_smem_orc_in_debug_write_m;

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L (read)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M (read)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L (read)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M (read)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L (read)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M (read)                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M (read)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M);

    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L (write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_read_l);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_read_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M (write)                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_read_m);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_read_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L (write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_write_l);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_write_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M (write)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_write_m);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_write_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L (write)                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_read_l);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_read_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M (write)                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_read_m);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_read_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L (write)                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_write_l);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_write_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M (write)                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_write_m);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_write_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L (write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_read_l);
    #endif
    return m_vo_smem_display_b_luma_in_debug_read_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M (write)                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_read_m);
    #endif
    return m_vo_smem_display_b_luma_in_debug_read_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L (write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_write_l);
    #endif
    return m_vo_smem_display_b_luma_in_debug_write_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M (write)                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_write_m);
    #endif
    return m_vo_smem_display_b_luma_in_debug_write_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_L (write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_orc_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_READ_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_read_l);
    #endif
    return m_vo_smem_orc_in_debug_read_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_M (write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_orc_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_READ_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_read_m);
    #endif
    return m_vo_smem_orc_in_debug_read_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_L (write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_orc_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_write_l);
    #endif
    return m_vo_smem_orc_in_debug_write_l;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_M (write)                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_orc_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M,data,data);
    #endif
}
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_write_m);
    #endif
    return m_vo_smem_orc_in_debug_write_m;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_VO_SMEM_init(void)
{
    GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L((U16)0x00000000);
    GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M((U16)0x00000000);
    GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L((U16)0x00000000);
    GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L((U16)0x00000000);
    GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M((U16)0x00000000);
    GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L((U16)0x00000000);
    GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M((U16)0x00000000);
    GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L((U16)0x00000000);
    GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M((U16)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

