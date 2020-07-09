/*!
*******************************************************************************
**
** \file      gh_vic.h
**
** \brief     VIC.
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
#ifndef _GH_VIC_H
#define _GH_VIC_H

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

#define GH_VIC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VIC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VIC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VIC_ENABLE_DEBUG_PRINT
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
#define REG_VIC_SENSE                                       FIO_ADDRESS(VIC,0x90008000) /* read/write */
#define REG_VIC_EVENT                                       FIO_ADDRESS(VIC,0x90008004) /* read/write */
#define REG_VIC_BOTHEDGE                                    FIO_ADDRESS(VIC,0x90008008) /* read/write */
#define REG_VIC_SELECT                                      FIO_ADDRESS(VIC,0x9000800C) /* read/write */
#define REG_VIC_ENABLE                                      FIO_ADDRESS(VIC,0x90008010) /* read/write */
#define REG_VIC_ENCLR                                       FIO_ADDRESS(VIC,0x90008014) /* write */
#define REG_VIC_RAWSTS                                      FIO_ADDRESS(VIC,0x90008018) /* read */
#define REG_VIC_SOFTINT                                     FIO_ADDRESS(VIC,0x9000801C) /* read/write */
#define REG_VIC_SOFTINTRCLR                                 FIO_ADDRESS(VIC,0x90008020) /* write */
#define REG_VIC_PROTECT                                     FIO_ADDRESS(VIC,0x90008024) /* read/write */
#define REG_VIC_IRQSTS                                      FIO_ADDRESS(VIC,0x90008030) /* read */
#define REG_VIC_FIQSTS                                      FIO_ADDRESS(VIC,0x90008034) /* read */
#define REG_VIC_EDGECLR                                     FIO_ADDRESS(VIC,0x90008038) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VIC_Protect */
    U32 all;
    struct {
        U32 protect                     : 1;
        U32                             : 31;
    } bitc;
} GH_VIC_PROTECT_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern U32                                     m_vic_enclr[2];
extern U32                                     m_vic_softintrclr[2];
extern U32                                     m_vic_edgeclr[2];

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VIC_Sense (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_Sense'. */
void GH_VIC_set_Sense(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Sense'. */
U32  GH_VIC_get_Sense(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_Sense(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Sense] <-- 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_Sense(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Sense] --> 0x%08x\n",
                        (REG_VIC_SENSE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Event (read/write)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_Event'. */
void GH_VIC_set_Event(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Event'. */
U32  GH_VIC_get_Event(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_Event(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Event] <-- 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_Event(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Event] --> 0x%08x\n",
                        (REG_VIC_EVENT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_BothEdge (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_BothEdge'. */
void GH_VIC_set_BothEdge(U8 index, U32 data);
/*! \brief Reads the register 'VIC_BothEdge'. */
U32  GH_VIC_get_BothEdge(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_BothEdge(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_BothEdge] <-- 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_BothEdge(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_BothEdge] --> 0x%08x\n",
                        (REG_VIC_BOTHEDGE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Select (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_Select'. */
void GH_VIC_set_Select(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Select'. */
U32  GH_VIC_get_Select(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_Select(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Select] <-- 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_Select(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Select] --> 0x%08x\n",
                        (REG_VIC_SELECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_Enable (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_Enable'. */
void GH_VIC_set_Enable(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Enable'. */
U32  GH_VIC_get_Enable(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_Enable(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Enable] <-- 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_Enable(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Enable] --> 0x%08x\n",
                        (REG_VIC_ENABLE + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_EnClr (write)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VIC_EnClr'. */
void GH_VIC_set_EnClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_EnClr'. */
U32  GH_VIC_getm_EnClr(U8 index);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VIC_set_EnClr(U8 index, U32 data)
{
    m_vic_enclr[index] = data;
    *(volatile U32 *)(REG_VIC_ENCLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EnClr] <-- 0x%08x\n",
                        (REG_VIC_ENCLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_EnClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EnClr] --> 0x%08x\n",
                        m_vic_enclr[index]);
    #endif
    return m_vic_enclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VIC_RawSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIC_RawSts'. */
U32  GH_VIC_get_RawSts(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIC_get_RawSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_RAWSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_RawSts] --> 0x%08x\n",
                        (REG_VIC_RAWSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_SoftInt (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_SoftInt'. */
void GH_VIC_set_SoftInt(U8 index, U32 data);
/*! \brief Reads the register 'VIC_SoftInt'. */
U32  GH_VIC_get_SoftInt(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_SoftInt(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftInt] <-- 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_SoftInt(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_SoftInt] --> 0x%08x\n",
                        (REG_VIC_SOFTINT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_SoftIntrClr (write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VIC_SoftIntrClr'. */
void GH_VIC_set_SoftIntrClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_SoftIntrClr'. */
U32  GH_VIC_getm_SoftIntrClr(U8 index);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VIC_set_SoftIntrClr(U8 index, U32 data)
{
    m_vic_softintrclr[index] = data;
    *(volatile U32 *)(REG_VIC_SOFTINTRCLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_SoftIntrClr] <-- 0x%08x\n",
                        (REG_VIC_SOFTINTRCLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_SoftIntrClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_SoftIntrClr] --> 0x%08x\n",
                        m_vic_softintrclr[index]);
    #endif
    return m_vic_softintrclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* register VIC_Protect (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIC_Protect'. */
void GH_VIC_set_Protect(U8 index, U32 data);
/*! \brief Reads the register 'VIC_Protect'. */
U32  GH_VIC_get_Protect(U8 index);
/*! \brief Writes the bit group 'Protect' of register 'VIC_Protect'. */
void GH_VIC_set_Protect_Protect(U8 index, U8 data);
/*! \brief Reads the bit group 'Protect' of register 'VIC_Protect'. */
U8   GH_VIC_get_Protect_Protect(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIC_set_Protect(U8 index, U32 data)
{
    *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_get_Protect(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
GH_INLINE void GH_VIC_set_Protect_Protect(U8 index, U8 data)
{
    GH_VIC_PROTECT_S d;
    d.all = *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000));
    d.bitc.protect = data;
    *(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)) = d.all;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_Protect_Protect] <-- 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIC_get_Protect_Protect(U8 index)
{
    GH_VIC_PROTECT_S tmp_value;
    U32 value = (*(volatile U32 *)(REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)));

    tmp_value.all = value;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_Protect_Protect] --> 0x%08x\n",
                        (REG_VIC_PROTECT + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return tmp_value.bitc.protect;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_IRQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIC_IRQSts'. */
U32  GH_VIC_get_IRQSts(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIC_get_IRQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_IRQSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_IRQSts] --> 0x%08x\n",
                        (REG_VIC_IRQSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_FIQSts (read)                                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIC_FIQSts'. */
U32  GH_VIC_get_FIQSts(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIC_get_FIQSts(U8 index)
{
    U32 value = (*(volatile U32 *)(REG_VIC_FIQSTS + index * FIO_MOFFSET(VIC,0x00001000)));

    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIC_get_FIQSts] --> 0x%08x\n",
                        (REG_VIC_FIQSTS + index * FIO_MOFFSET(VIC,0x00001000)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIC_EdgeClr (write)                                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'VIC_EdgeClr'. */
void GH_VIC_set_EdgeClr(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VIC_EdgeClr'. */
U32  GH_VIC_getm_EdgeClr(U8 index);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_VIC_set_EdgeClr(U8 index, U32 data)
{
    m_vic_edgeclr[index] = data;
    *(volatile U32 *)(REG_VIC_EDGECLR + index * FIO_MOFFSET(VIC,0x00001000)) = data;
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIC_set_EdgeClr] <-- 0x%08x\n",
                        (REG_VIC_EDGECLR + index * FIO_MOFFSET(VIC,0x00001000)),data,data);
    #endif
}
GH_INLINE U32  GH_VIC_getm_EdgeClr(U8 index)
{
    #if GH_VIC_ENABLE_DEBUG_PRINT
    GH_VIC_DEBUG_PRINT_FUNCTION( "[GH_VIC_getm_EdgeClr] --> 0x%08x\n",
                        m_vic_edgeclr[index]);
    #endif
    return m_vic_edgeclr[index];
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VIC_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VIC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

