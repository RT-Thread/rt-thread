/*!
*******************************************************************************
**
** \file      gh_vo_top.h
**
** \brief     TOP control Registers.
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
#ifndef _GH_VO_TOP_H
#define _GH_VO_TOP_H

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

#define GH_VO_TOP_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_TOP_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_TOP_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_TOP_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_TOP_RESET_VOUT                               FIO_ADDRESS(VO_TOP,0x90008A00) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_A                           FIO_ADDRESS(VO_TOP,0x90008A04) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_B                           FIO_ADDRESS(VO_TOP,0x90008A08) /* read/write */
#define REG_VO_TOP_ENABLE_CLOCK_OSDR                        FIO_ADDRESS(VO_TOP,0x90008A0C) /* read/write */
#define REG_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING              FIO_ADDRESS(VO_TOP,0x90008A10) /* read/write */
#define REG_VO_TOP_ENABLE_CONFIG_CLOCK_GATING               FIO_ADDRESS(VO_TOP,0x90008A14) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_TOP_RESET_VOUT */
    U32 all;
    struct {
        U32                             : 31;
        U32 reset                       : 1;
    } bitc;
} GH_VO_TOP_RESET_VOUT_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_A */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_A_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_B */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_B_S;

typedef union { /* VO_TOP_ENABLE_CLOCK_OSDR */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CLOCK_OSDR_S;

typedef union { /* VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING_S;

typedef union { /* VO_TOP_ENABLE_CONFIG_CLOCK_GATING */
    U32 all;
    struct {
        U32 enable                      : 1;
        U32                             : 31;
    } bitc;
} GH_VO_TOP_ENABLE_CONFIG_CLOCK_GATING_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_TOP_RESET_VOUT (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_RESET_VOUT'. */
void GH_VO_TOP_set_RESET_VOUT(U32 data);
/*! \brief Reads the register 'VO_TOP_RESET_VOUT'. */
U32  GH_VO_TOP_get_RESET_VOUT(void);
/*! \brief Writes the bit group 'reset' of register 'VO_TOP_RESET_VOUT'. */
void GH_VO_TOP_set_RESET_VOUT_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'VO_TOP_RESET_VOUT'. */
U8   GH_VO_TOP_get_RESET_VOUT_reset(void);

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_A (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_A'. */
void GH_VO_TOP_set_ENABLE_CLOCK_A(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_A'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_A(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_A'. */
void GH_VO_TOP_set_ENABLE_CLOCK_A_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_A'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_A_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_B (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_B'. */
void GH_VO_TOP_set_ENABLE_CLOCK_B(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_B'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_B(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_B'. */
void GH_VO_TOP_set_ENABLE_CLOCK_B_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_B'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_B_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CLOCK_OSDR (read/write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
U32  GH_VO_TOP_get_ENABLE_CLOCK_OSDR(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
void GH_VO_TOP_set_ENABLE_CLOCK_OSDR_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CLOCK_OSDR'. */
U8   GH_VO_TOP_get_ENABLE_CLOCK_OSDR_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING (read/write)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
U32  GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_SMEM_IF_CLOCK_GATING_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_SMEM_IF_CLOCK_GATING'. */
U8   GH_VO_TOP_get_ENABLE_SMEM_IF_CLOCK_GATING_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_TOP_ENABLE_CONFIG_CLOCK_GATING (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING(U32 data);
/*! \brief Reads the register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
U32  GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING(void);
/*! \brief Writes the bit group 'enable' of register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
void GH_VO_TOP_set_ENABLE_CONFIG_CLOCK_GATING_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_TOP_ENABLE_CONFIG_CLOCK_GATING'. */
U8   GH_VO_TOP_get_ENABLE_CONFIG_CLOCK_GATING_enable(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_TOP_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_top.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_TOP_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

