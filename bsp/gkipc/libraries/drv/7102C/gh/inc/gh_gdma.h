/*!
*******************************************************************************
**
** \file      gh_gdma.h
**
** \brief     The Graphics DMA unit.
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
#define REG_GDMA_SOURCE1_BASE                               FIO_ADDRESS(GDMA,0x60015000) /* read/write */
#define REG_GDMA_SOURCE1_PITCH                              FIO_ADDRESS(GDMA,0x60015004) /* read/write */
#define REG_GDMA_SOURCE2_BASE                               FIO_ADDRESS(GDMA,0x60015008) /* read/write */
#define REG_GDMA_SOURCE2_PITCH                              FIO_ADDRESS(GDMA,0x6001500C) /* read/write */
#define REG_GDMA_DESTINATION_BASE                           FIO_ADDRESS(GDMA,0x60015010) /* read/write */
#define REG_GDMA_DESTINATION_PITCH                          FIO_ADDRESS(GDMA,0x60015014) /* read/write */
#define REG_GDMA_WIDTH                                      FIO_ADDRESS(GDMA,0x60015018) /* read/write */
#define REG_GDMA_HEIGHT                                     FIO_ADDRESS(GDMA,0x6001501C) /* read/write */
#define REG_GDMA_TRANSPARENT                                FIO_ADDRESS(GDMA,0x60015020) /* read/write */
#define REG_GDMA_OPCODE                                     FIO_ADDRESS(GDMA,0x60015024) /* read/write */
#define REG_GDMA_NUM_PENDING_OPS                            FIO_ADDRESS(GDMA,0x60015028) /* read */

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
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_SOURCE1_BASE'. */
void GH_GDMA_set_SOURCE1_BASE(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE1_BASE'. */
U32  GH_GDMA_get_SOURCE1_BASE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_SOURCE1_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE1_BASE] <-- 0x%08x\n",
                        REG_GDMA_SOURCE1_BASE,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_SOURCE1_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE1_BASE] --> 0x%08x\n",
                        REG_GDMA_SOURCE1_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE1_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_SOURCE1_PITCH'. */
void GH_GDMA_set_SOURCE1_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE1_PITCH'. */
U32  GH_GDMA_get_SOURCE1_PITCH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_SOURCE1_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE1_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE1_PITCH] <-- 0x%08x\n",
                        REG_GDMA_SOURCE1_PITCH,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_SOURCE1_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE1_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE1_PITCH] --> 0x%08x\n",
                        REG_GDMA_SOURCE1_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_BASE (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_SOURCE2_BASE'. */
void GH_GDMA_set_SOURCE2_BASE(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE2_BASE'. */
U32  GH_GDMA_get_SOURCE2_BASE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_SOURCE2_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE2_BASE] <-- 0x%08x\n",
                        REG_GDMA_SOURCE2_BASE,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_SOURCE2_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE2_BASE] --> 0x%08x\n",
                        REG_GDMA_SOURCE2_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_SOURCE2_PITCH (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_SOURCE2_PITCH'. */
void GH_GDMA_set_SOURCE2_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_SOURCE2_PITCH'. */
U32  GH_GDMA_get_SOURCE2_PITCH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_SOURCE2_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_SOURCE2_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_SOURCE2_PITCH] <-- 0x%08x\n",
                        REG_GDMA_SOURCE2_PITCH,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_SOURCE2_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_SOURCE2_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_SOURCE2_PITCH] --> 0x%08x\n",
                        REG_GDMA_SOURCE2_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_BASE (read/write)                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_DESTINATION_BASE'. */
void GH_GDMA_set_DESTINATION_BASE(U32 data);
/*! \brief Reads the register 'GDMA_DESTINATION_BASE'. */
U32  GH_GDMA_get_DESTINATION_BASE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_DESTINATION_BASE(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_BASE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_DESTINATION_BASE] <-- 0x%08x\n",
                        REG_GDMA_DESTINATION_BASE,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_DESTINATION_BASE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_BASE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_DESTINATION_BASE] --> 0x%08x\n",
                        REG_GDMA_DESTINATION_BASE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_DESTINATION_PITCH (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_DESTINATION_PITCH'. */
void GH_GDMA_set_DESTINATION_PITCH(U32 data);
/*! \brief Reads the register 'GDMA_DESTINATION_PITCH'. */
U32  GH_GDMA_get_DESTINATION_PITCH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_DESTINATION_PITCH(U32 data)
{
    *(volatile U32 *)REG_GDMA_DESTINATION_PITCH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_DESTINATION_PITCH] <-- 0x%08x\n",
                        REG_GDMA_DESTINATION_PITCH,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_DESTINATION_PITCH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_DESTINATION_PITCH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_DESTINATION_PITCH] --> 0x%08x\n",
                        REG_GDMA_DESTINATION_PITCH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_WIDTH (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_WIDTH'. */
void GH_GDMA_set_WIDTH(U32 data);
/*! \brief Reads the register 'GDMA_WIDTH'. */
U32  GH_GDMA_get_WIDTH(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_WIDTH(U32 data)
{
    *(volatile U32 *)REG_GDMA_WIDTH = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_WIDTH] <-- 0x%08x\n",
                        REG_GDMA_WIDTH,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_WIDTH(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_WIDTH);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_WIDTH] --> 0x%08x\n",
                        REG_GDMA_WIDTH,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_HEIGHT (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_HEIGHT'. */
void GH_GDMA_set_HEIGHT(U32 data);
/*! \brief Reads the register 'GDMA_HEIGHT'. */
U32  GH_GDMA_get_HEIGHT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_HEIGHT(U32 data)
{
    *(volatile U32 *)REG_GDMA_HEIGHT = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_HEIGHT] <-- 0x%08x\n",
                        REG_GDMA_HEIGHT,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_HEIGHT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_HEIGHT);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_HEIGHT] --> 0x%08x\n",
                        REG_GDMA_HEIGHT,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_TRANSPARENT (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_TRANSPARENT'. */
void GH_GDMA_set_TRANSPARENT(U32 data);
/*! \brief Reads the register 'GDMA_TRANSPARENT'. */
U32  GH_GDMA_get_TRANSPARENT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_TRANSPARENT(U32 data)
{
    *(volatile U32 *)REG_GDMA_TRANSPARENT = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_TRANSPARENT] <-- 0x%08x\n",
                        REG_GDMA_TRANSPARENT,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_TRANSPARENT(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_TRANSPARENT);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_TRANSPARENT] --> 0x%08x\n",
                        REG_GDMA_TRANSPARENT,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_OPCODE (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'GDMA_OPCODE'. */
void GH_GDMA_set_OPCODE(U32 data);
/*! \brief Reads the register 'GDMA_OPCODE'. */
U32  GH_GDMA_get_OPCODE(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_GDMA_set_OPCODE(U32 data)
{
    *(volatile U32 *)REG_GDMA_OPCODE = data;
    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_GDMA_set_OPCODE] <-- 0x%08x\n",
                        REG_GDMA_OPCODE,data,data);
    #endif
}
GH_INLINE U32  GH_GDMA_get_OPCODE(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_OPCODE);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_OPCODE] --> 0x%08x\n",
                        REG_GDMA_OPCODE,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register GDMA_NUM_PENDING_OPS (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'GDMA_NUM_PENDING_OPS'. */
U32  GH_GDMA_get_NUM_PENDING_OPS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_GDMA_get_NUM_PENDING_OPS(void)
{
    U32 value = (*(volatile U32 *)REG_GDMA_NUM_PENDING_OPS);

    #if GH_GDMA_ENABLE_DEBUG_PRINT
    GH_GDMA_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_GDMA_get_NUM_PENDING_OPS] --> 0x%08x\n",
                        REG_GDMA_NUM_PENDING_OPS,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_GDMA_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_GDMA_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

