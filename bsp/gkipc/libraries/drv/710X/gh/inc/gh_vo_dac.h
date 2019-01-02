/*!
*******************************************************************************
**
** \file      gh_vo_dac.h
**
** \brief     VDAC Registers.
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
#ifndef _GH_VO_DAC_H
#define _GH_VO_DAC_H

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

#define GH_VO_DAC_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_DAC_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_DAC_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_DAC_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DAC_EN_IDAC_X                                FIO_ADDRESS(VO_DAC,0x90022680) /* read/write */
#define REG_VO_DAC_MODE_SD                                  FIO_ADDRESS(VO_DAC,0x90022681) /* read/write */
#define REG_VO_DAC_IDAC_IHALF_SD                            FIO_ADDRESS(VO_DAC,0x90022682) /* read/write */
#define REG_VO_DAC_GCR_LEVEL                                FIO_ADDRESS(VO_DAC,0x90022684) /* read/write */
#define REG_VO_DAC_IDA_IQUART_SD                            FIO_ADDRESS(VO_DAC,0x90022685) /* read/write */
#define REG_VO_DAC_GCR_IDAC_GAINX                           FIO_ADDRESS(VO_DAC,0x90022686) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DAC_EN_IDAC_X */
    U8 all;
    struct {
        U8 enable                       : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_EN_IDAC_X_S;

typedef union { /* VO_DAC_MODE_SD */
    U8 all;
    struct {
        U8 mode                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_MODE_SD_S;

typedef union { /* VO_DAC_IDAC_IHALF_SD */
    U8 all;
    struct {
        U8 half                         : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDAC_IHALF_SD_S;

typedef union { /* VO_DAC_GCR_LEVEL */
    U8 all;
    struct {
        U8 level                        : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DAC_GCR_LEVEL_S;

typedef union { /* VO_DAC_IDA_IQUART_SD */
    U8 all;
    struct {
        U8 quart                        : 1;
        U8                              : 7;
    } bitc;
} GH_VO_DAC_IDA_IQUART_SD_S;

typedef union { /* VO_DAC_GCR_IDAC_GAINX */
    U8 all;
    struct {
        U8 gain                         : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DAC_GCR_IDAC_GAINX_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_DAC_EN_IDAC_X (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_EN_IDAC_X'. */
void GH_VO_DAC_set_EN_IDAC_X(U8 data);
/*! \brief Reads the register 'VO_DAC_EN_IDAC_X'. */
U8   GH_VO_DAC_get_EN_IDAC_X(void);
/*! \brief Writes the bit group 'enable' of register 'VO_DAC_EN_IDAC_X'. */
void GH_VO_DAC_set_EN_IDAC_X_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_DAC_EN_IDAC_X'. */
U8   GH_VO_DAC_get_EN_IDAC_X_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_DAC_MODE_SD (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_MODE_SD'. */
void GH_VO_DAC_set_MODE_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_MODE_SD'. */
U8   GH_VO_DAC_get_MODE_SD(void);
/*! \brief Writes the bit group 'mode' of register 'VO_DAC_MODE_SD'. */
void GH_VO_DAC_set_MODE_SD_mode(U8 data);
/*! \brief Reads the bit group 'mode' of register 'VO_DAC_MODE_SD'. */
U8   GH_VO_DAC_get_MODE_SD_mode(void);

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDAC_IHALF_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_IDAC_IHALF_SD'. */
void GH_VO_DAC_set_IDAC_IHALF_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_IDAC_IHALF_SD'. */
U8   GH_VO_DAC_get_IDAC_IHALF_SD(void);
/*! \brief Writes the bit group 'half' of register 'VO_DAC_IDAC_IHALF_SD'. */
void GH_VO_DAC_set_IDAC_IHALF_SD_half(U8 data);
/*! \brief Reads the bit group 'half' of register 'VO_DAC_IDAC_IHALF_SD'. */
U8   GH_VO_DAC_get_IDAC_IHALF_SD_half(void);

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_LEVEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_GCR_LEVEL'. */
void GH_VO_DAC_set_GCR_LEVEL(U8 data);
/*! \brief Reads the register 'VO_DAC_GCR_LEVEL'. */
U8   GH_VO_DAC_get_GCR_LEVEL(void);
/*! \brief Writes the bit group 'level' of register 'VO_DAC_GCR_LEVEL'. */
void GH_VO_DAC_set_GCR_LEVEL_level(U8 data);
/*! \brief Reads the bit group 'level' of register 'VO_DAC_GCR_LEVEL'. */
U8   GH_VO_DAC_get_GCR_LEVEL_level(void);

/*----------------------------------------------------------------------------*/
/* register VO_DAC_IDA_IQUART_SD (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_IDA_IQUART_SD'. */
void GH_VO_DAC_set_IDA_IQUART_SD(U8 data);
/*! \brief Reads the register 'VO_DAC_IDA_IQUART_SD'. */
U8   GH_VO_DAC_get_IDA_IQUART_SD(void);
/*! \brief Writes the bit group 'quart' of register 'VO_DAC_IDA_IQUART_SD'. */
void GH_VO_DAC_set_IDA_IQUART_SD_quart(U8 data);
/*! \brief Reads the bit group 'quart' of register 'VO_DAC_IDA_IQUART_SD'. */
U8   GH_VO_DAC_get_IDA_IQUART_SD_quart(void);

/*----------------------------------------------------------------------------*/
/* register VO_DAC_GCR_IDAC_GAINX (read/write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DAC_GCR_IDAC_GAINX'. */
void GH_VO_DAC_set_GCR_IDAC_GAINX(U8 data);
/*! \brief Reads the register 'VO_DAC_GCR_IDAC_GAINX'. */
U8   GH_VO_DAC_get_GCR_IDAC_GAINX(void);
/*! \brief Writes the bit group 'gain' of register 'VO_DAC_GCR_IDAC_GAINX'. */
void GH_VO_DAC_set_GCR_IDAC_GAINX_gain(U8 data);
/*! \brief Reads the bit group 'gain' of register 'VO_DAC_GCR_IDAC_GAINX'. */
U8   GH_VO_DAC_get_GCR_IDAC_GAINX_gain(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DAC_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_dac.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DAC_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

