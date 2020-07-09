/******************************************************************************
**
** \file      gh_spi_all.c
**
** \brief     Helper functions for handling all buffer managers.
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
#include "gtypes.h"
#include "gh_spi_all.h"

void GH_SPI_set_CTRLR0(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0(data);
    }
}

U32  GH_SPI_get_CTRLR0(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_DFS(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_DFS(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_DFS(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_DFS(data);
    }
}

U8   GH_SPI_get_CTRLR0_DFS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_DFS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_DFS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_DFS();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_FRF(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_FRF(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_FRF(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_FRF(data);
    }
}

U8   GH_SPI_get_CTRLR0_FRF(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_FRF();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_FRF();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_FRF();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_SCPH(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_SCPH(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_SCPH(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_SCPH(data);
    }
}

U8   GH_SPI_get_CTRLR0_SCPH(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_SCPH();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_SCPH();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_SCPH();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_SCPOL(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_SCPOL(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_SCPOL(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_SCPOL(data);
    }
}

U8   GH_SPI_get_CTRLR0_SCPOL(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_SCPOL();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_SCPOL();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_SCPOL();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_TMOD(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_TMOD(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_TMOD(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_TMOD(data);
    }
}

U8   GH_SPI_get_CTRLR0_TMOD(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_TMOD();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_TMOD();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_TMOD();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_SLV_OE(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_SLV_OE(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_SLV_OE(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_SLV_OE(data);
    }
}

U8   GH_SPI_get_CTRLR0_SLV_OE(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_SLV_OE();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_SLV_OE();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_SLV_OE();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_SRL(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_SRL(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_SRL(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_SRL(data);
    }
}

U8   GH_SPI_get_CTRLR0_SRL(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_SRL();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_SRL();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_SRL();
    }
    return 0;
}

void GH_SPI_set_CTRLR0_CFS(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR0_CFS(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR0_CFS(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR0_CFS(data);
    }
}

U8   GH_SPI_get_CTRLR0_CFS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR0_CFS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR0_CFS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR0_CFS();
    }
    return 0;
}

void GH_SPI_set_CTRLR1(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR1(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR1(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR1(data);
    }
}

U32  GH_SPI_get_CTRLR1(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR1();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR1();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR1();
    }
    return 0;
}

void GH_SPI_set_CTRLR1_NDF(U8 spi, U16 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_CTRLR1_NDF(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_CTRLR1_NDF(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_CTRLR1_NDF(data);
    }
}

U16  GH_SPI_get_CTRLR1_NDF(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_CTRLR1_NDF();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_CTRLR1_NDF();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_CTRLR1_NDF();
    }
    return 0;
}

void GH_SPI_set_SSIENR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_SSIENR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_SSIENR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_SSIENR(data);
    }
}

U32  GH_SPI_get_SSIENR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SSIENR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SSIENR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SSIENR();
    }
    return 0;
}

void GH_SPI_set_SSIENR_ssi_enb(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_SSIENR_ssi_enb(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_SSIENR_ssi_enb(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_SSIENR_ssi_enb(data);
    }
}

U8   GH_SPI_get_SSIENR_ssi_enb(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SSIENR_ssi_enb();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SSIENR_ssi_enb();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SSIENR_ssi_enb();
    }
    return 0;
}

void GH_SPI_set_SER(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_SER(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_SER(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_SER(data);
    }
}

U32  GH_SPI_get_SER(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SER();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SER();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SER();
    }
    return 0;
}

void GH_SPI_set_SER_SER_L(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_SER_SER_L(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_SER_SER_L(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_SER_SER_L(data);
    }
}

U8   GH_SPI_get_SER_SER_L(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SER_SER_L();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SER_SER_L();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SER_SER_L();
    }
    return 0;
}

void GH_SPI_set_SER_SER_H(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_SER_SER_H(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_SER_SER_H(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_SER_SER_H(data);
    }
}

U8   GH_SPI_get_SER_SER_H(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SER_SER_H();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SER_SER_H();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SER_SER_H();
    }
    return 0;
}

void GH_SPI_set_BAUDR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_BAUDR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_BAUDR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_BAUDR(data);
    }
}

U32  GH_SPI_get_BAUDR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_BAUDR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_BAUDR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_BAUDR();
    }
    return 0;
}

void GH_SPI_set_BAUDR_SCKDV(U8 spi, U16 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_BAUDR_SCKDV(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_BAUDR_SCKDV(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_BAUDR_SCKDV(data);
    }
}

U16  GH_SPI_get_BAUDR_SCKDV(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_BAUDR_SCKDV();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_BAUDR_SCKDV();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_BAUDR_SCKDV();
    }
    return 0;
}

void GH_SPI_set_TXFTLR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_TXFTLR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_TXFTLR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_TXFTLR(data);
    }
}

U32  GH_SPI_get_TXFTLR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXFTLR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXFTLR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXFTLR();
    }
    return 0;
}

void GH_SPI_set_TXFTLR_TFT(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_TXFTLR_TFT(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_TXFTLR_TFT(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_TXFTLR_TFT(data);
    }
}

U8   GH_SPI_get_TXFTLR_TFT(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXFTLR_TFT();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXFTLR_TFT();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXFTLR_TFT();
    }
    return 0;
}

void GH_SPI_set_RXFTLR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_RXFTLR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_RXFTLR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_RXFTLR(data);
    }
}

U32  GH_SPI_get_RXFTLR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXFTLR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXFTLR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXFTLR();
    }
    return 0;
}

void GH_SPI_set_RXFTLR_RFT(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_RXFTLR_RFT(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_RXFTLR_RFT(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_RXFTLR_RFT(data);
    }
}

U8   GH_SPI_get_RXFTLR_RFT(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXFTLR_RFT();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXFTLR_RFT();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXFTLR_RFT();
    }
    return 0;
}

void GH_SPI_set_TXFLR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_TXFLR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_TXFLR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_TXFLR(data);
    }
}

U32  GH_SPI_get_TXFLR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXFLR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXFLR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXFLR();
    }
    return 0;
}

void GH_SPI_set_TXFLR_TXTFL(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_TXFLR_TXTFL(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_TXFLR_TXTFL(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_TXFLR_TXTFL(data);
    }
}

U8   GH_SPI_get_TXFLR_TXTFL(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXFLR_TXTFL();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXFLR_TXTFL();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXFLR_TXTFL();
    }
    return 0;
}

void GH_SPI_set_RXFLR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_RXFLR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_RXFLR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_RXFLR(data);
    }
}

U32  GH_SPI_get_RXFLR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXFLR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXFLR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXFLR();
    }
    return 0;
}

void GH_SPI_set_RXFLR_RXTFL(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_RXFLR_RXTFL(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_RXFLR_RXTFL(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_RXFLR_RXTFL(data);
    }
}

U8   GH_SPI_get_RXFLR_RXTFL(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXFLR_RXTFL();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXFLR_RXTFL();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXFLR_RXTFL();
    }
    return 0;
}

U32  GH_SPI_get_SR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR();
    }
    return 0;
}

U8   GH_SPI_get_SR_BUSY(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_BUSY();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_BUSY();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_BUSY();
    }
    return 0;
}

U8   GH_SPI_get_SR_TFNF(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_TFNF();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_TFNF();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_TFNF();
    }
    return 0;
}

U8   GH_SPI_get_SR_TFE(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_TFE();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_TFE();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_TFE();
    }
    return 0;
}

U8   GH_SPI_get_SR_RFNE(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_RFNE();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_RFNE();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_RFNE();
    }
    return 0;
}

U8   GH_SPI_get_SR_RFF(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_RFF();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_RFF();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_RFF();
    }
    return 0;
}

U8   GH_SPI_get_SR_TXE(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_TXE();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_TXE();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_TXE();
    }
    return 0;
}

U8   GH_SPI_get_SR_DCOL(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_SR_DCOL();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_SR_DCOL();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_SR_DCOL();
    }
    return 0;
}

void GH_SPI_set_IMR(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR(data);
    }
}

U32  GH_SPI_get_IMR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR();
    }
    return 0;
}

void GH_SPI_set_IMR_TXEIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_TXEIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_TXEIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_TXEIM(data);
    }
}

U8   GH_SPI_get_IMR_TXEIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_TXEIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_TXEIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_TXEIM();
    }
    return 0;
}

void GH_SPI_set_IMR_TXOIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_TXOIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_TXOIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_TXOIM(data);
    }
}

U8   GH_SPI_get_IMR_TXOIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_TXOIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_TXOIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_TXOIM();
    }
    return 0;
}

void GH_SPI_set_IMR_RXUIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_RXUIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_RXUIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_RXUIM(data);
    }
}

U8   GH_SPI_get_IMR_RXUIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_RXUIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_RXUIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_RXUIM();
    }
    return 0;
}

void GH_SPI_set_IMR_RXOIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_RXOIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_RXOIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_RXOIM(data);
    }
}

U8   GH_SPI_get_IMR_RXOIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_RXOIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_RXOIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_RXOIM();
    }
    return 0;
}

void GH_SPI_set_IMR_RXFIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_RXFIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_RXFIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_RXFIM(data);
    }
}

U8   GH_SPI_get_IMR_RXFIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_RXFIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_RXFIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_RXFIM();
    }
    return 0;
}

void GH_SPI_set_IMR_MSTIM(U8 spi, U8 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_IMR_MSTIM(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_IMR_MSTIM(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_IMR_MSTIM(data);
    }
}

U8   GH_SPI_get_IMR_MSTIM(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IMR_MSTIM();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IMR_MSTIM();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IMR_MSTIM();
    }
    return 0;
}

U32  GH_SPI_get_ISR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR();
    }
    return 0;
}

U8   GH_SPI_get_ISR_TXEIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_TXEIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_TXEIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_TXEIS();
    }
    return 0;
}

U8   GH_SPI_get_ISR_TXOIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_TXOIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_TXOIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_TXOIS();
    }
    return 0;
}

U8   GH_SPI_get_ISR_RXUIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_RXUIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_RXUIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_RXUIS();
    }
    return 0;
}

U8   GH_SPI_get_ISR_RXOIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_RXOIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_RXOIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_RXOIS();
    }
    return 0;
}

U8   GH_SPI_get_ISR_RXFIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_RXFIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_RXFIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_RXFIS();
    }
    return 0;
}

U8   GH_SPI_get_ISR_MSTIS(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ISR_MSTIS();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ISR_MSTIS();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ISR_MSTIS();
    }
    return 0;
}

U32  GH_SPI_get_RISR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_TXEIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_TXEIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_TXEIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_TXEIR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_TXOIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_TXOIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_TXOIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_TXOIR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_RXUIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_RXUIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_RXUIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_RXUIR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_RXOIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_RXOIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_RXOIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_RXOIR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_RXFIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_RXFIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_RXFIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_RXFIR();
    }
    return 0;
}

U8   GH_SPI_get_RISR_MSTIR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RISR_MSTIR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RISR_MSTIR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RISR_MSTIR();
    }
    return 0;
}

U32  GH_SPI_get_TXOICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXOICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXOICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXOICR();
    }
    return 0;
}

U8   GH_SPI_get_TXOICR_TXOICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_TXOICR_TXOICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_TXOICR_TXOICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_TXOICR_TXOICR();
    }
    return 0;
}

U32  GH_SPI_get_RXOICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXOICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXOICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXOICR();
    }
    return 0;
}

U8   GH_SPI_get_RXOICR_RXOICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXOICR_RXOICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXOICR_RXOICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXOICR_RXOICR();
    }
    return 0;
}

U32  GH_SPI_get_RXUICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXUICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXUICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXUICR();
    }
    return 0;
}

U8   GH_SPI_get_RXUICR_RXUICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_RXUICR_RXUICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_RXUICR_RXUICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_RXUICR_RXUICR();
    }
    return 0;
}

U32  GH_SPI_get_MSTICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_MSTICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_MSTICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_MSTICR();
    }
    return 0;
}

U8   GH_SPI_get_MSTICR_MSTICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_MSTICR_MSTICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_MSTICR_MSTICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_MSTICR_MSTICR();
    }
    return 0;
}

U32  GH_SPI_get_ICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ICR();
    }
    return 0;
}

U8   GH_SPI_get_ICR_ICR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_ICR_ICR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_ICR_ICR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_ICR_ICR();
    }
    return 0;
}

U32  GH_SPI_get_IDR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IDR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IDR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IDR();
    }
    return 0;
}

U8   GH_SPI_get_IDR_ID(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_IDR_ID();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_IDR_ID();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_IDR_ID();
    }
    return 0;
}

void GH_SPI_set_DW(U8 spi, U32 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_DW(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_DW(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_DW(data);
    }
}

U32  GH_SPI_get_DR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_DR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_DR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_DR();
    }
    return 0;
}

void GH_SPI_set_DW_DW(U8 spi, U16 data)
{
    if(spi == GH_SPI0)
    {
        GH_SPI0_set_DW_DW(data);
    }
    else if(spi == GH_SPI1)
    {
        GH_SPI1_set_DW_DW(data);
    }
    else if(spi == GH_SPI2)
    {
        GH_SPI2_set_DW_DW(data);
    }
}

U16  GH_SPI_get_DR_DR(U8 spi)
{
    if(spi == GH_SPI0)
    {
        return GH_SPI0_get_DR_DR();
    }
    else if(spi == GH_SPI1)
    {
        return GH_SPI1_get_DR_DR();
    }
    else if(spi == GH_SPI2)
    {
        return GH_SPI2_get_DR_DR();
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
void GH_SPI_init(void)
{
    GH_SPI0_init();
    GH_SPI1_init();
    GH_SPI2_init();
}
/*---------------------------------------------------------------------------*/
/* end of file                                                               */
/*---------------------------------------------------------------------------*/
