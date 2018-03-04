/*!
*******************************************************************************
**
** \file      gh_spi1.h
**
** \brief     Master interface and supports up to 1 external SPI slave devices. SSI2.
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
#ifndef _GH_SPI1_H
#define _GH_SPI1_H

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

#define GH_SPI1_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_SPI1_DEBUG_PRINT_FUNCTION printk
#else
#define GH_SPI1_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_SPI1_ENABLE_DEBUG_PRINT
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
#define REG_SPI1_CTRLR0                                     FIO_ADDRESS(SPI1,0xA0001000) /* read/write */
#define REG_SPI1_CTRLR1                                     FIO_ADDRESS(SPI1,0xA0001004) /* read/write */
#define REG_SPI1_SSIENR                                     FIO_ADDRESS(SPI1,0xA0001008) /* read/write */
#define REG_SPI1_SER                                        FIO_ADDRESS(SPI1,0xA0001010) /* read/write */
#define REG_SPI1_BAUDR                                      FIO_ADDRESS(SPI1,0xA0001014) /* read/write */
#define REG_SPI1_TXFTLR                                     FIO_ADDRESS(SPI1,0xA0001018) /* read/write */
#define REG_SPI1_RXFTLR                                     FIO_ADDRESS(SPI1,0xA000101C) /* read/write */
#define REG_SPI1_TXFLR                                      FIO_ADDRESS(SPI1,0xA0001020) /* read/write */
#define REG_SPI1_RXFLR                                      FIO_ADDRESS(SPI1,0xA0001024) /* read/write */
#define REG_SPI1_SR                                         FIO_ADDRESS(SPI1,0xA0001028) /* read */
#define REG_SPI1_IMR                                        FIO_ADDRESS(SPI1,0xA000102C) /* read/write */
#define REG_SPI1_ISR                                        FIO_ADDRESS(SPI1,0xA0001030) /* read */
#define REG_SPI1_RISR                                       FIO_ADDRESS(SPI1,0xA0001034) /* read */
#define REG_SPI1_TXOICR                                     FIO_ADDRESS(SPI1,0xA0001038) /* read */
#define REG_SPI1_RXOICR                                     FIO_ADDRESS(SPI1,0xA000103C) /* read */
#define REG_SPI1_RXUICR                                     FIO_ADDRESS(SPI1,0xA0001040) /* read */
#define REG_SPI1_MSTICR                                     FIO_ADDRESS(SPI1,0xA0001044) /* read */
#define REG_SPI1_ICR                                        FIO_ADDRESS(SPI1,0xA0001048) /* read */
#define REG_SPI1_IDR                                        FIO_ADDRESS(SPI1,0xA0001058) /* read */
#define REG_SPI1_DR                                         FIO_ADDRESS(SPI1,0xA0001060) /* read */
#define REG_SPI1_DW                                         FIO_ADDRESS(SPI1,0xA0001060) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SPI1_CTRLR0 */
    U32 all;
    struct {
        U32 dfs                         : 4;
        U32 frf                         : 2;
        U32 scph                        : 1;
        U32 scpol                       : 1;
        U32 tmod                        : 2;
        U32 slv_oe                      : 1;
        U32 srl                         : 1;
        U32 cfs                         : 4;
        U32                             : 16;
    } bitc;
} GH_SPI1_CTRLR0_S;

typedef union { /* SPI1_CTRLR1 */
    U32 all;
    struct {
        U32 ndf                         : 16;
        U32                             : 16;
    } bitc;
} GH_SPI1_CTRLR1_S;

typedef union { /* SPI1_SSIENR */
    U32 all;
    struct {
        U32 ssi_enb                     : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_SSIENR_S;

typedef union { /* SPI1_SER */
    U32 all;
    struct {
        U32 ser_l                       : 2;
        U32                             : 2;
        U32 ser_h                       : 4;
        U32                             : 24;
    } bitc;
} GH_SPI1_SER_S;

typedef union { /* SPI1_BAUDR */
    U32 all;
    struct {
        U32 sckdv                       : 16;
        U32                             : 16;
    } bitc;
} GH_SPI1_BAUDR_S;

typedef union { /* SPI1_TXFTLR */
    U32 all;
    struct {
        U32 tft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI1_TXFTLR_S;

typedef union { /* SPI1_RXFTLR */
    U32 all;
    struct {
        U32 rft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI1_RXFTLR_S;

typedef union { /* SPI1_TXFLR */
    U32 all;
    struct {
        U32 txtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI1_TXFLR_S;

typedef union { /* SPI1_RXFLR */
    U32 all;
    struct {
        U32 rxtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI1_RXFLR_S;

typedef union { /* SPI1_SR */
    U32 all;
    struct {
        U32 busy                        : 1;
        U32 tfnf                        : 1;
        U32 tfe                         : 1;
        U32 rfne                        : 1;
        U32 rff                         : 1;
        U32 txe                         : 1;
        U32 dcol                        : 1;
        U32                             : 25;
    } bitc;
} GH_SPI1_SR_S;

typedef union { /* SPI1_IMR */
    U32 all;
    struct {
        U32 txeim                       : 1;
        U32 txoim                       : 1;
        U32 rxuim                       : 1;
        U32 rxoim                       : 1;
        U32 rxfim                       : 1;
        U32 mstim                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI1_IMR_S;

typedef union { /* SPI1_ISR */
    U32 all;
    struct {
        U32 txeis                       : 1;
        U32 txois                       : 1;
        U32 rxuis                       : 1;
        U32 rxois                       : 1;
        U32 rxfis                       : 1;
        U32 mstis                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI1_ISR_S;

typedef union { /* SPI1_RISR */
    U32 all;
    struct {
        U32 txeir                       : 1;
        U32 txoir                       : 1;
        U32 rxuir                       : 1;
        U32 rxoir                       : 1;
        U32 rxfir                       : 1;
        U32 mstir                       : 1;
        U32                             : 26;
    } bitc;
} GH_SPI1_RISR_S;

typedef union { /* SPI1_TXOICR */
    U32 all;
    struct {
        U32 txoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_TXOICR_S;

typedef union { /* SPI1_RXOICR */
    U32 all;
    struct {
        U32 rxoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_RXOICR_S;

typedef union { /* SPI1_RXUICR */
    U32 all;
    struct {
        U32 rxuicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_RXUICR_S;

typedef union { /* SPI1_MSTICR */
    U32 all;
    struct {
        U32 msticr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_MSTICR_S;

typedef union { /* SPI1_ICR */
    U32 all;
    struct {
        U32 icr                         : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_ICR_S;

typedef union { /* SPI1_IDR */
    U32 all;
    struct {
        U32 id                          : 1;
        U32                             : 31;
    } bitc;
} GH_SPI1_IDR_S;

typedef union { /* SPI1_DR */
    U32 all;
    struct {
        U32 dr                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI1_DR_S;

typedef union { /* SPI1_DW */
    U32 all;
    struct {
        U32 dw                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI1_DW_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_SPI1_DW_S                            m_spi1_dw;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SPI1_CTRLR0 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0(U32 data);
/*! \brief Reads the register 'SPI1_CTRLR0'. */
U32  GH_SPI1_get_CTRLR0(void);
/*! \brief Writes the bit group 'DFS' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_DFS(U8 data);
/*! \brief Reads the bit group 'DFS' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_DFS(void);
/*! \brief Writes the bit group 'FRF' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_FRF(U8 data);
/*! \brief Reads the bit group 'FRF' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_FRF(void);
/*! \brief Writes the bit group 'SCPH' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_SCPH(U8 data);
/*! \brief Reads the bit group 'SCPH' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_SCPH(void);
/*! \brief Writes the bit group 'SCPOL' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_SCPOL(U8 data);
/*! \brief Reads the bit group 'SCPOL' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_SCPOL(void);
/*! \brief Writes the bit group 'TMOD' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_TMOD(U8 data);
/*! \brief Reads the bit group 'TMOD' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_TMOD(void);
/*! \brief Writes the bit group 'SLV_OE' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_SLV_OE(U8 data);
/*! \brief Reads the bit group 'SLV_OE' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_SLV_OE(void);
/*! \brief Writes the bit group 'SRL' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_SRL(U8 data);
/*! \brief Reads the bit group 'SRL' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_SRL(void);
/*! \brief Writes the bit group 'CFS' of register 'SPI1_CTRLR0'. */
void GH_SPI1_set_CTRLR0_CFS(U8 data);
/*! \brief Reads the bit group 'CFS' of register 'SPI1_CTRLR0'. */
U8   GH_SPI1_get_CTRLR0_CFS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_CTRLR0(U32 data)
{
    *(volatile U32 *)REG_SPI1_CTRLR0 = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_CTRLR0(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_CTRLR0_DFS(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.dfs = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_DFS] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_DFS(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_DFS] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.dfs;
}
GH_INLINE void GH_SPI1_set_CTRLR0_FRF(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.frf = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_FRF] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_FRF(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_FRF] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.frf;
}
GH_INLINE void GH_SPI1_set_CTRLR0_SCPH(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.scph = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SCPH] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_SCPH(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SCPH] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.scph;
}
GH_INLINE void GH_SPI1_set_CTRLR0_SCPOL(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.scpol = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SCPOL] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_SCPOL(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SCPOL] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.scpol;
}
GH_INLINE void GH_SPI1_set_CTRLR0_TMOD(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.tmod = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_TMOD] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_TMOD(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_TMOD] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.tmod;
}
GH_INLINE void GH_SPI1_set_CTRLR0_SLV_OE(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.slv_oe = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SLV_OE] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_SLV_OE(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SLV_OE] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.slv_oe;
}
GH_INLINE void GH_SPI1_set_CTRLR0_SRL(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.srl = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_SRL] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_SRL(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_SRL] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.srl;
}
GH_INLINE void GH_SPI1_set_CTRLR0_CFS(U8 data)
{
    GH_SPI1_CTRLR0_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR0;
    d.bitc.cfs = data;
    *(volatile U32 *)REG_SPI1_CTRLR0 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR0_CFS] <-- 0x%08x\n",
                        REG_SPI1_CTRLR0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_CTRLR0_CFS(void)
{
    GH_SPI1_CTRLR0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR0);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR0_CFS] --> 0x%08x\n",
                        REG_SPI1_CTRLR0,value);
    #endif
    return tmp_value.bitc.cfs;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_CTRLR1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_CTRLR1'. */
void GH_SPI1_set_CTRLR1(U32 data);
/*! \brief Reads the register 'SPI1_CTRLR1'. */
U32  GH_SPI1_get_CTRLR1(void);
/*! \brief Writes the bit group 'NDF' of register 'SPI1_CTRLR1'. */
void GH_SPI1_set_CTRLR1_NDF(U16 data);
/*! \brief Reads the bit group 'NDF' of register 'SPI1_CTRLR1'. */
U16  GH_SPI1_get_CTRLR1_NDF(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_CTRLR1(U32 data)
{
    *(volatile U32 *)REG_SPI1_CTRLR1 = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR1] <-- 0x%08x\n",
                        REG_SPI1_CTRLR1,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_CTRLR1(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR1);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR1] --> 0x%08x\n",
                        REG_SPI1_CTRLR1,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_CTRLR1_NDF(U16 data)
{
    GH_SPI1_CTRLR1_S d;
    d.all = *(volatile U32 *)REG_SPI1_CTRLR1;
    d.bitc.ndf = data;
    *(volatile U32 *)REG_SPI1_CTRLR1 = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_CTRLR1_NDF] <-- 0x%08x\n",
                        REG_SPI1_CTRLR1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SPI1_get_CTRLR1_NDF(void)
{
    GH_SPI1_CTRLR1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_CTRLR1);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_CTRLR1_NDF] --> 0x%08x\n",
                        REG_SPI1_CTRLR1,value);
    #endif
    return tmp_value.bitc.ndf;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SSIENR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_SSIENR'. */
void GH_SPI1_set_SSIENR(U32 data);
/*! \brief Reads the register 'SPI1_SSIENR'. */
U32  GH_SPI1_get_SSIENR(void);
/*! \brief Writes the bit group 'ssi_enb' of register 'SPI1_SSIENR'. */
void GH_SPI1_set_SSIENR_ssi_enb(U8 data);
/*! \brief Reads the bit group 'ssi_enb' of register 'SPI1_SSIENR'. */
U8   GH_SPI1_get_SSIENR_ssi_enb(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_SSIENR(U32 data)
{
    *(volatile U32 *)REG_SPI1_SSIENR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SSIENR] <-- 0x%08x\n",
                        REG_SPI1_SSIENR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_SSIENR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SSIENR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SSIENR] --> 0x%08x\n",
                        REG_SPI1_SSIENR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_SSIENR_ssi_enb(U8 data)
{
    GH_SPI1_SSIENR_S d;
    d.all = *(volatile U32 *)REG_SPI1_SSIENR;
    d.bitc.ssi_enb = data;
    *(volatile U32 *)REG_SPI1_SSIENR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SSIENR_ssi_enb] <-- 0x%08x\n",
                        REG_SPI1_SSIENR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_SSIENR_ssi_enb(void)
{
    GH_SPI1_SSIENR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SSIENR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SSIENR_ssi_enb] --> 0x%08x\n",
                        REG_SPI1_SSIENR,value);
    #endif
    return tmp_value.bitc.ssi_enb;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SER (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_SER'. */
void GH_SPI1_set_SER(U32 data);
/*! \brief Reads the register 'SPI1_SER'. */
U32  GH_SPI1_get_SER(void);
/*! \brief Writes the bit group 'SER_L' of register 'SPI1_SER'. */
void GH_SPI1_set_SER_SER_L(U8 data);
/*! \brief Reads the bit group 'SER_L' of register 'SPI1_SER'. */
U8   GH_SPI1_get_SER_SER_L(void);
/*! \brief Writes the bit group 'SER_H' of register 'SPI1_SER'. */
void GH_SPI1_set_SER_SER_H(U8 data);
/*! \brief Reads the bit group 'SER_H' of register 'SPI1_SER'. */
U8   GH_SPI1_get_SER_SER_H(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_SER(U32 data)
{
    *(volatile U32 *)REG_SPI1_SER = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER] <-- 0x%08x\n",
                        REG_SPI1_SER,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_SER(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_SER_SER_L(U8 data)
{
    GH_SPI1_SER_S d;
    d.all = *(volatile U32 *)REG_SPI1_SER;
    d.bitc.ser_l = data;
    *(volatile U32 *)REG_SPI1_SER = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER_SER_L] <-- 0x%08x\n",
                        REG_SPI1_SER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_SER_SER_L(void)
{
    GH_SPI1_SER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER_SER_L] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return tmp_value.bitc.ser_l;
}
GH_INLINE void GH_SPI1_set_SER_SER_H(U8 data)
{
    GH_SPI1_SER_S d;
    d.all = *(volatile U32 *)REG_SPI1_SER;
    d.bitc.ser_h = data;
    *(volatile U32 *)REG_SPI1_SER = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_SER_SER_H] <-- 0x%08x\n",
                        REG_SPI1_SER,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_SER_SER_H(void)
{
    GH_SPI1_SER_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SER);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SER_SER_H] --> 0x%08x\n",
                        REG_SPI1_SER,value);
    #endif
    return tmp_value.bitc.ser_h;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_BAUDR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_BAUDR'. */
void GH_SPI1_set_BAUDR(U32 data);
/*! \brief Reads the register 'SPI1_BAUDR'. */
U32  GH_SPI1_get_BAUDR(void);
/*! \brief Writes the bit group 'SCKDV' of register 'SPI1_BAUDR'. */
void GH_SPI1_set_BAUDR_SCKDV(U16 data);
/*! \brief Reads the bit group 'SCKDV' of register 'SPI1_BAUDR'. */
U16  GH_SPI1_get_BAUDR_SCKDV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_BAUDR(U32 data)
{
    *(volatile U32 *)REG_SPI1_BAUDR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_BAUDR] <-- 0x%08x\n",
                        REG_SPI1_BAUDR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_BAUDR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_BAUDR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_BAUDR] --> 0x%08x\n",
                        REG_SPI1_BAUDR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_BAUDR_SCKDV(U16 data)
{
    GH_SPI1_BAUDR_S d;
    d.all = *(volatile U32 *)REG_SPI1_BAUDR;
    d.bitc.sckdv = data;
    *(volatile U32 *)REG_SPI1_BAUDR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_BAUDR_SCKDV] <-- 0x%08x\n",
                        REG_SPI1_BAUDR,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_SPI1_get_BAUDR_SCKDV(void)
{
    GH_SPI1_BAUDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_BAUDR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_BAUDR_SCKDV] --> 0x%08x\n",
                        REG_SPI1_BAUDR,value);
    #endif
    return tmp_value.bitc.sckdv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_TXFTLR'. */
void GH_SPI1_set_TXFTLR(U32 data);
/*! \brief Reads the register 'SPI1_TXFTLR'. */
U32  GH_SPI1_get_TXFTLR(void);
/*! \brief Writes the bit group 'TFT' of register 'SPI1_TXFTLR'. */
void GH_SPI1_set_TXFTLR_TFT(U8 data);
/*! \brief Reads the bit group 'TFT' of register 'SPI1_TXFTLR'. */
U8   GH_SPI1_get_TXFTLR_TFT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_TXFTLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_TXFTLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFTLR] <-- 0x%08x\n",
                        REG_SPI1_TXFTLR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_TXFTLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXFTLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFTLR] --> 0x%08x\n",
                        REG_SPI1_TXFTLR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_TXFTLR_TFT(U8 data)
{
    GH_SPI1_TXFTLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_TXFTLR;
    d.bitc.tft = data;
    *(volatile U32 *)REG_SPI1_TXFTLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFTLR_TFT] <-- 0x%08x\n",
                        REG_SPI1_TXFTLR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_TXFTLR_TFT(void)
{
    GH_SPI1_TXFTLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXFTLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFTLR_TFT] --> 0x%08x\n",
                        REG_SPI1_TXFTLR,value);
    #endif
    return tmp_value.bitc.tft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_RXFTLR'. */
void GH_SPI1_set_RXFTLR(U32 data);
/*! \brief Reads the register 'SPI1_RXFTLR'. */
U32  GH_SPI1_get_RXFTLR(void);
/*! \brief Writes the bit group 'RFT' of register 'SPI1_RXFTLR'. */
void GH_SPI1_set_RXFTLR_RFT(U8 data);
/*! \brief Reads the bit group 'RFT' of register 'SPI1_RXFTLR'. */
U8   GH_SPI1_get_RXFTLR_RFT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_RXFTLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_RXFTLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFTLR] <-- 0x%08x\n",
                        REG_SPI1_RXFTLR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_RXFTLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXFTLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFTLR] --> 0x%08x\n",
                        REG_SPI1_RXFTLR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_RXFTLR_RFT(U8 data)
{
    GH_SPI1_RXFTLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_RXFTLR;
    d.bitc.rft = data;
    *(volatile U32 *)REG_SPI1_RXFTLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFTLR_RFT] <-- 0x%08x\n",
                        REG_SPI1_RXFTLR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_RXFTLR_RFT(void)
{
    GH_SPI1_RXFTLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXFTLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFTLR_RFT] --> 0x%08x\n",
                        REG_SPI1_RXFTLR,value);
    #endif
    return tmp_value.bitc.rft;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_TXFLR'. */
void GH_SPI1_set_TXFLR(U32 data);
/*! \brief Reads the register 'SPI1_TXFLR'. */
U32  GH_SPI1_get_TXFLR(void);
/*! \brief Writes the bit group 'TXTFL' of register 'SPI1_TXFLR'. */
void GH_SPI1_set_TXFLR_TXTFL(U8 data);
/*! \brief Reads the bit group 'TXTFL' of register 'SPI1_TXFLR'. */
U8   GH_SPI1_get_TXFLR_TXTFL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_TXFLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_TXFLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFLR] <-- 0x%08x\n",
                        REG_SPI1_TXFLR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_TXFLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXFLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFLR] --> 0x%08x\n",
                        REG_SPI1_TXFLR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_TXFLR_TXTFL(U8 data)
{
    GH_SPI1_TXFLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_TXFLR;
    d.bitc.txtfl = data;
    *(volatile U32 *)REG_SPI1_TXFLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_TXFLR_TXTFL] <-- 0x%08x\n",
                        REG_SPI1_TXFLR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_TXFLR_TXTFL(void)
{
    GH_SPI1_TXFLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXFLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXFLR_TXTFL] --> 0x%08x\n",
                        REG_SPI1_TXFLR,value);
    #endif
    return tmp_value.bitc.txtfl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_RXFLR'. */
void GH_SPI1_set_RXFLR(U32 data);
/*! \brief Reads the register 'SPI1_RXFLR'. */
U32  GH_SPI1_get_RXFLR(void);
/*! \brief Writes the bit group 'RXTFL' of register 'SPI1_RXFLR'. */
void GH_SPI1_set_RXFLR_RXTFL(U8 data);
/*! \brief Reads the bit group 'RXTFL' of register 'SPI1_RXFLR'. */
U8   GH_SPI1_get_RXFLR_RXTFL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_RXFLR(U32 data)
{
    *(volatile U32 *)REG_SPI1_RXFLR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFLR] <-- 0x%08x\n",
                        REG_SPI1_RXFLR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_RXFLR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXFLR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFLR] --> 0x%08x\n",
                        REG_SPI1_RXFLR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_RXFLR_RXTFL(U8 data)
{
    GH_SPI1_RXFLR_S d;
    d.all = *(volatile U32 *)REG_SPI1_RXFLR;
    d.bitc.rxtfl = data;
    *(volatile U32 *)REG_SPI1_RXFLR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_RXFLR_RXTFL] <-- 0x%08x\n",
                        REG_SPI1_RXFLR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_RXFLR_RXTFL(void)
{
    GH_SPI1_RXFLR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXFLR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXFLR_RXTFL] --> 0x%08x\n",
                        REG_SPI1_RXFLR,value);
    #endif
    return tmp_value.bitc.rxtfl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_SR (read)                                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_SR'. */
U32  GH_SPI1_get_SR(void);
/*! \brief Reads the bit group 'BUSY' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_BUSY(void);
/*! \brief Reads the bit group 'TFNF' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_TFNF(void);
/*! \brief Reads the bit group 'TFE' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_TFE(void);
/*! \brief Reads the bit group 'RFNE' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_RFNE(void);
/*! \brief Reads the bit group 'RFF' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_RFF(void);
/*! \brief Reads the bit group 'TXE' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_TXE(void);
/*! \brief Reads the bit group 'DCOL' of register 'SPI1_SR'. */
U8   GH_SPI1_get_SR_DCOL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_SR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_SR_BUSY(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_BUSY] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.busy;
}
GH_INLINE U8   GH_SPI1_get_SR_TFNF(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TFNF] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.tfnf;
}
GH_INLINE U8   GH_SPI1_get_SR_TFE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TFE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.tfe;
}
GH_INLINE U8   GH_SPI1_get_SR_RFNE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_RFNE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.rfne;
}
GH_INLINE U8   GH_SPI1_get_SR_RFF(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_RFF] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.rff;
}
GH_INLINE U8   GH_SPI1_get_SR_TXE(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_TXE] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.txe;
}
GH_INLINE U8   GH_SPI1_get_SR_DCOL(void)
{
    GH_SPI1_SR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_SR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_SR_DCOL] --> 0x%08x\n",
                        REG_SPI1_SR,value);
    #endif
    return tmp_value.bitc.dcol;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_IMR (read/write)                                             */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'SPI1_IMR'. */
void GH_SPI1_set_IMR(U32 data);
/*! \brief Reads the register 'SPI1_IMR'. */
U32  GH_SPI1_get_IMR(void);
/*! \brief Writes the bit group 'TXEIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_TXEIM(U8 data);
/*! \brief Reads the bit group 'TXEIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_TXEIM(void);
/*! \brief Writes the bit group 'TXOIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_TXOIM(U8 data);
/*! \brief Reads the bit group 'TXOIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_TXOIM(void);
/*! \brief Writes the bit group 'RXUIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_RXUIM(U8 data);
/*! \brief Reads the bit group 'RXUIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_RXUIM(void);
/*! \brief Writes the bit group 'RXOIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_RXOIM(U8 data);
/*! \brief Reads the bit group 'RXOIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_RXOIM(void);
/*! \brief Writes the bit group 'RXFIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_RXFIM(U8 data);
/*! \brief Reads the bit group 'RXFIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_RXFIM(void);
/*! \brief Writes the bit group 'MSTIM' of register 'SPI1_IMR'. */
void GH_SPI1_set_IMR_MSTIM(U8 data);
/*! \brief Reads the bit group 'MSTIM' of register 'SPI1_IMR'. */
U8   GH_SPI1_get_IMR_MSTIM(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_SPI1_set_IMR(U32 data)
{
    *(volatile U32 *)REG_SPI1_IMR = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR] <-- 0x%08x\n",
                        REG_SPI1_IMR,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_get_IMR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return value;
}
GH_INLINE void GH_SPI1_set_IMR_TXEIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.txeim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_TXEIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_TXEIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_TXEIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.txeim;
}
GH_INLINE void GH_SPI1_set_IMR_TXOIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.txoim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_TXOIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_TXOIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_TXOIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.txoim;
}
GH_INLINE void GH_SPI1_set_IMR_RXUIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxuim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXUIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_RXUIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXUIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxuim;
}
GH_INLINE void GH_SPI1_set_IMR_RXOIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxoim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXOIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_RXOIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXOIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxoim;
}
GH_INLINE void GH_SPI1_set_IMR_RXFIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.rxfim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_RXFIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_RXFIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_RXFIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.rxfim;
}
GH_INLINE void GH_SPI1_set_IMR_MSTIM(U8 data)
{
    GH_SPI1_IMR_S d;
    d.all = *(volatile U32 *)REG_SPI1_IMR;
    d.bitc.mstim = data;
    *(volatile U32 *)REG_SPI1_IMR = d.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_IMR_MSTIM] <-- 0x%08x\n",
                        REG_SPI1_IMR,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_SPI1_get_IMR_MSTIM(void)
{
    GH_SPI1_IMR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IMR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IMR_MSTIM] --> 0x%08x\n",
                        REG_SPI1_IMR,value);
    #endif
    return tmp_value.bitc.mstim;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_ISR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_ISR'. */
U32  GH_SPI1_get_ISR(void);
/*! \brief Reads the bit group 'TXEIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_TXEIS(void);
/*! \brief Reads the bit group 'TXOIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_TXOIS(void);
/*! \brief Reads the bit group 'RXUIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_RXUIS(void);
/*! \brief Reads the bit group 'RXOIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_RXOIS(void);
/*! \brief Reads the bit group 'RXFIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_RXFIS(void);
/*! \brief Reads the bit group 'MSTIS' of register 'SPI1_ISR'. */
U8   GH_SPI1_get_ISR_MSTIS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_ISR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_ISR_TXEIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_TXEIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.txeis;
}
GH_INLINE U8   GH_SPI1_get_ISR_TXOIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_TXOIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.txois;
}
GH_INLINE U8   GH_SPI1_get_ISR_RXUIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXUIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxuis;
}
GH_INLINE U8   GH_SPI1_get_ISR_RXOIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXOIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxois;
}
GH_INLINE U8   GH_SPI1_get_ISR_RXFIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_RXFIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.rxfis;
}
GH_INLINE U8   GH_SPI1_get_ISR_MSTIS(void)
{
    GH_SPI1_ISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ISR_MSTIS] --> 0x%08x\n",
                        REG_SPI1_ISR,value);
    #endif
    return tmp_value.bitc.mstis;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RISR (read)                                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_RISR'. */
U32  GH_SPI1_get_RISR(void);
/*! \brief Reads the bit group 'TXEIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_TXEIR(void);
/*! \brief Reads the bit group 'TXOIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_TXOIR(void);
/*! \brief Reads the bit group 'RXUIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_RXUIR(void);
/*! \brief Reads the bit group 'RXOIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_RXOIR(void);
/*! \brief Reads the bit group 'RXFIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_RXFIR(void);
/*! \brief Reads the bit group 'MSTIR' of register 'SPI1_RISR'. */
U8   GH_SPI1_get_RISR_MSTIR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_RISR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_RISR_TXEIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_TXEIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.txeir;
}
GH_INLINE U8   GH_SPI1_get_RISR_TXOIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_TXOIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.txoir;
}
GH_INLINE U8   GH_SPI1_get_RISR_RXUIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXUIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxuir;
}
GH_INLINE U8   GH_SPI1_get_RISR_RXOIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXOIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxoir;
}
GH_INLINE U8   GH_SPI1_get_RISR_RXFIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_RXFIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.rxfir;
}
GH_INLINE U8   GH_SPI1_get_RISR_MSTIR(void)
{
    GH_SPI1_RISR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RISR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RISR_MSTIR] --> 0x%08x\n",
                        REG_SPI1_RISR,value);
    #endif
    return tmp_value.bitc.mstir;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_TXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_TXOICR'. */
U32  GH_SPI1_get_TXOICR(void);
/*! \brief Reads the bit group 'TXOICR' of register 'SPI1_TXOICR'. */
U8   GH_SPI1_get_TXOICR_TXOICR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_TXOICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_TXOICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXOICR] --> 0x%08x\n",
                        REG_SPI1_TXOICR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_TXOICR_TXOICR(void)
{
    GH_SPI1_TXOICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_TXOICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_TXOICR_TXOICR] --> 0x%08x\n",
                        REG_SPI1_TXOICR,value);
    #endif
    return tmp_value.bitc.txoicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_RXOICR'. */
U32  GH_SPI1_get_RXOICR(void);
/*! \brief Reads the bit group 'RXOICR' of register 'SPI1_RXOICR'. */
U8   GH_SPI1_get_RXOICR_RXOICR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_RXOICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXOICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXOICR] --> 0x%08x\n",
                        REG_SPI1_RXOICR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_RXOICR_RXOICR(void)
{
    GH_SPI1_RXOICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXOICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXOICR_RXOICR] --> 0x%08x\n",
                        REG_SPI1_RXOICR,value);
    #endif
    return tmp_value.bitc.rxoicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_RXUICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_RXUICR'. */
U32  GH_SPI1_get_RXUICR(void);
/*! \brief Reads the bit group 'RXUICR' of register 'SPI1_RXUICR'. */
U8   GH_SPI1_get_RXUICR_RXUICR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_RXUICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_RXUICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXUICR] --> 0x%08x\n",
                        REG_SPI1_RXUICR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_RXUICR_RXUICR(void)
{
    GH_SPI1_RXUICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_RXUICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_RXUICR_RXUICR] --> 0x%08x\n",
                        REG_SPI1_RXUICR,value);
    #endif
    return tmp_value.bitc.rxuicr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_MSTICR (read)                                                */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_MSTICR'. */
U32  GH_SPI1_get_MSTICR(void);
/*! \brief Reads the bit group 'MSTICR' of register 'SPI1_MSTICR'. */
U8   GH_SPI1_get_MSTICR_MSTICR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_MSTICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_MSTICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_MSTICR] --> 0x%08x\n",
                        REG_SPI1_MSTICR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_MSTICR_MSTICR(void)
{
    GH_SPI1_MSTICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_MSTICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_MSTICR_MSTICR] --> 0x%08x\n",
                        REG_SPI1_MSTICR,value);
    #endif
    return tmp_value.bitc.msticr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_ICR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_ICR'. */
U32  GH_SPI1_get_ICR(void);
/*! \brief Reads the bit group 'ICR' of register 'SPI1_ICR'. */
U8   GH_SPI1_get_ICR_ICR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_ICR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_ICR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ICR] --> 0x%08x\n",
                        REG_SPI1_ICR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_ICR_ICR(void)
{
    GH_SPI1_ICR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_ICR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_ICR_ICR] --> 0x%08x\n",
                        REG_SPI1_ICR,value);
    #endif
    return tmp_value.bitc.icr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_IDR (read)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_IDR'. */
U32  GH_SPI1_get_IDR(void);
/*! \brief Reads the bit group 'ID' of register 'SPI1_IDR'. */
U8   GH_SPI1_get_IDR_ID(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_IDR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_IDR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IDR] --> 0x%08x\n",
                        REG_SPI1_IDR,value);
    #endif
    return value;
}
GH_INLINE U8   GH_SPI1_get_IDR_ID(void)
{
    GH_SPI1_IDR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_IDR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_IDR_ID] --> 0x%08x\n",
                        REG_SPI1_IDR,value);
    #endif
    return tmp_value.bitc.id;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_DR (read)                                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'SPI1_DR'. */
U32  GH_SPI1_get_DR(void);
/*! \brief Reads the bit group 'DR' of register 'SPI1_DR'. */
U16  GH_SPI1_get_DR_DR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_SPI1_get_DR(void)
{
    U32 value = (*(volatile U32 *)REG_SPI1_DR);

    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_DR] --> 0x%08x\n",
                        REG_SPI1_DR,value);
    #endif
    return value;
}
GH_INLINE U16  GH_SPI1_get_DR_DR(void)
{
    GH_SPI1_DR_S tmp_value;
    U32 value = (*(volatile U32 *)REG_SPI1_DR);

    tmp_value.all = value;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_SPI1_get_DR_DR] --> 0x%08x\n",
                        REG_SPI1_DR,value);
    #endif
    return tmp_value.bitc.dr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register SPI1_DW (write)                                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL < 2
/*! \brief Writes the register 'SPI1_DW'. */
void GH_SPI1_set_DW(U32 data);
/*! \brief Reads the mirror variable of the register 'SPI1_DW'. */
U32  GH_SPI1_getm_DW(void);
/*! \brief Writes the bit group 'DW' of register 'SPI1_DW'. */
void GH_SPI1_set_DW_DW(U16 data);
/*! \brief Reads the bit group 'DW' from the mirror variable of register 'SPI1_DW'. */
U16  GH_SPI1_getm_DW_DW(void);
#else /* GH_INLINE_LEVEL < 2 */
GH_INLINE void GH_SPI1_set_DW(U32 data)
{
    m_spi1_dw.all = data;
    *(volatile U32 *)REG_SPI1_DW = data;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_DW] <-- 0x%08x\n",
                        REG_SPI1_DW,data,data);
    #endif
}
GH_INLINE U32  GH_SPI1_getm_DW(void)
{
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "[GH_SPI1_getm_DW] --> 0x%08x\n",
                        m_spi1_dw.all);
    #endif
    return m_spi1_dw.all;
}
GH_INLINE void GH_SPI1_set_DW_DW(U16 data)
{
    m_spi1_dw.bitc.dw = data;
    *(volatile U32 *)REG_SPI1_DW = m_spi1_dw.all;
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_SPI1_set_DW_DW] <-- 0x%08x\n",
                        REG_SPI1_DW,m_spi1_dw.all,m_spi1_dw.all);
    #endif
}
GH_INLINE U16  GH_SPI1_getm_DW_DW(void)
{
    #if GH_SPI1_ENABLE_DEBUG_PRINT
    GH_SPI1_DEBUG_PRINT_FUNCTION( "[GH_SPI1_getm_DW_DW] --> 0x%08x\n",
                        m_spi1_dw.bitc.dw);
    #endif
    return m_spi1_dw.bitc.dw;
}
#endif /* GH_INLINE_LEVEL < 2 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SPI1_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SPI1_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

