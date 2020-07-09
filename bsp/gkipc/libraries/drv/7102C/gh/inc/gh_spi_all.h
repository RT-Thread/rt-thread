/*!
*******************************************************************************
**
** \file      gh_spi_all.h
**
** \brief     Buffer Manager.
**
**            This header file includes all BM header files and defines some
**            additional macros/helper functions.
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
#ifndef _GH_SPI_ALL_H
#define _GH_SPI_ALL_H

#include "gtypes.h"
#include "gh_spi0.h"
#include "gh_spi1.h"
#include "gh_spi2.h"

#define GH_SPI0    0
#define GH_SPI1    1
#define GH_SPI2    2
/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void GH_SPI_set_CTRLR0(U8 spi, U32 data);
U32  GH_SPI_get_CTRLR0(U8 spi);
void GH_SPI_set_CTRLR0_DFS(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_DFS(U8 spi);
void GH_SPI_set_CTRLR0_FRF(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_FRF(U8 spi);
void GH_SPI_set_CTRLR0_SCPH(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_SCPH(U8 spi);
void GH_SPI_set_CTRLR0_SCPOL(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_SCPOL(U8 spi);
void GH_SPI_set_CTRLR0_TMOD(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_TMOD(U8 spi);
void GH_SPI_set_CTRLR0_SLV_OE(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_SLV_OE(U8 spi);
void GH_SPI_set_CTRLR0_SRL(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_SRL(U8 spi);
void GH_SPI_set_CTRLR0_CFS(U8 spi, U8 data);
U8   GH_SPI_get_CTRLR0_CFS(U8 spi);
void GH_SPI_set_CTRLR1(U8 spi, U32 data);
U32  GH_SPI_get_CTRLR1(U8 spi);
void GH_SPI_set_CTRLR1_NDF(U8 spi, U16 data);
U16  GH_SPI_get_CTRLR1_NDF(U8 spi);
void GH_SPI_set_SSIENR(U8 spi, U32 data);
U32  GH_SPI_get_SSIENR(U8 spi);
void GH_SPI_set_SSIENR_ssi_enb(U8 spi, U8 data);
U8   GH_SPI_get_SSIENR_ssi_enb(U8 spi);
void GH_SPI_set_SER(U8 spi, U32 data);
U32  GH_SPI_get_SER(U8 spi);
void GH_SPI_set_SER_SER_L(U8 spi, U8 data);
U8   GH_SPI_get_SER_SER_L(U8 spi);
void GH_SPI_set_SER_SER_H(U8 spi, U8 data);
U8   GH_SPI_get_SER_SER_H(U8 spi);
void GH_SPI_set_BAUDR(U8 spi, U32 data);
U32  GH_SPI_get_BAUDR(U8 spi);
void GH_SPI_set_BAUDR_SCKDV(U8 spi, U16 data);
U16  GH_SPI_get_BAUDR_SCKDV(U8 spi);
void GH_SPI_set_TXFTLR(U8 spi, U32 data);
U32  GH_SPI_get_TXFTLR(U8 spi);
void GH_SPI_set_TXFTLR_TFT(U8 spi, U8 data);
U8   GH_SPI_get_TXFTLR_TFT(U8 spi);
void GH_SPI_set_RXFTLR(U8 spi, U32 data);
U32  GH_SPI_get_RXFTLR(U8 spi);
void GH_SPI_set_RXFTLR_RFT(U8 spi, U8 data);
U8   GH_SPI_get_RXFTLR_RFT(U8 spi);
void GH_SPI_set_TXFLR(U8 spi, U32 data);
U32  GH_SPI_get_TXFLR(U8 spi);
void GH_SPI_set_TXFLR_TXTFL(U8 spi, U8 data);
U8   GH_SPI_get_TXFLR_TXTFL(U8 spi);
void GH_SPI_set_RXFLR(U8 spi, U32 data);
U32  GH_SPI_get_RXFLR(U8 spi);
void GH_SPI_set_RXFLR_RXTFL(U8 spi, U8 data);
U8   GH_SPI_get_RXFLR_RXTFL(U8 spi);
U32  GH_SPI_get_SR(U8 spi);
U8   GH_SPI_get_SR_BUSY(U8 spi);
U8   GH_SPI_get_SR_TFNF(U8 spi);
U8   GH_SPI_get_SR_TFE(U8 spi);
U8   GH_SPI_get_SR_RFNE(U8 spi);
U8   GH_SPI_get_SR_RFF(U8 spi);
U8   GH_SPI_get_SR_TXE(U8 spi);
U8   GH_SPI_get_SR_DCOL(U8 spi);
void GH_SPI_set_IMR(U8 spi, U32 data);
U32  GH_SPI_get_IMR(U8 spi);
void GH_SPI_set_IMR_TXEIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_TXEIM(U8 spi);
void GH_SPI_set_IMR_TXOIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_TXOIM(U8 spi);
void GH_SPI_set_IMR_RXUIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_RXUIM(U8 spi);
void GH_SPI_set_IMR_RXOIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_RXOIM(U8 spi);
void GH_SPI_set_IMR_RXFIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_RXFIM(U8 spi);
void GH_SPI_set_IMR_MSTIM(U8 spi, U8 data);
U8   GH_SPI_get_IMR_MSTIM(U8 spi);
U32  GH_SPI_get_ISR(U8 spi);
U8   GH_SPI_get_ISR_TXEIS(U8 spi);
U8   GH_SPI_get_ISR_TXOIS(U8 spi);
U8   GH_SPI_get_ISR_RXUIS(U8 spi);
U8   GH_SPI_get_ISR_RXOIS(U8 spi);
U8   GH_SPI_get_ISR_RXFIS(U8 spi);
U8   GH_SPI_get_ISR_MSTIS(U8 spi);
U32  GH_SPI_get_RISR(U8 spi);
U8   GH_SPI_get_RISR_TXEIR(U8 spi);
U8   GH_SPI_get_RISR_TXOIR(U8 spi);
U8   GH_SPI_get_RISR_RXUIR(U8 spi);
U8   GH_SPI_get_RISR_RXOIR(U8 spi);
U8   GH_SPI_get_RISR_RXFIR(U8 spi);
U8   GH_SPI_get_RISR_MSTIR(U8 spi);
U32  GH_SPI_get_TXOICR(U8 spi);
U8   GH_SPI_get_TXOICR_TXOICR(U8 spi);
U32  GH_SPI_get_RXOICR(U8 spi);
U8   GH_SPI_get_RXOICR_RXOICR(U8 spi);
U32  GH_SPI_get_RXUICR(U8 spi);
U8   GH_SPI_get_RXUICR_RXUICR(U8 spi);
U32  GH_SPI_get_MSTICR(U8 spi);
U8   GH_SPI_get_MSTICR_MSTICR(U8 spi);
U32  GH_SPI_get_ICR(U8 spi);
U8   GH_SPI_get_ICR_ICR(U8 spi);
U32  GH_SPI_get_IDR(U8 spi);
U8   GH_SPI_get_IDR_ID(U8 spi);
void GH_SPI_set_DW(U8 spi, U32 data);
U32  GH_SPI_get_DR(U8 spi);
void GH_SPI_set_DW_DW(U8 spi, U16 data);
U16  GH_SPI_get_DR_DR(U8 spi);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_SPI_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_SPI_ALL_H */
