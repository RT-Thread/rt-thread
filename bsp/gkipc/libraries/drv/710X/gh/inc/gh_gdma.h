/*!
*******************************************************************************
**
** \file      gh_gdma.h
**
** \brief     The Graphics DMA unit.
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
#ifndef _GH_GDMA_H
#define _GH_GDMA_H

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

#define GH_GDMA_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_GDMA_DEBUG_PRINT_FUNCTION printk
#else
#define GH_GDMA_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_GDMA_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_GDMA_SOURCE1_BASE                               FIO_ADDRESS(GDMA,0x90015000) /* read/write */
#define REG_GDMA_SOURCE1_PITCH                              FIO_ADDRESS(GDMA,0x90015004) /* read/write */
#define REG_GDMA_SOURCE2_BASE                               FIO_ADDRESS(GDMA,0x90015008) /* read/write */
#define REG_GDMA_SOURCE2_PITCH                              FIO_ADDRESS(GDMA,0x9001500C) /* read/write */
#define REG_GDMA_DESTINATION_BASE                           FIO_ADDRESS(GDMA,0x90015010) /* read/write */
#define REG_GDMA_DESTINATION_PITCH                          FIO_ADDRESS(GDMA,0x90015014) /* read/write */
#define REG_GDMA_WIDTH                                      FIO_ADDRESS(GDMA,0x90015018) /* read/write */
#define REG_GDMA_HEIGHT                                     FIO_ADDRESS(GDMA,0x9001501C) /* read/write */
#define REG_GDMA_TRANSPARENT                                FIO_ADDRESS(GDMA,0x90015020) /* read/write */
#define REG_GDMA_OPCODE                                     FIO_ADDRESS(GDMA,0x90015024) /* read/write */
#define REG_GDMA_NUM_PENDING_OPS                            FIO_ADDRESS(GDMA,0x90015028) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_SOURCE1_BASE'. */
void GH_GDMA_set_SOURCE1_BASE(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE1_BASE'. */
U32  GH_GDMA_get_SOURCE1_BASE(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_SOURCE1_PITCH'. */
void GH_GDMA_set_SOURCE1_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE1_PITCH'. */
U32  GH_GDMA_get_SOURCE1_PITCH(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_SOURCE2_BASE'. */
void GH_GDMA_set_SOURCE2_BASE(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE2_BASE'. */
U32  GH_GDMA_get_SOURCE2_BASE(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_SOURCE2_PITCH'. */
void GH_GDMA_set_SOURCE2_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE2_PITCH'. */
U32  GH_GDMA_get_SOURCE2_PITCH(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_BASE (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_DESTINATION_BASE'. */
void GH_GDMA_set_DESTINATION_BASE(U32 data);
/*! \brief Reads the register 'GDMA_DESTINATION_BASE'. */
U32  GH_GDMA_get_DESTINATION_BASE(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_PITCH (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_DESTINATION_PITCH'. */
void GH_GDMA_set_DESTINATION_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_DESTINATION_PITCH'. */
U32  GH_GDMA_get_DESTINATION_PITCH(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_WIDTH (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_WIDTH'. */
void GH_GDMA_set_WIDTH(U32 data);
/*! \brief Reads the register 'GDMA_WIDTH'. */
U32  GH_GDMA_get_WIDTH(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_HEIGHT (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_HEIGHT'. */
void GH_GDMA_set_HEIGHT(U32 data);
/*! \brief Reads the register 'GDMA_HEIGHT'. */
U32  GH_GDMA_get_HEIGHT(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_TRANSPARENT (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_TRANSPARENT'. */
void GH_GDMA_set_TRANSPARENT(U32 data);
/*! \brief Reads the register 'GDMA_TRANSPARENT'. */
U32  GH_GDMA_get_TRANSPARENT(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_OPCODE (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'GDMA_OPCODE'. */
void GH_GDMA_set_OPCODE(U32 data);
/*! \brief Reads the register 'GDMA_OPCODE'. */
U32  GH_GDMA_get_OPCODE(void);

/*----------------------------------------------------------------------------*/
/* register GDMA_NUM_PENDING_OPS (read)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'GDMA_NUM_PENDING_OPS'. */
U32  GH_GDMA_get_NUM_PENDING_OPS(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_GDMA_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_gdma.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_GDMA_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

