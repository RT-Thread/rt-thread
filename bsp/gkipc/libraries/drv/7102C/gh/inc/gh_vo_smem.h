/*!
*******************************************************************************
**
** \file      gh_vo_smem.h
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
#ifndef _GH_VO_SMEM_H
#define _GH_VO_SMEM_H

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

#define GH_VO_SMEM_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_SMEM_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_SMEM_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_SMEM_ENABLE_DEBUG_PRINT
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
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L          FIO_ADDRESS(VO_SMEM,0x90004050) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M          FIO_ADDRESS(VO_SMEM,0x90004054) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L         FIO_ADDRESS(VO_SMEM,0x90004058) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M         FIO_ADDRESS(VO_SMEM,0x9000405C) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L            FIO_ADDRESS(VO_SMEM,0x90004060) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M            FIO_ADDRESS(VO_SMEM,0x90004064) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L           FIO_ADDRESS(VO_SMEM,0x90004068) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M           FIO_ADDRESS(VO_SMEM,0x9000406C) /* read */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L            FIO_ADDRESS(VO_SMEM,0x90004070) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M            FIO_ADDRESS(VO_SMEM,0x90004074) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L           FIO_ADDRESS(VO_SMEM,0x90004078) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M           FIO_ADDRESS(VO_SMEM,0x9000407C) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L        FIO_ADDRESS(VO_SMEM,0x90004080) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M        FIO_ADDRESS(VO_SMEM,0x90004084) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L       FIO_ADDRESS(VO_SMEM,0x90004088) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M       FIO_ADDRESS(VO_SMEM,0x9000408C) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L          FIO_ADDRESS(VO_SMEM,0x90004090) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M          FIO_ADDRESS(VO_SMEM,0x90004094) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L         FIO_ADDRESS(VO_SMEM,0x90004098) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M         FIO_ADDRESS(VO_SMEM,0x9000409C) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_L                     FIO_ADDRESS(VO_SMEM,0x900040A0) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_M                     FIO_ADDRESS(VO_SMEM,0x900040A4) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L                    FIO_ADDRESS(VO_SMEM,0x900040A8) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M                    FIO_ADDRESS(VO_SMEM,0x900040AC) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U16                                     m_vo_smem_osd_b_mapped_in_debug_read_l;
extern U16                                     m_vo_smem_osd_b_mapped_in_debug_read_m;
extern U16                                     m_vo_smem_osd_b_mapped_in_debug_write_l;
extern U16                                     m_vo_smem_osd_b_mapped_in_debug_write_m;
extern U16                                     m_vo_smem_display_b_chroma_in_debug_read_l;
extern U16                                     m_vo_smem_display_b_chroma_in_debug_read_m;
extern U16                                     m_vo_smem_display_b_chroma_in_debug_write_l;
extern U16                                     m_vo_smem_display_b_chroma_in_debug_write_m;
extern U16                                     m_vo_smem_display_b_luma_in_debug_read_l;
extern U16                                     m_vo_smem_display_b_luma_in_debug_read_m;
extern U16                                     m_vo_smem_display_b_luma_in_debug_write_l;
extern U16                                     m_vo_smem_display_b_luma_in_debug_write_m;
extern U16                                     m_vo_smem_orc_in_debug_read_l;
extern U16                                     m_vo_smem_orc_in_debug_read_m;
extern U16                                     m_vo_smem_orc_in_debug_write_l;
extern U16                                     m_vo_smem_orc_in_debug_write_m;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L (read)                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L(void)
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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M(void)
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
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L(void)
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
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M(void)
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
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L(void)
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
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_osd_b_mapped_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_chroma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(void)
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
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_display_b_luma_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(void)
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
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L(U16 data)
{
    m_vo_smem_orc_in_debug_read_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_READ_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L(void)
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
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M(U16 data)
{
    m_vo_smem_orc_in_debug_read_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_READ_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_READ_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M(void)
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
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L(U16 data)
{
    m_vo_smem_orc_in_debug_write_l = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L(void)
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
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M(U16 data)
{
    m_vo_smem_orc_in_debug_write_m = data;
    *(volatile U16 *)REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M = data;
    #if GH_VO_SMEM_ENABLE_DEBUG_PRINT
    GH_VO_SMEM_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M] <-- 0x%08x\n",
                        REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M,data,data);
    #endif
}
GH_INLINE U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M(void)
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
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_SMEM_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_SMEM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

