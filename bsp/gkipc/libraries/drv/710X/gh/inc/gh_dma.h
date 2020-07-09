/*!
*******************************************************************************
**
** \file      gh_dma.h
**
** \brief     DMA Engine Subsystem.
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
#ifndef _GH_DMA_H
#define _GH_DMA_H

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

#define GH_DMA_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_DMA_DEBUG_PRINT_FUNCTION printk
#else
#define GH_DMA_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_DMA_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_DMA_CONTROL                                     FIO_ADDRESS(DMA,0x90005300) /* read/write */
#define REG_DMA_SOURCE_ADDRESS                              FIO_ADDRESS(DMA,0x90005304) /* read/write */
#define REG_DMA_DESTINATION_ADDRESS                         FIO_ADDRESS(DMA,0x90005308) /* read/write */
#define REG_DMA_STATUS                                      FIO_ADDRESS(DMA,0x9000530C) /* read/write */
#define REG_DMA_DESCRIPTOR_ADDRESS                          FIO_ADDRESS(DMA,0x90005380) /* read/write */
#define REG_DMA_IR                                          FIO_ADDRESS(DMA,0x900053F0) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* DMA_Control */
    U32 all;
    struct {
        U32 count                       : 22;
        U32 ts                          : 2;
        U32 blk                         : 3;
        U32 ni                          : 1;
        U32 rm                          : 1;
        U32 wm                          : 1;
        U32 d                           : 1;
        U32 en                          : 1;
    } bitc;
} GH_DMA_CONTROL_S;

typedef union { /* DMA_Status */
    U32 all;
    struct {
        U32 count                       : 22;
        U32 dn                          : 1;
        U32 ae                          : 1;
        U32 rwe                         : 1;
        U32 be                          : 1;
        U32 me                          : 1;
        U32 od                          : 1;
        U32 dd                          : 1;
        U32 da                          : 1;
        U32 oe                          : 1;
        U32 dm                          : 1;
    } bitc;
} GH_DMA_STATUS_S;

typedef union { /* DMA_IR */
    U32 all;
    struct {
        U32 i0                          : 1;
        U32 i1                          : 1;
        U32 i2                          : 1;
        U32 i3                          : 1;
        U32                             : 28;
    } bitc;
} GH_DMA_IR_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register DMA_Control (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DMA_Control'. */
void GH_DMA_set_Control(U8 index, U32 data);
/*! \brief Reads the register 'DMA_Control'. */
U32  GH_DMA_get_Control(U8 index);
/*! \brief Writes the bit group 'count' of register 'DMA_Control'. */
void GH_DMA_set_Control_count(U8 index, U32 data);
/*! \brief Reads the bit group 'count' of register 'DMA_Control'. */
U32  GH_DMA_get_Control_count(U8 index);
/*! \brief Writes the bit group 'ts' of register 'DMA_Control'. */
void GH_DMA_set_Control_ts(U8 index, U8 data);
/*! \brief Reads the bit group 'ts' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_ts(U8 index);
/*! \brief Writes the bit group 'blk' of register 'DMA_Control'. */
void GH_DMA_set_Control_blk(U8 index, U8 data);
/*! \brief Reads the bit group 'blk' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_blk(U8 index);
/*! \brief Writes the bit group 'ni' of register 'DMA_Control'. */
void GH_DMA_set_Control_ni(U8 index, U8 data);
/*! \brief Reads the bit group 'ni' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_ni(U8 index);
/*! \brief Writes the bit group 'rm' of register 'DMA_Control'. */
void GH_DMA_set_Control_rm(U8 index, U8 data);
/*! \brief Reads the bit group 'rm' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_rm(U8 index);
/*! \brief Writes the bit group 'wm' of register 'DMA_Control'. */
void GH_DMA_set_Control_wm(U8 index, U8 data);
/*! \brief Reads the bit group 'wm' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_wm(U8 index);
/*! \brief Writes the bit group 'd' of register 'DMA_Control'. */
void GH_DMA_set_Control_d(U8 index, U8 data);
/*! \brief Reads the bit group 'd' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_d(U8 index);
/*! \brief Writes the bit group 'en' of register 'DMA_Control'. */
void GH_DMA_set_Control_en(U8 index, U8 data);
/*! \brief Reads the bit group 'en' of register 'DMA_Control'. */
U8   GH_DMA_get_Control_en(U8 index);

/*----------------------------------------------------------------------------*/
/* register DMA_Source_Address (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DMA_Source_Address'. */
void GH_DMA_set_Source_Address(U8 index, U32 data);
/*! \brief Reads the register 'DMA_Source_Address'. */
U32  GH_DMA_get_Source_Address(U8 index);

/*----------------------------------------------------------------------------*/
/* register DMA_Destination_Address (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DMA_Destination_Address'. */
void GH_DMA_set_Destination_Address(U8 index, U32 data);
/*! \brief Reads the register 'DMA_Destination_Address'. */
U32  GH_DMA_get_Destination_Address(U8 index);

/*----------------------------------------------------------------------------*/
/* register DMA_Status (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DMA_Status'. */
void GH_DMA_set_Status(U8 index, U32 data);
/*! \brief Reads the register 'DMA_Status'. */
U32  GH_DMA_get_Status(U8 index);
/*! \brief Writes the bit group 'count' of register 'DMA_Status'. */
void GH_DMA_set_Status_count(U8 index, U32 data);
/*! \brief Reads the bit group 'count' of register 'DMA_Status'. */
U32  GH_DMA_get_Status_count(U8 index);
/*! \brief Writes the bit group 'dn' of register 'DMA_Status'. */
void GH_DMA_set_Status_dn(U8 index, U8 data);
/*! \brief Reads the bit group 'dn' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_dn(U8 index);
/*! \brief Writes the bit group 'ae' of register 'DMA_Status'. */
void GH_DMA_set_Status_ae(U8 index, U8 data);
/*! \brief Reads the bit group 'ae' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_ae(U8 index);
/*! \brief Writes the bit group 'rwe' of register 'DMA_Status'. */
void GH_DMA_set_Status_rwe(U8 index, U8 data);
/*! \brief Reads the bit group 'rwe' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_rwe(U8 index);
/*! \brief Writes the bit group 'be' of register 'DMA_Status'. */
void GH_DMA_set_Status_be(U8 index, U8 data);
/*! \brief Reads the bit group 'be' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_be(U8 index);
/*! \brief Writes the bit group 'me' of register 'DMA_Status'. */
void GH_DMA_set_Status_me(U8 index, U8 data);
/*! \brief Reads the bit group 'me' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_me(U8 index);
/*! \brief Writes the bit group 'od' of register 'DMA_Status'. */
void GH_DMA_set_Status_od(U8 index, U8 data);
/*! \brief Reads the bit group 'od' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_od(U8 index);
/*! \brief Writes the bit group 'dd' of register 'DMA_Status'. */
void GH_DMA_set_Status_dd(U8 index, U8 data);
/*! \brief Reads the bit group 'dd' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_dd(U8 index);
/*! \brief Writes the bit group 'da' of register 'DMA_Status'. */
void GH_DMA_set_Status_da(U8 index, U8 data);
/*! \brief Reads the bit group 'da' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_da(U8 index);
/*! \brief Writes the bit group 'oe' of register 'DMA_Status'. */
void GH_DMA_set_Status_oe(U8 index, U8 data);
/*! \brief Reads the bit group 'oe' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_oe(U8 index);
/*! \brief Writes the bit group 'dm' of register 'DMA_Status'. */
void GH_DMA_set_Status_dm(U8 index, U8 data);
/*! \brief Reads the bit group 'dm' of register 'DMA_Status'. */
U8   GH_DMA_get_Status_dm(U8 index);

/*----------------------------------------------------------------------------*/
/* register DMA_Descriptor_Address (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'DMA_Descriptor_Address'. */
void GH_DMA_set_Descriptor_Address(U8 index, U32 data);
/*! \brief Reads the register 'DMA_Descriptor_Address'. */
U32  GH_DMA_get_Descriptor_Address(U8 index);

/*----------------------------------------------------------------------------*/
/* register DMA_IR (read)                                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'DMA_IR'. */
U32  GH_DMA_get_IR(void);
/*! \brief Reads the bit group 'i0' of register 'DMA_IR'. */
U8   GH_DMA_get_IR_i0(void);
/*! \brief Reads the bit group 'i1' of register 'DMA_IR'. */
U8   GH_DMA_get_IR_i1(void);
/*! \brief Reads the bit group 'i2' of register 'DMA_IR'. */
U8   GH_DMA_get_IR_i2(void);
/*! \brief Reads the bit group 'i3' of register 'DMA_IR'. */
U8   GH_DMA_get_IR_i3(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_DMA_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_dma.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_DMA_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

