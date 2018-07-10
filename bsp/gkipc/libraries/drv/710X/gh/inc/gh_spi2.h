/*!
*******************************************************************************
**
** \file      gh_spi2.h
**
** \brief     Slave interface; Slave3, TSSI.
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
#ifndef _GH_SPI2_H
#define _GH_SPI2_H

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

#define GH_SPI2_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_SPI2_DEBUG_PRINT_FUNCTION printk
#else
#define GH_SPI2_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_SPI2_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_SPI2_CTRLR0                                     FIO_ADDRESS(SPI2,0xa0001000) /* read/write */
#define REG_SPI2_CTRLR1                                     FIO_ADDRESS(SPI2,0xa0001004) /* read/write */
#define REG_SPI2_SSIENR                                     FIO_ADDRESS(SPI2,0xa0001008) /* read/write */
#define REG_SPI2_SER                                        FIO_ADDRESS(SPI2,0xa0001010) /* read/write */
#define REG_SPI2_BAUDR                                      FIO_ADDRESS(SPI2,0xa0001014) /* read/write */
#define REG_SPI2_TXFTLR                                     FIO_ADDRESS(SPI2,0xa0001018) /* read/write */
#define REG_SPI2_RXFTLR                                     FIO_ADDRESS(SPI2,0xa000101C) /* read/write */
#define REG_SPI2_TXFLR                                      FIO_ADDRESS(SPI2,0xa0001020) /* read/write */
#define REG_SPI2_RXFLR                                      FIO_ADDRESS(SPI2,0xa0001024) /* read/write */
#define REG_SPI2_SR                                         FIO_ADDRESS(SPI2,0xa0001028) /* read */
#define REG_SPI2_IMR                                        FIO_ADDRESS(SPI2,0xa000102C) /* read/write */
#define REG_SPI2_ISR                                        FIO_ADDRESS(SPI2,0xa0001030) /* read */
#define REG_SPI2_RISR                                       FIO_ADDRESS(SPI2,0xa0001034) /* read */
#define REG_SPI2_TXOICR                                     FIO_ADDRESS(SPI2,0xa0001038) /* read */
#define REG_SPI2_RXOICR                                     FIO_ADDRESS(SPI2,0xa000103C) /* read */
#define REG_SPI2_RXUICR                                     FIO_ADDRESS(SPI2,0xa0001040) /* read */
#define REG_SPI2_MSTICR                                     FIO_ADDRESS(SPI2,0xa0001044) /* read */
#define REG_SPI2_ICR                                        FIO_ADDRESS(SPI2,0xa0001048) /* read */
#define REG_SPI2_IDR                                        FIO_ADDRESS(SPI2,0xa0001058) /* read */
#define REG_SPI2_DR                                         FIO_ADDRESS(SPI2,0xa0001060) /* read */
#define REG_SPI2_DW                                         FIO_ADDRESS(SPI2,0xa0001060) /* write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* SPI2_CTRLR0 */
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
} GH_SPI2_CTRLR0_S;

typedef union { /* SPI2_CTRLR1 */
    U32 all;
    struct {
        U32 ndf                         : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_CTRLR1_S;

typedef union { /* SPI2_SSIENR */
    U32 all;
    struct {
        U32 ssi_enb                     : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_SSIENR_S;

typedef union { /* SPI2_SER */
    U32 all;
    struct {
        U32 ser_l                       : 2;
        U32                             : 2;
        U32 ser_h                       : 4;
        U32                             : 24;
    } bitc;
} GH_SPI2_SER_S;

typedef union { /* SPI2_BAUDR */
    U32 all;
    struct {
        U32 sckdv                       : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_BAUDR_S;

typedef union { /* SPI2_TXFTLR */
    U32 all;
    struct {
        U32 tft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI2_TXFTLR_S;

typedef union { /* SPI2_RXFTLR */
    U32 all;
    struct {
        U32 rft                         : 4;
        U32                             : 28;
    } bitc;
} GH_SPI2_RXFTLR_S;

typedef union { /* SPI2_TXFLR */
    U32 all;
    struct {
        U32 txtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI2_TXFLR_S;

typedef union { /* SPI2_RXFLR */
    U32 all;
    struct {
        U32 rxtfl                       : 5;
        U32                             : 27;
    } bitc;
} GH_SPI2_RXFLR_S;

typedef union { /* SPI2_SR */
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
} GH_SPI2_SR_S;

typedef union { /* SPI2_IMR */
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
} GH_SPI2_IMR_S;

typedef union { /* SPI2_ISR */
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
} GH_SPI2_ISR_S;

typedef union { /* SPI2_RISR */
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
} GH_SPI2_RISR_S;

typedef union { /* SPI2_TXOICR */
    U32 all;
    struct {
        U32 txoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_TXOICR_S;

typedef union { /* SPI2_RXOICR */
    U32 all;
    struct {
        U32 rxoicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_RXOICR_S;

typedef union { /* SPI2_RXUICR */
    U32 all;
    struct {
        U32 rxuicr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_RXUICR_S;

typedef union { /* SPI2_MSTICR */
    U32 all;
    struct {
        U32 msticr                      : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_MSTICR_S;

typedef union { /* SPI2_ICR */
    U32 all;
    struct {
        U32 icr                         : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_ICR_S;

typedef union { /* SPI2_IDR */
    U32 all;
    struct {
        U32 id                          : 1;
        U32                             : 31;
    } bitc;
} GH_SPI2_IDR_S;

typedef union { /* SPI2_DR */
    U32 all;
    struct {
        U32 dr                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_DR_S;

typedef union { /* SPI2_DW */
    U32 all;
    struct {
        U32 dw                          : 16;
        U32                             : 16;
    } bitc;
} GH_SPI2_DW_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_SPI2_DW_S                            m_spi2_dw;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register SPI2_CTRLR0 (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0(U32 data);
/*! \brief Reads the register 'SPI2_CTRLR0'. */
U32  GH_SPI2_get_CTRLR0(void);
/*! \brief Writes the bit group 'DFS' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_DFS(U8 data);
/*! \brief Reads the bit group 'DFS' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_DFS(void);
/*! \brief Writes the bit group 'FRF' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_FRF(U8 data);
/*! \brief Reads the bit group 'FRF' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_FRF(void);
/*! \brief Writes the bit group 'SCPH' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_SCPH(U8 data);
/*! \brief Reads the bit group 'SCPH' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_SCPH(void);
/*! \brief Writes the bit group 'SCPOL' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_SCPOL(U8 data);
/*! \brief Reads the bit group 'SCPOL' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_SCPOL(void);
/*! \brief Writes the bit group 'TMOD' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_TMOD(U8 data);
/*! \brief Reads the bit group 'TMOD' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_TMOD(void);
/*! \brief Writes the bit group 'SLV_OE' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_SLV_OE(U8 data);
/*! \brief Reads the bit group 'SLV_OE' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_SLV_OE(void);
/*! \brief Writes the bit group 'SRL' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_SRL(U8 data);
/*! \brief Reads the bit group 'SRL' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_SRL(void);
/*! \brief Writes the bit group 'CFS' of register 'SPI2_CTRLR0'. */
void GH_SPI2_set_CTRLR0_CFS(U8 data);
/*! \brief Reads the bit group 'CFS' of register 'SPI2_CTRLR0'. */
U8   GH_SPI2_get_CTRLR0_CFS(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_CTRLR1 (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_CTRLR1'. */
void GH_SPI2_set_CTRLR1(U32 data);
/*! \brief Reads the register 'SPI2_CTRLR1'. */
U32  GH_SPI2_get_CTRLR1(void);
/*! \brief Writes the bit group 'NDF' of register 'SPI2_CTRLR1'. */
void GH_SPI2_set_CTRLR1_NDF(U16 data);
/*! \brief Reads the bit group 'NDF' of register 'SPI2_CTRLR1'. */
U16  GH_SPI2_get_CTRLR1_NDF(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_SSIENR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_SSIENR'. */
void GH_SPI2_set_SSIENR(U32 data);
/*! \brief Reads the register 'SPI2_SSIENR'. */
U32  GH_SPI2_get_SSIENR(void);
/*! \brief Writes the bit group 'ssi_enb' of register 'SPI2_SSIENR'. */
void GH_SPI2_set_SSIENR_ssi_enb(U8 data);
/*! \brief Reads the bit group 'ssi_enb' of register 'SPI2_SSIENR'. */
U8   GH_SPI2_get_SSIENR_ssi_enb(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_SER (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_SER'. */
void GH_SPI2_set_SER(U32 data);
/*! \brief Reads the register 'SPI2_SER'. */
U32  GH_SPI2_get_SER(void);
/*! \brief Writes the bit group 'SER_L' of register 'SPI2_SER'. */
void GH_SPI2_set_SER_SER_L(U8 data);
/*! \brief Reads the bit group 'SER_L' of register 'SPI2_SER'. */
U8   GH_SPI2_get_SER_SER_L(void);
/*! \brief Writes the bit group 'SER_H' of register 'SPI2_SER'. */
void GH_SPI2_set_SER_SER_H(U8 data);
/*! \brief Reads the bit group 'SER_H' of register 'SPI2_SER'. */
U8   GH_SPI2_get_SER_SER_H(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_BAUDR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_BAUDR'. */
void GH_SPI2_set_BAUDR(U32 data);
/*! \brief Reads the register 'SPI2_BAUDR'. */
U32  GH_SPI2_get_BAUDR(void);
/*! \brief Writes the bit group 'SCKDV' of register 'SPI2_BAUDR'. */
void GH_SPI2_set_BAUDR_SCKDV(U16 data);
/*! \brief Reads the bit group 'SCKDV' of register 'SPI2_BAUDR'. */
U16  GH_SPI2_get_BAUDR_SCKDV(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_TXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_TXFTLR'. */
void GH_SPI2_set_TXFTLR(U32 data);
/*! \brief Reads the register 'SPI2_TXFTLR'. */
U32  GH_SPI2_get_TXFTLR(void);
/*! \brief Writes the bit group 'TFT' of register 'SPI2_TXFTLR'. */
void GH_SPI2_set_TXFTLR_TFT(U8 data);
/*! \brief Reads the bit group 'TFT' of register 'SPI2_TXFTLR'. */
U8   GH_SPI2_get_TXFTLR_TFT(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_RXFTLR (read/write)                                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_RXFTLR'. */
void GH_SPI2_set_RXFTLR(U32 data);
/*! \brief Reads the register 'SPI2_RXFTLR'. */
U32  GH_SPI2_get_RXFTLR(void);
/*! \brief Writes the bit group 'RFT' of register 'SPI2_RXFTLR'. */
void GH_SPI2_set_RXFTLR_RFT(U8 data);
/*! \brief Reads the bit group 'RFT' of register 'SPI2_RXFTLR'. */
U8   GH_SPI2_get_RXFTLR_RFT(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_TXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_TXFLR'. */
void GH_SPI2_set_TXFLR(U32 data);
/*! \brief Reads the register 'SPI2_TXFLR'. */
U32  GH_SPI2_get_TXFLR(void);
/*! \brief Writes the bit group 'TXTFL' of register 'SPI2_TXFLR'. */
void GH_SPI2_set_TXFLR_TXTFL(U8 data);
/*! \brief Reads the bit group 'TXTFL' of register 'SPI2_TXFLR'. */
U8   GH_SPI2_get_TXFLR_TXTFL(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_RXFLR (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_RXFLR'. */
void GH_SPI2_set_RXFLR(U32 data);
/*! \brief Reads the register 'SPI2_RXFLR'. */
U32  GH_SPI2_get_RXFLR(void);
/*! \brief Writes the bit group 'RXTFL' of register 'SPI2_RXFLR'. */
void GH_SPI2_set_RXFLR_RXTFL(U8 data);
/*! \brief Reads the bit group 'RXTFL' of register 'SPI2_RXFLR'. */
U8   GH_SPI2_get_RXFLR_RXTFL(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_SR (read)                                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_SR'. */
U32  GH_SPI2_get_SR(void);
/*! \brief Reads the bit group 'BUSY' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_BUSY(void);
/*! \brief Reads the bit group 'TFNF' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_TFNF(void);
/*! \brief Reads the bit group 'TFE' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_TFE(void);
/*! \brief Reads the bit group 'RFNE' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_RFNE(void);
/*! \brief Reads the bit group 'RFF' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_RFF(void);
/*! \brief Reads the bit group 'TXE' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_TXE(void);
/*! \brief Reads the bit group 'DCOL' of register 'SPI2_SR'. */
U8   GH_SPI2_get_SR_DCOL(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_IMR (read/write)                                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_IMR'. */
void GH_SPI2_set_IMR(U32 data);
/*! \brief Reads the register 'SPI2_IMR'. */
U32  GH_SPI2_get_IMR(void);
/*! \brief Writes the bit group 'TXEIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_TXEIM(U8 data);
/*! \brief Reads the bit group 'TXEIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_TXEIM(void);
/*! \brief Writes the bit group 'TXOIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_TXOIM(U8 data);
/*! \brief Reads the bit group 'TXOIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_TXOIM(void);
/*! \brief Writes the bit group 'RXUIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_RXUIM(U8 data);
/*! \brief Reads the bit group 'RXUIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_RXUIM(void);
/*! \brief Writes the bit group 'RXOIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_RXOIM(U8 data);
/*! \brief Reads the bit group 'RXOIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_RXOIM(void);
/*! \brief Writes the bit group 'RXFIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_RXFIM(U8 data);
/*! \brief Reads the bit group 'RXFIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_RXFIM(void);
/*! \brief Writes the bit group 'MSTIM' of register 'SPI2_IMR'. */
void GH_SPI2_set_IMR_MSTIM(U8 data);
/*! \brief Reads the bit group 'MSTIM' of register 'SPI2_IMR'. */
U8   GH_SPI2_get_IMR_MSTIM(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_ISR (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_ISR'. */
U32  GH_SPI2_get_ISR(void);
/*! \brief Reads the bit group 'TXEIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_TXEIS(void);
/*! \brief Reads the bit group 'TXOIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_TXOIS(void);
/*! \brief Reads the bit group 'RXUIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_RXUIS(void);
/*! \brief Reads the bit group 'RXOIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_RXOIS(void);
/*! \brief Reads the bit group 'RXFIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_RXFIS(void);
/*! \brief Reads the bit group 'MSTIS' of register 'SPI2_ISR'. */
U8   GH_SPI2_get_ISR_MSTIS(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_RISR (read)                                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_RISR'. */
U32  GH_SPI2_get_RISR(void);
/*! \brief Reads the bit group 'TXEIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_TXEIR(void);
/*! \brief Reads the bit group 'TXOIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_TXOIR(void);
/*! \brief Reads the bit group 'RXUIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_RXUIR(void);
/*! \brief Reads the bit group 'RXOIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_RXOIR(void);
/*! \brief Reads the bit group 'RXFIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_RXFIR(void);
/*! \brief Reads the bit group 'MSTIR' of register 'SPI2_RISR'. */
U8   GH_SPI2_get_RISR_MSTIR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_TXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_TXOICR'. */
U32  GH_SPI2_get_TXOICR(void);
/*! \brief Reads the bit group 'TXOICR' of register 'SPI2_TXOICR'. */
U8   GH_SPI2_get_TXOICR_TXOICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_RXOICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_RXOICR'. */
U32  GH_SPI2_get_RXOICR(void);
/*! \brief Reads the bit group 'RXOICR' of register 'SPI2_RXOICR'. */
U8   GH_SPI2_get_RXOICR_RXOICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_RXUICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_RXUICR'. */
U32  GH_SPI2_get_RXUICR(void);
/*! \brief Reads the bit group 'RXUICR' of register 'SPI2_RXUICR'. */
U8   GH_SPI2_get_RXUICR_RXUICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_MSTICR (read)                                                */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_MSTICR'. */
U32  GH_SPI2_get_MSTICR(void);
/*! \brief Reads the bit group 'MSTICR' of register 'SPI2_MSTICR'. */
U8   GH_SPI2_get_MSTICR_MSTICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_ICR (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_ICR'. */
U32  GH_SPI2_get_ICR(void);
/*! \brief Reads the bit group 'ICR' of register 'SPI2_ICR'. */
U8   GH_SPI2_get_ICR_ICR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_IDR (read)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_IDR'. */
U32  GH_SPI2_get_IDR(void);
/*! \brief Reads the bit group 'ID' of register 'SPI2_IDR'. */
U8   GH_SPI2_get_IDR_ID(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_DR (read)                                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'SPI2_DR'. */
U32  GH_SPI2_get_DR(void);
/*! \brief Reads the bit group 'DR' of register 'SPI2_DR'. */
U16  GH_SPI2_get_DR_DR(void);

/*----------------------------------------------------------------------------*/
/* register SPI2_DW (write)                                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'SPI2_DW'. */
void GH_SPI2_set_DW(U32 data);
/*! \brief Reads the mirror variable of the register 'SPI2_DW'. */
U32  GH_SPI2_getm_DW(void);
/*! \brief Writes the bit group 'DW' of register 'SPI2_DW'. */
void GH_SPI2_set_DW_DW(U16 data);
/*! \brief Reads the bit group 'DW' from the mirror variable of register 'SPI2_DW'. */
U16  GH_SPI2_getm_DW_DW(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SPI2_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_spi2.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_SPI2_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

