/******************************************************************************
**
** \file      gh_sflash.c
**
** \brief     SFLASH.
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
#include <stdio.h>
#include <string.h>
#include "gh_sflash.h"
#include "gh_spi_all.h"
#include "gd_gpio.h"
#include "gd_sflash.h"

/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
static GH_SFLASH_COMMAND_S sflashCmd;
static GBOOL setflashCmd = GFALSE;
#define SPI_NOPDATA        0x00
static GD_SPI_STATUS_PARAMS_S*    pSflashHandle = NULL;

/*----------------------------------------------------------------------------*/
/* register UART_Dr (read/write)                                              */
/*----------------------------------------------------------------------------*/

void GH_SPI_SFLASH_set_Handle(GD_SPI_STATUS_PARAMS_S* pHandle)
{
    pSflashHandle = pHandle;
    U32 type = GD_GPIO_TYPE_OUTPUT_SPI0_CS0;
    GH_SPI_set_SER(pSflashHandle->spi, 0x01);
    if(GD_GPIO_Open(GD_GPIO_34,GD_GPIO_TYPE_OUTPUT_SPI0_CS0,NULL,&pSflashHandle->cs)!=GD_OK)
        printf("sf cs open error\n");;
}

void GH_SPI_SFLASH_set_Command(U32 data)
{
    sflashCmd.all = data;
    setflashCmd = GTRUE;
    if(sflashCmd.bitc.code!=0x06)
    {
        GD_GPIO_Write(pSflashHandle->cs, 1);
    }
    GD_GPIO_Write(pSflashHandle->cs, 0);
}
void GH_SPI_SFLASH_set_Data(U32 data)
{
    U8 senddata;
    if(setflashCmd)
    {
        setflashCmd = GFALSE;
        switch(sflashCmd.all & SFLASH_SEND_CMD)
        {
        case SFLASH_SEND_CMD:
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, sflashCmd.bitc.code);
            GH_SPI_get_DR(pSflashHandle->spi);
            break;
        case SFLASH_NO_SEND_CMD:
            break;
        }
        switch(sflashCmd.all & SFLASH_SEND_ADDR_BYTE_NUM_7)
        {
        case SFLASH_SEND_ADDR_BYTE_NUM_0:
            break;
        case SFLASH_SEND_ADDR_BYTE_NUM_1:
            senddata = data & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);
            break;
        case SFLASH_SEND_ADDR_BYTE_NUM_2:
            senddata = (data>>8) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);

            senddata = data & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);
            break;
        case SFLASH_SEND_ADDR_BYTE_NUM_3:
            senddata = (data>>16) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);

            senddata = (data>>8) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);

            senddata = data & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, senddata);
            GH_SPI_get_DR(pSflashHandle->spi);
            break;
        }
    }
    else
    {
        senddata = (data>>24) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
        GH_SPI_set_DW(pSflashHandle->spi, senddata);
        GH_SPI_get_DR(pSflashHandle->spi);
        senddata = (data>>16) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
        GH_SPI_set_DW(pSflashHandle->spi, senddata);
        GH_SPI_get_DR(pSflashHandle->spi);
        senddata = (data>>8) & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
        GH_SPI_set_DW(pSflashHandle->spi, senddata);
        GH_SPI_get_DR(pSflashHandle->spi);
        senddata = data & 0xFF;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
        GH_SPI_set_DW(pSflashHandle->spi,senddata);
        GH_SPI_get_DR(pSflashHandle->spi);
    }
}
U32  GH_SPI_SFLASH_get_Data(void)
{
    U32 revdata = 0;
    U8  senddata;
    U8 i;
    if(setflashCmd)
    {
        setflashCmd = GFALSE;
        switch(sflashCmd.all & SFLASH_SEND_CMD)
        {
        case SFLASH_SEND_CMD:
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, sflashCmd.bitc.code);
            GH_SPI_get_DR(pSflashHandle->spi);
            break;
        case SFLASH_NO_SEND_CMD:
            break;
        }
    }
    if((sflashCmd.all & SFLASH_TRANSFER_BYTE_NUM_4) == SFLASH_TRANSFER_BYTE_NUM_4)
    {
        sflashCmd.bitc.datanum = 0x04;
    }
    for(i=0;i<sflashCmd.bitc.datanum;i++)
    {
        revdata <<= 8;
        while(GH_SPI_get_RXFLR(pSflashHandle->spi) == 0x00)
            GH_SPI_set_DW(pSflashHandle->spi, SPI_NOPDATA);
        senddata = GH_SPI_get_DR(pSflashHandle->spi);
        revdata += senddata;
    }
    return revdata;
}

void GH_SPI_SFLASH_set_CE(U32 data)
{
    GD_GPIO_Write(pSflashHandle->cs, 0);
}
U32  GH_SPI_SFLASH_get_CE(void)
{
    return 0;
}
U8   GH_SPI_SFLASH_get_CE_CHSELECT(void)
{
    return 0;
}
void GH_SPI_SFLASH_set_Speed(U32 data)
{
}
void GH_SPI_SFLASH_set_CE_CHSELECT(U8 data)
{
    GD_GPIO_Write(pSflashHandle->cs, 1);
}


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

