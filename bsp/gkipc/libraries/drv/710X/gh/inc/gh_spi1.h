/*!
*******************************************************************************
**
** \file      gh_spi1.h
**
** \brief     Master interface and supports up to 1 external SPI slave devices. SSI2.
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SPI1_CTRLR0                                     FIO_ADDRESS(SPI1,0xa000F000) /* read/write */
#define REG_SPI1_CTRLR1                                     FIO_ADDRESS(SPI1,0xa000F004) /* read/write */
#define REG_SPI1_SSIENR                                     FIO_ADDRESS(SPI1,0xa000F008) /* read/write */
#define REG_SPI1_SER                                        FIO_ADDRESS(SPI1,0xa000F010) /* read/write */
#define REG_SPI1_BAUDR                                      FIO_ADDRESS(SPI1,0xa000F014) /* read/write */
#define REG_SPI1_TXFTLR                                     FIO_ADDRESS(SPI1,0xa000F018) /* read/write */
#define REG_SPI1_RXFTLR                                     FIO_ADDRESS(SPI1,0xa000F01C) /* read/write */
#define REG_SPI1_TXFLR                                      FIO_ADDRESS(SPI1,0xa000F020) /* read/write */
#define REG_SPI1_RXFLR                                      FIO_ADDRESS(SPI1,0xa000F024) /* read/write */
#define REG_SPI1_SR                                         FIO_ADDRESS(SPI1,0xa000F028) /* read */
#define REG_SPI1_IMR                                        FIO_ADDRESS(SPI1,0xa000F02C) /* read/write */
#define REG_SPI1_ISR                                        FIO_ADDRESS(SPI1,0xa000F030) /* read */
#define REG_SPI1_RISR                                       FIO_ADDRESS(SPI1,0xa000F034) /* read */
#define REG_SPI1_TXOICR                                     FIO_ADDRESS(SPI1,0xa000F038) /* read */
#define REG_SPI1_RXOICR                                     FIO_ADDRESS(SPI1,0xa000F03C) /* read */
#define REG_SPI1_RXUICR                                     FIO_ADDRESS(SPI1,0xa000F040) /* read */
#define REG_SPI1_MSTICR                                     FIO_ADDRESS(SPI1,0xa000F044) /* read */
#define REG_SPI1_ICR                                        FIO_ADDRESS(SPI1,0xa000F048) /* read */
#define REG_SPI1_IDR                                        FIO_ADDRESS(SPI1,0xa000F058) /* read */
#define REG_SPI1_DR                                         FIO_ADDRESS(SPI1,0xa000F060) /* read */
#define REG_SPI1_DW                                         FIO_ADDRESS(SPI1,0xa000F060) /* write */

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

/*----------------------------------------------------------------------------*/
/* register SPI1_CTRLR1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_CTRLR1'. */
void GH_SPI1_set_CTRLR1(U32 data);
/*! \brief Reads the register 'SPI1_CTRLR1'. */
U32  GH_SPI1_get_CTRLR1(void);
/*! \brief Writes the bit group 'NDF' of register 'SPI1_CTRLR1'. */
void GH_SPI1_set_CTRLR1_NDF(U16 data);
/*! \brief Reads the bit group 'NDF' of register 'SPI1_CTRLR1'. */
U16  GH_SPI1_get_CTRLR1_NDF(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_SSIENR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_SSIENR'. */
void GH_SPI1_set_SSIENR(U32 data);
/*! \brief Reads the register 'SPI1_SSIENR'. */
U32  GH_SPI1_get_SSIENR(void);
/*! \brief Writes the bit group 'ssi_enb' of register 'SPI1_SSIENR'. */
void GH_SPI1_set_SSIENR_ssi_enb(U8 data);
/*! \brief Reads the bit group 'ssi_enb' of register 'SPI1_SSIENR'. */
U8   GH_SPI1_get_SSIENR_ssi_enb(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_SER (read/write)                                             */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register SPI1_BAUDR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_BAUDR'. */
void GH_SPI1_set_BAUDR(U32 data);
/*! \brief Reads the register 'SPI1_BAUDR'. */
U32  GH_SPI1_get_BAUDR(void);
/*! \brief Writes the bit group 'SCKDV' of register 'SPI1_BAUDR'. */
void GH_SPI1_set_BAUDR_SCKDV(U16 data);
/*! \brief Reads the bit group 'SCKDV' of register 'SPI1_BAUDR'. */
U16  GH_SPI1_get_BAUDR_SCKDV(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_TXFTLR'. */
void GH_SPI1_set_TXFTLR(U32 data);
/*! \brief Reads the register 'SPI1_TXFTLR'. */
U32  GH_SPI1_get_TXFTLR(void);
/*! \brief Writes the bit group 'TFT' of register 'SPI1_TXFTLR'. */
void GH_SPI1_set_TXFTLR_TFT(U8 data);
/*! \brief Reads the bit group 'TFT' of register 'SPI1_TXFTLR'. */
U8   GH_SPI1_get_TXFTLR_TFT(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_RXFTLR'. */
void GH_SPI1_set_RXFTLR(U32 data);
/*! \brief Reads the register 'SPI1_RXFTLR'. */
U32  GH_SPI1_get_RXFTLR(void);
/*! \brief Writes the bit group 'RFT' of register 'SPI1_RXFTLR'. */
void GH_SPI1_set_RXFTLR_RFT(U8 data);
/*! \brief Reads the bit group 'RFT' of register 'SPI1_RXFTLR'. */
U8   GH_SPI1_get_RXFTLR_RFT(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_TXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_TXFLR'. */
void GH_SPI1_set_TXFLR(U32 data);
/*! \brief Reads the register 'SPI1_TXFLR'. */
U32  GH_SPI1_get_TXFLR(void);
/*! \brief Writes the bit group 'TXTFL' of register 'SPI1_TXFLR'. */
void GH_SPI1_set_TXFLR_TXTFL(U8 data);
/*! \brief Reads the bit group 'TXTFL' of register 'SPI1_TXFLR'. */
U8   GH_SPI1_get_TXFLR_TXTFL(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_RXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_RXFLR'. */
void GH_SPI1_set_RXFLR(U32 data);
/*! \brief Reads the register 'SPI1_RXFLR'. */
U32  GH_SPI1_get_RXFLR(void);
/*! \brief Writes the bit group 'RXTFL' of register 'SPI1_RXFLR'. */
void GH_SPI1_set_RXFLR_RXTFL(U8 data);
/*! \brief Reads the bit group 'RXTFL' of register 'SPI1_RXFLR'. */
U8   GH_SPI1_get_RXFLR_RXTFL(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_SR (read)                                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register SPI1_IMR (read/write)                                             */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register SPI1_ISR (read)                                                   */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register SPI1_RISR (read)                                                  */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register SPI1_TXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_TXOICR'. */
U32  GH_SPI1_get_TXOICR(void);
/*! \brief Reads the bit group 'TXOICR' of register 'SPI1_TXOICR'. */
U8   GH_SPI1_get_TXOICR_TXOICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_RXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_RXOICR'. */
U32  GH_SPI1_get_RXOICR(void);
/*! \brief Reads the bit group 'RXOICR' of register 'SPI1_RXOICR'. */
U8   GH_SPI1_get_RXOICR_RXOICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_RXUICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_RXUICR'. */
U32  GH_SPI1_get_RXUICR(void);
/*! \brief Reads the bit group 'RXUICR' of register 'SPI1_RXUICR'. */
U8   GH_SPI1_get_RXUICR_RXUICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_MSTICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_MSTICR'. */
U32  GH_SPI1_get_MSTICR(void);
/*! \brief Reads the bit group 'MSTICR' of register 'SPI1_MSTICR'. */
U8   GH_SPI1_get_MSTICR_MSTICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_ICR (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_ICR'. */
U32  GH_SPI1_get_ICR(void);
/*! \brief Reads the bit group 'ICR' of register 'SPI1_ICR'. */
U8   GH_SPI1_get_ICR_ICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_IDR (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_IDR'. */
U32  GH_SPI1_get_IDR(void);
/*! \brief Reads the bit group 'ID' of register 'SPI1_IDR'. */
U8   GH_SPI1_get_IDR_ID(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_DR (read)                                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI1_DR'. */
U32  GH_SPI1_get_DR(void);
/*! \brief Reads the bit group 'DR' of register 'SPI1_DR'. */
U16  GH_SPI1_get_DR_DR(void);

/*----------------------------------------------------------------------------*/
/* register SPI1_DW (write)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI1_DW'. */
void GH_SPI1_set_DW(U32 data);
/*! \brief Reads the mirror variable of the register 'SPI1_DW'. */
U32  GH_SPI1_getm_DW(void);
/*! \brief Writes the bit group 'DW' of register 'SPI1_DW'. */
void GH_SPI1_set_DW_DW(U16 data);
/*! \brief Reads the bit group 'DW' from the mirror variable of register 'SPI1_DW'. */
U16  GH_SPI1_getm_DW_DW(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SPI1_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_spi1.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_SPI1_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

