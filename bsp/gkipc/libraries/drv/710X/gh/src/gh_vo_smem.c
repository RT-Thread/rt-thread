/******************************************************************************
**
** \file      gh_vo_smem.c
**
** \brief     SMEM interface Registers.
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
#include "gh_vo_smem.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L_REAL     FIO_ADDRESS(VO_SMEM,0x60008050) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M_REAL     FIO_ADDRESS(VO_SMEM,0x60008054) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L_REAL    FIO_ADDRESS(VO_SMEM,0x60008058) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M_REAL    FIO_ADDRESS(VO_SMEM,0x6000805C) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L_REAL       FIO_ADDRESS(VO_SMEM,0x60008060) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M_REAL       FIO_ADDRESS(VO_SMEM,0x60008064) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L_REAL      FIO_ADDRESS(VO_SMEM,0x60008068) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M_REAL      FIO_ADDRESS(VO_SMEM,0x6000806C) /* read */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L_REAL       FIO_ADDRESS(VO_SMEM,0x60008070) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M_REAL       FIO_ADDRESS(VO_SMEM,0x60008074) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L_REAL      FIO_ADDRESS(VO_SMEM,0x60008078) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M_REAL      FIO_ADDRESS(VO_SMEM,0x6000807C) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L_REAL   FIO_ADDRESS(VO_SMEM,0x60008080) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M_REAL   FIO_ADDRESS(VO_SMEM,0x60008084) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L_REAL  FIO_ADDRESS(VO_SMEM,0x60008088) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M_REAL  FIO_ADDRESS(VO_SMEM,0x6000808C) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L_REAL     FIO_ADDRESS(VO_SMEM,0x60008090) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M_REAL     FIO_ADDRESS(VO_SMEM,0x60008094) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L_REAL    FIO_ADDRESS(VO_SMEM,0x60008098) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M_REAL    FIO_ADDRESS(VO_SMEM,0x6000809C) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_L_REAL                FIO_ADDRESS(VO_SMEM,0x600080A0) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_M_REAL                FIO_ADDRESS(VO_SMEM,0x600080A4) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L_REAL               FIO_ADDRESS(VO_SMEM,0x600080A8) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M_REAL               FIO_ADDRESS(VO_SMEM,0x600080AC) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/

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
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M (read)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L (read)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M (read)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L (read)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M (read)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L (read)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M (read)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M(void)
{
    U16 value = (*(volatile U16 *)REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L (write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_read_l);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_read_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M (write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_read_m);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_read_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L (write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_write_l);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_write_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M (write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_osd_b_mapped_in_debug_write_m);
    #endif
    return m_vo_smem_osd_b_mapped_in_debug_write_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L (write)                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_read_l);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_read_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M (write)                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_read_m);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_read_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L (write)                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_write_l);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_write_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M (write)                 */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_display_b_chroma_in_debug_write_m);
    #endif
    return m_vo_smem_display_b_chroma_in_debug_write_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L (write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_read_l);
    #endif
    return m_vo_smem_display_b_luma_in_debug_read_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M (write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_read_m);
    #endif
    return m_vo_smem_display_b_luma_in_debug_read_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L (write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_write_l);
    #endif
    return m_vo_smem_display_b_luma_in_debug_write_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M (write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_display_b_luma_in_debug_write_m);
    #endif
    return m_vo_smem_display_b_luma_in_debug_write_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_L (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_orc_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_read_l);
    #endif
    return m_vo_smem_orc_in_debug_read_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_M (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_orc_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_read_m);
    #endif
    return m_vo_smem_orc_in_debug_read_m;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_L (write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_orc_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_write_l);
    #endif
    return m_vo_smem_orc_in_debug_write_l;
}

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_M (write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_orc_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M_REAL = data;
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M(void)
{
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "[GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M] --> 0x%08x\n",
                        m_vo_smem_orc_in_debug_write_m);
    #endif
    return m_vo_smem_orc_in_debug_write_m;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_SMEM_init(void)
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

