/*!
*******************************************************************************
**
** \file      gh_vo_smem.h
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L          FIO_ADDRESS(VO_SMEM,0x90008050) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M          FIO_ADDRESS(VO_SMEM,0x90008054) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L         FIO_ADDRESS(VO_SMEM,0x90008058) /* read */
#define REG_VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M         FIO_ADDRESS(VO_SMEM,0x9000805C) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L            FIO_ADDRESS(VO_SMEM,0x90008060) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M            FIO_ADDRESS(VO_SMEM,0x90008064) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L           FIO_ADDRESS(VO_SMEM,0x90008068) /* read */
#define REG_VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M           FIO_ADDRESS(VO_SMEM,0x9000806C) /* read */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L            FIO_ADDRESS(VO_SMEM,0x90008070) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M            FIO_ADDRESS(VO_SMEM,0x90008074) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L           FIO_ADDRESS(VO_SMEM,0x90008078) /* write */
#define REG_VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M           FIO_ADDRESS(VO_SMEM,0x9000807C) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L        FIO_ADDRESS(VO_SMEM,0x90008080) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M        FIO_ADDRESS(VO_SMEM,0x90008084) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L       FIO_ADDRESS(VO_SMEM,0x90008088) /* write */
#define REG_VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M       FIO_ADDRESS(VO_SMEM,0x9000808C) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L          FIO_ADDRESS(VO_SMEM,0x90008090) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M          FIO_ADDRESS(VO_SMEM,0x90008094) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L         FIO_ADDRESS(VO_SMEM,0x90008098) /* write */
#define REG_VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M         FIO_ADDRESS(VO_SMEM,0x9000809C) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_L                     FIO_ADDRESS(VO_SMEM,0x900080A0) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_READ_M                     FIO_ADDRESS(VO_SMEM,0x900080A4) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_L                    FIO_ADDRESS(VO_SMEM,0x900080A8) /* write */
#define REG_VO_SMEM_ORC_IN_DEBUG_WRITE_M                    FIO_ADDRESS(VO_SMEM,0x900080AC) /* write */

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
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M (read)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L (read)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M (read)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_CHROMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_get_MIXER_B_CHROMA_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L (read)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M (read)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L (read)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M (read)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_SMEM_MIXER_B_LUMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_get_MIXER_B_LUMA_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L (write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M (write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L (write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M (write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_OSD_B_MAPPED_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_OSD_B_MAPPED_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_OSD_B_MAPPED_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L (write)                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M (write)                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L (write)                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M (write)                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_CHROMA_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L (write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M (write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L (write)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M (write)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_DISPLAY_B_LUMA_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_L (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_READ_L'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_READ_L'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_READ_M (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_READ_M'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_READ_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_READ_M'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_READ_M(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_L (write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_L'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_L(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_L'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_SMEM_ORC_IN_DEBUG_WRITE_M (write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_M'. */
void GH_VO_SMEM_set_ORC_IN_DEBUG_WRITE_M(U16 data);
/*! \brief Reads the mirror variable of the register 'VO_SMEM_ORC_IN_DEBUG_WRITE_M'. */
U16  GH_VO_SMEM_getm_ORC_IN_DEBUG_WRITE_M(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_SMEM_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_smem.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_SMEM_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

