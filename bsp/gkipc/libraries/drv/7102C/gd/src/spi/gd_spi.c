/*
*******************************************************************************
**
** \file      gd_spi.c
**
** \brief     Generic spi   device driver (core functions).
**
**              (C) Goke Microelectronics China 2007 - 2010
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. HUNAN GOFORTUNE SEMICONDUCTOR
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
** \version   $Id: gd_spi.c,v 1.2 2013/11/21 09:28:00
**
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <gtypes.h>
#include <gd_int.h>
#include "gh_spi_all.h"
#include "gd_spi.h"
#include "gd_gpio.h"
#include "gd_sflash.h"
#include "gd_timer.h"

#include "rtthread.h"

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/
//#define DEBUG
#define SPI_BLOCK_COUNT    6  //ÓÐ¼¸¸öSPI 6 + 1 + 1

/* Config SSI_CLK */
#define SPI_RX_TIMEOUT      0xffffffff    /* Number of FIFO entries */
#define SPI_DUMMY_DATA      0x00
#define SPI_FIFO_LEVEL      0x10

/* SPI rw mode */
#define SPI_WRITE_READ      0
#define SPI_WRITE_ONLY      1
#define SPI_READ_ONLY       2
/* Tx FIFO empty interrupt mask */
#define SPI_TXEIS_MASK      0x00000001
#define SPI_TXOIS_MASK      0x00000002
#define SPI_RXUIM_MASK      0x00000004
#define SPI_RXOIM_MASK      0x00000008
#define SPI_RXFIM_MASK      0x00000010
#define SPI_MSTIM_MASK      0x00000020

#define USE_CS_OUTSIDE //rtthread spi driver framework use cs function outside, 20171107,youbo
/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static U8                        SpiInitDone = 0;
static GD_SPI_STATUS_PARAMS_S    SPIstatus[SPI_BLOCK_COUNT];

static GD_SPI_ISR_PARAMS_S       SpiIsr[2];
static GISR1 GD_SPI_ISR0( void );
static GISR1 GD_SPI_ISR1( void );

/*
*******************************************************************************
**
** spiCmdBitSet is used to transfer command from unsigned int to command struct.
**
*******************************************************************************
*/
static GERR spiHandleCheck( GD_HANDLE pHandle )
{
    U32                ii;

    /* check if handle is valid */
    for (ii = 0; ii < SPI_BLOCK_COUNT; ii++)
    {
        if ((pHandle == (GD_HANDLE)(&SPIstatus[ii])) && (SPIstatus[ii].using))
        {
            return GD_OK;
        }
    }
    if (ii >= SPI_BLOCK_COUNT)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}



/*!
********************************************************************************
**
** \brief Initialize the serial peripheral interface driver
**
** This function initializes the serial peripheral interface driver.
**
** \return
** - GD_ERR_ALREADY_INITIALIZED if already initialized
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_Init( void )
{
    U32         ii;

    GERR        ret;
    GD_INT_OPEN_PARAMS_S     intParams0;
    GD_INT_OPEN_PARAMS_S     intParams1;

    /* check if already initialized */
    if(SpiInitDone != 0)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    for (ii = 0; ii < SPI_BLOCK_COUNT; ii++)
    {
        SPIstatus[ii].spi           = 0;
        SPIstatus[ii].slave         = 0;
        SPIstatus[ii].cs            = 0;
        SPIstatus[ii].polarity      = 0;
        SPIstatus[ii].baudrate      = 3000000;  // 3M
        SPIstatus[ii].using         = 0;
        SPIstatus[ii].datwidth      = 8;
		SPIstatus[ii].used_irq      = GFALSE;
    }
    SpiInitDone = 1;
    /*open the sdio control interrupt*/

    intParams0.type           = (S8)GD_INT_SSI_SPI_IRQ;
    intParams0.sensitivity    = GD_INT_LEVEL_HIGH;
    intParams0.active         = GD_INT_INVERT_IRQ;
    intParams0.priority       = GD_INT_MID_PRIORITY;
    intParams0.isrFct.lowPrio = GD_SPI_ISR0;
    ret = GD_INT_Open(&intParams0, &(SpiIsr[0].spiIrqHandle));
    if(ret != GD_OK)
    {
        return GD_ERR_SPI_INI_ERR;
    }
    GD_INT_Enable(&(SpiIsr[0].spiIrqHandle), GD_INT_ENABLED);
    SpiIsr[0].rwmode = GD_SPI_UNUSED;
    
    intParams1.type           = (S8)GD_INT_SSI2_IRQ;
    intParams1.sensitivity    = GD_INT_LEVEL_HIGH;
    intParams1.active         = GD_INT_INVERT_IRQ;
    intParams1.priority       = GD_INT_MID_PRIORITY;
    intParams1.isrFct.lowPrio = GD_SPI_ISR1;
    ret = GD_INT_Open(&intParams1, &(SpiIsr[1].spiIrqHandle));
    if(ret != GD_OK)
    {
        return GD_ERR_SPI_INI_ERR;
    }
    GD_INT_Enable(&(SpiIsr[1].spiIrqHandle), GD_INT_ENABLED);
    SpiIsr[1].rwmode = GD_SPI_UNUSED;

    return GD_OK;
}

/*!
********************************************************************************
**
** \brief Terminates the serial peripheral interface driver
**
** This function terminates the serial peripheral interface driver.
**
** \return
** - GD_ERR_NOT_INITIALIZED if the driver was not initialized before
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_Exit( void )
{
    U32            ii;

    if( SpiInitDone == 0 )
        return( GD_ERR_NOT_INITIALIZED );

    for (ii = 0; ii < SPI_BLOCK_COUNT; ii++)
    {
        SPIstatus[ii].using    = 0;
    }
    SpiInitDone = 0;

    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Opens a new serial peripheral interface driver instance
**
** This function opens a new instance of the serial peripheral interface driver for
** application use. It first checks whether the driver is currently not in
** use because it is not allowed to open more that one instance.
**
** \param pHandle The address of a variable where to store the resulting handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given openParamsP points to 0
** - GD_ERR_ALREADY_OPEN  if the driver is already in use
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_Open( GD_SPI_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle )
{
    U32            ii;

    if((openParamsP == NULL) || (openParamsP->baudrate == 0))
    {
        return GD_ERR_BAD_PARAMETER;
    }
    switch(openParamsP->spi)
    {
    case GD_SPI_CHANNEL_0:
        if(openParamsP->slave > GD_SPI_SLAVE5)
        {
            return GD_ERR_BAD_PARAMETER;
        }
        break;
    case GD_SPI_CHANNEL_1:
        if(openParamsP->slave > GD_SPI_SLAVE1)
        {
            return GD_ERR_BAD_PARAMETER;
        }
        break;
    default:
        return GD_ERR_BAD_PARAMETER;
    }

    for (ii = 0; ii < SPI_BLOCK_COUNT; ii++)
    {
        if (0 == SPIstatus[ii].using)
        {
            SPIstatus[ii].spi           = openParamsP->spi;
            SPIstatus[ii].slave         = openParamsP->slave;
            SPIstatus[ii].using         = 1;
            SPIstatus[ii].polarity      = openParamsP->polarity;
            SPIstatus[ii].baudrate      = openParamsP->baudrate;
            SPIstatus[ii].used_irq      = openParamsP->used_irq;
            break;
        }
    }
    if (ii >= SPI_BLOCK_COUNT)
    {
        return GD_ERR_DEVICE_BUSY;
    }

    // disable
    GH_SPI_set_SSIENR_ssi_enb(openParamsP->spi, 0);
    switch(openParamsP->spi)
    {
    case GD_SPI_CHANNEL_0:
        /*switch(openParamsP->slave)
        {
        case GD_SPI_SLAVE0:
            GH_SPI_set_SER(openParamsP->spi, 0x01);
            break;
        case GD_SPI_SLAVE1:
            GH_SPI_set_SER(openParamsP->spi, 0x02);
            break;
        case GD_SPI_SLAVE2:
            GH_SPI_set_SER(openParamsP->spi, 0x10);
            break;
        case GD_SPI_SLAVE3:
            GH_SPI_set_SER(openParamsP->spi, 0x20);
            break;
        case GD_SPI_SLAVE4:
            GH_SPI_set_SER(openParamsP->spi, 0x40);
            break;
        case GD_SPI_SLAVE5:
            GH_SPI_set_SER(openParamsP->spi, 0x80);
            break;
        }*/
        // use spi cs
        if(openParamsP->csgpio < GD_GPIO_NUM)
        {
            GD_GPIO_Open(openParamsP->csgpio, GD_GPIO_TYPE_OUTPUT_1, NULL, &SPIstatus[ii].cs);
            GD_GPIO_Write(SPIstatus[ii].cs, 1);
        }

        break;
    case GD_SPI_CHANNEL_1:
        if(openParamsP->csgpio < GD_GPIO_NUM)
        {
            GD_GPIO_Open(openParamsP->csgpio, GD_GPIO_TYPE_OUTPUT_1, NULL, &SPIstatus[ii].cs);
            GD_GPIO_Write(SPIstatus[ii].cs, 1);
        }
        //GH_SPI_set_SER(openParamsP->spi, GH_SPI_get_SER(openParamsP->spi) | 0x01);
        break;
    default:
        return( GD_ERR_BAD_PARAMETER );
        //break;
    }
    GH_SPI_set_SER(openParamsP->spi, 0x00);

    GH_SPI_set_CTRLR0(openParamsP->spi, 0);
    GH_SPI_set_CTRLR0_CFS(openParamsP->spi, 0x07);
    GH_SPI_set_CTRLR0_DFS(openParamsP->spi, 0x07);
    if((openParamsP->polarity == SPI_POLARITY_MODE1) || (openParamsP->polarity == SPI_POLARITY_MODE3))
    {
        GH_SPI_set_CTRLR0_SCPH(openParamsP->spi, 0x1);
    }
    else
    {
        GH_SPI_set_CTRLR0_SCPH(openParamsP->spi, 0x0);
    }
    if((openParamsP->polarity == SPI_POLARITY_MODE2) || (openParamsP->polarity == SPI_POLARITY_MODE3))
    {
        GH_SPI_set_CTRLR0_SCPOL(openParamsP->spi, 0x1);
    }
    else
    {
        GH_SPI_set_CTRLR0_SCPOL(openParamsP->spi, 0x0);
    }
    GH_SPI_set_CTRLR1(openParamsP->spi, 0);

    GH_SPI_set_BAUDR_SCKDV(openParamsP->spi, (GD_GET_APB_ClkHz()/openParamsP->baudrate) & 0xFFFE);


    GH_SPI_set_TXFTLR(openParamsP->spi, 0x0F);

    GH_SPI_set_RXFTLR(openParamsP->spi, 0x0F);

    GH_SPI_set_TXFLR(openParamsP->spi, 0x0F);

    GH_SPI_set_RXFLR(openParamsP->spi, 0x0F);

    GH_SPI_set_IMR(openParamsP->spi, 0x0);
    // clear the DR

    /* set GD_HANDLE */
    *pHandle = (GD_HANDLE)(&SPIstatus[ii]);
    GH_SPI_set_SSIENR_ssi_enb(openParamsP->spi, 1);
    // clear the fifo
    while(GH_SPI_get_RXFLR(openParamsP->spi))
    {
        GH_SPI_get_DR(openParamsP->spi);
    }
    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Closes a serial peripheral interface driver instance
**
** This function closes an open instance of the serial peripheral interface driver
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_Close( GD_HANDLE *pHandle )
{
    GERR            ret;
    GD_SPI_STATUS_PARAMS_S    *status = (GD_SPI_STATUS_PARAMS_S *)(*pHandle);

    ret = spiHandleCheck(*pHandle);
    if (GD_OK != ret)
    {
        return ret;
    }

    if(status->cs)
    {
        GD_GPIO_Close(&status->cs);
        status->cs = 0;
    }

    status->using = 0;
    pHandle = NULL;

    return( GD_OK );
}

void GD_SPI_Transfer_Mode(GD_SPI_ISR_PARAMS_S* SpiTHandle)
{
    SpiTHandle->all_len  = SpiTHandle->write_len + SpiTHandle->read_len;
    SpiTHandle->finished = 0;
    if(SpiTHandle->read_len == 0)
    {
        SpiTHandle->rwmode = GD_SPI_WRITE_ONLY;
    }
    else if(SpiTHandle->write_len == 0)
    {
        SpiTHandle->rwmode = GD_SPI_READ_ONLY;
    }
    else
    {
        SpiTHandle->rwmode = GD_SPI_WRITE_READ;
    }
    if(SpiTHandle->bitpw > 8)
    {
        SpiTHandle->bitpw = 16;
    }
    else
    {
        SpiTHandle->bitpw = 8;
    }
    GH_SPI_set_SSIENR_ssi_enb(SpiTHandle->spi, 0x0);
    GH_SPI_set_CTRLR0_CFS(SpiTHandle->spi, SpiTHandle->bitpw - 1);
    GH_SPI_set_CTRLR0_DFS(SpiTHandle->spi, SpiTHandle->bitpw - 1);
    GH_SPI_set_SSIENR_ssi_enb(SpiTHandle->spi, 0x1);
}

GERR GD_SPI_StartTransfer(GD_SPI_ISR_PARAMS_S* SpiTHandle)
{
    U16 temp;
    U32 w_xfer;
    U32 xfer;
    U32 i;
#ifdef DEBUG
printf("write-");
#endif
    switch(SpiTHandle->rwmode)
    {
    case GD_SPI_WRITE_ONLY:
#ifdef DEBUG
        printf("wo:");
#endif
        xfer = SpiTHandle->all_len - SpiTHandle->wf_len;
        if(xfer == 0)
            return GD_OK;
        if(xfer > SPI_FIFO_LEVEL)
        {
            xfer = SPI_FIFO_LEVEL;
        }
		#ifndef USE_CS_OUTSIDE
        	GD_SPI_GetDevice(SpiTHandle->spihandle);
		#endif
        GH_SPI_set_RXFTLR_RFT(SpiTHandle->spi, xfer - 1);
        for(i = 0; i < xfer; i++)
        {
            if(SpiTHandle->bitpw == 16)
            {
                temp = ((U16 *)SpiTHandle->wbuf)[SpiTHandle->wf_len++];
            }
            else
            {
                temp = ((U8 *)SpiTHandle->wbuf)[SpiTHandle->wf_len++];
            }
            GH_SPI_set_DW(SpiTHandle->spi, temp);
#ifdef DEBUG
            printf("%02x ",temp);
#endif
        }
        SpiTHandle->w_xfer = xfer;
        SpiTHandle->r_xfer = 0;
        break;
    case GD_SPI_WRITE_READ:
#ifdef DEBUG
        printf("wr:");
#endif
        xfer = SpiTHandle->all_len - SpiTHandle->wf_len - SpiTHandle->rf_len;
        if(xfer == 0)
            return GD_OK;
        if(xfer > SPI_FIFO_LEVEL)
        {
            xfer = SPI_FIFO_LEVEL;
        }
        if(SpiTHandle->wf_len < SpiTHandle->write_len)
        {
            w_xfer = SpiTHandle->write_len - SpiTHandle->wf_len;
        }
        else
        {
            w_xfer = 0;
        }
        if((w_xfer > xfer) && (w_xfer != 0))
        {
            w_xfer = xfer;
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(SpiTHandle->spihandle);
		#endif
        GH_SPI_set_RXFTLR_RFT(SpiTHandle->spi, xfer - 1);
        for(i = 0;i < w_xfer; i++)
        {
            if(SpiTHandle->bitpw == 16)
            {
                temp = ((U16 *)SpiTHandle->wbuf)[SpiTHandle->wf_len++];
            }
            else
            {
                temp = ((U8 *)SpiTHandle->wbuf)[SpiTHandle->wf_len++];
            }
            GH_SPI_set_DW(SpiTHandle->spi, temp);
#ifdef DEBUG
            printf("%02x ",temp);
#endif
        }
        SpiTHandle->w_xfer = i;
        SpiTHandle->r_xfer = xfer - i;
        for(i = w_xfer; i < xfer; i++)
        {
            GH_SPI_set_DW(SpiTHandle->spi, SPI_DUMMY_DATA);
#ifdef DEBUG
            printf("-- ");
#endif
        }
        break;
    case GD_SPI_READ_ONLY:
#ifdef DEBUG
        printf("ro:");
#endif
        xfer = SpiTHandle->all_len - SpiTHandle->rf_len;
        if(xfer == 0)
            return GD_OK;
        if(xfer > SPI_FIFO_LEVEL)
        {
            xfer = SPI_FIFO_LEVEL;
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(SpiTHandle->spihandle);
		#endif
        GH_SPI_set_RXFTLR_RFT(SpiTHandle->spi, xfer - 1);
        for(i = 0; i < xfer; i++)
        {
            GH_SPI_set_DW(SpiTHandle->spi, SPI_DUMMY_DATA);
#ifdef DEBUG
            printf("-- ",0x00);
#endif
        }
        SpiTHandle->w_xfer = 0;
        SpiTHandle->r_xfer = xfer;
        break;
    }
#ifdef DEBUG
    printf("\n");
#endif
    GH_SPI_set_IMR(SpiTHandle->spi, SPI_RXFIM_MASK);
    return GD_OK;
}

GERR GD_SPI_FinishTransfer(GD_SPI_ISR_PARAMS_S* SpiTHandle)
{
    U32 i = 0;
    U32 rx_xfer;
    U32 dummy;
    U16 data;
    
    while(GH_SPI_get_SR_BUSY(SpiTHandle->spi));
    rx_xfer = GH_SPI_get_RXFLR(SpiTHandle->spi);
#ifdef DEBUG
    printf("read--");
#endif
    switch(SpiTHandle->rwmode)
    {
    case GD_SPI_WRITE_ONLY:
#ifdef DEBUG
        printf("wo:");
#endif
        for(i=0;i<rx_xfer;i++)
        {
            GH_SPI_get_DR(SpiTHandle->spi);
#ifdef DEBUG
            printf("-- ",0x00);
#endif
        }
        break;
    case GD_SPI_WRITE_READ:
    case GD_SPI_READ_ONLY:
        if(SpiTHandle->w_xfer)
        {
#ifdef DEBUG
            printf("wr:");
#endif
            dummy = SpiTHandle->w_xfer;
            for(i=0;i<dummy;i++)
            {
                GH_SPI_get_DR(SpiTHandle->spi);
#ifdef DEBUG
                printf("-- ",0x00);
#endif
            }
        }
        else
        {
#ifdef DEBUG
            printf("ro:");
#endif
        }
        for(i = SpiTHandle->w_xfer;i<rx_xfer;i++)
        {
            data = GH_SPI_get_DR(SpiTHandle->spi);
            if(SpiTHandle->bitpw == 16)
            {
                ((U16 *)SpiTHandle->rbuf)[SpiTHandle->rf_len++] = data & 0xFFFF;
            }
            else
            {
                ((U8 *)SpiTHandle->rbuf)[SpiTHandle->rf_len++] = data & 0x00FF;
            }
#ifdef DEBUG
            printf("%02x ",data);
#endif
        }
        break;
    }
#ifdef DEBUG
    printf("\n");
#endif
	#ifndef USE_CS_OUTSIDE
		GD_SPI_ReleaseDevice(SpiTHandle->spihandle);
	#endif
    GH_SPI_set_IMR(SpiTHandle->spi, 0x0);
    GH_SPI_get_ICR(SpiTHandle->spi);
    GH_SPI_get_ISR(SpiTHandle->spi);
    if(SpiTHandle->wf_len == SpiTHandle->write_len && \
        SpiTHandle->rf_len == SpiTHandle->read_len)
    {
        SpiTHandle->rwmode = GD_SPI_UNUSED;
        SpiTHandle->finished = 1;
        SpiTHandle->write_len = 0;
        SpiTHandle->read_len = 0;
        SpiTHandle->all_len = 0;
    }
    else if((i == 0) )//|| (i < SpiTHandle->all_len))
    {
        SpiTHandle->finished = 1;
        SpiTHandle->rwmode = GD_SPI_UNUSED;
    }
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief Closes a serial peripheral interface driver instance
**
** This function closes an open instance of the serial peripheral interface driver
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/

GERR GD_SPI_WriteWords( GD_HANDLE handle, U16* wbuffer, U32 w_words )
{
    GERR    ret;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);
    U16     data;
    U32     wwords;
    U32     rwords;
    /* check if handle is valid */

    if(device->used_irq == GFALSE)
    {
        ret = spiHandleCheck(handle);
        if (GD_OK != ret)
        {
            return ret;
        }

        wwords = 0;
        rwords = 0;
        /* fill the FIFO first */
        while ((wwords < SPI_FIFO_LEVEL) && (wwords < w_words))
        {
            data = wbuffer[wwords++];
            GH_SPI_set_DW(device->spi, (U32)data);
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(handle);
		#endif
        // remain data
        while (wwords < w_words)
        {
            // read data first
            if (rwords <= w_words)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U16)GH_SPI_get_DR(device->spi);
                    rwords++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                data = wbuffer[wwords++];
                GH_SPI_set_DW(device->spi, (U32)data);
            }
        }
        while (rwords < w_words)
        {
            // read data
            if (GH_SPI_get_RXFLR(device->spi))
            {
                /* Consume the dummy data */
                data = (U16)GH_SPI_get_DR(device->spi);
                rwords++;
            }
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_ReleaseDevice(handle);
		#endif
    }
    else
    {
        GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[device->spi];
        int i = 0;
        if(SpiIrqHandle->rwmode != GD_SPI_UNUSED)
        {
            return GD_ERR_SPI_BUSY;
        }
        SpiIrqHandle->spi = device->spi;
        SpiIrqHandle->write_len = w_words;
        SpiIrqHandle->read_len = 0;
        SpiIrqHandle->bitpw = device->datwidth;
        SpiIrqHandle->wbuf = (void *)wbuffer;
        SpiIrqHandle->rbuf = NULL;
        SpiIrqHandle->wf_len = 0;
        SpiIrqHandle->rf_len = 0;
        SpiIrqHandle->w_xfer = 0;
        GD_SPI_Transfer_Mode(SpiIrqHandle);
        GD_SPI_StartTransfer(SpiIrqHandle);
        while(SpiIrqHandle->finished == 0)
        {
            i++;
            if(i>=0xffffffff)
            {
                return GD_ERR_SPI_BUSY;
	 	    }
            rt_thread_yield();
        }
    }

    return( GD_OK );
}

GERR GD_SPI_WriteThenReadWords( GD_HANDLE handle, U16* wbuffer, U32 w_words, U16* rbuffer, U32 r_words )
{
    GERR    ret = GD_OK;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);
    U16     data;
    U32     wwords;
    U32     rwords;
    U32     spi_duration;
    U32     preload  = SPI_FIFO_LEVEL;
    U32     postload = SPI_FIFO_LEVEL;
    U32     i,retry,fifo_size;

    if(device->used_irq == GFALSE)
    {
        wwords = 0;
        rwords = 0;
        /* check if handle is valid */
        ret = spiHandleCheck(handle);
        if (GD_OK != ret)
        {
            return ret;
        }

        //GH_SPI_set_CTRLR0_TMOD(device->spi, SPI_WRITE_READ);
        //GH_SPI_set_IMR(device->spi, SPI_TXEIS_MASK | SPI_TXOIS_MASK);
        /* Find the duration of SPI TX and RX */
        spi_duration = w_words + r_words;

        /* Fill the TX FIFO up with the data to be sent */
        if (w_words < preload)
        {
            preload = w_words;
            if (spi_duration < SPI_FIFO_LEVEL)
                postload = spi_duration;
        }
        while (wwords < preload)
        {
            data = wbuffer[wwords++];
            GH_SPI_set_DW(device->spi, (U32)data);
        }

        while (wwords < postload )
        {
            GH_SPI_set_DW(device->spi, SPI_DUMMY_DATA);
            wwords++;
        }

        /* Enable SPI slave device */
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(handle);
		#endif

        // remain data
        while (wwords < w_words)
        {
            // read data first
            if (rwords < w_words)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U16)GH_SPI_get_DR(device->spi);
                    rwords++;
                }
            }
            else
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    data = (U16)GH_SPI_get_DR(device->spi);
                    *rbuffer++ = data;
                    rwords++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                data = wbuffer[wwords++];
                GH_SPI_set_DW(device->spi, (U32)data);
            }
        }

        while (wwords < spi_duration)
        {
            // read data first
            if (rwords < w_words)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U16)GH_SPI_get_DR(device->spi);
                    rwords++;
                }
            }
            else
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    data = (U16)GH_SPI_get_DR(device->spi);
                    *rbuffer++ = data;
                    rwords++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                GH_SPI_set_DW(device->spi, SPI_DUMMY_DATA);
                wwords++;
            }
        }

        /* Read the remaining data in RX FIFO */
        while (rwords < spi_duration)//r_words)
        {
            fifo_size = GH_SPI_get_RXFLR(device->spi);
            if (fifo_size)
            {
                for (i = 0; i < fifo_size; i++)
                {
                    if (rwords < w_words)
                    {
                        /* Consume the dummy data */
                        data = (U16)GH_SPI_get_DR(device->spi);
                    }
                    else
                    {
                        data = (U16)GH_SPI_get_DR(device->spi);
                        *rbuffer++ = data;
                    }
                    rwords++;
                }
                retry = 0;
            }
            else
            {
                retry++;
                if (retry >= SPI_RX_TIMEOUT)
                {
                    break;
                }
            }
        }
        /* Disable the SPI TX/RX */
		#ifndef USE_CS_OUTSIDE
			GD_SPI_ReleaseDevice(handle);
		#endif
    }
    else
    {
        GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[device->spi];
        i = 0;
        if(SpiIrqHandle->rwmode != GD_SPI_UNUSED)
        {
            return GD_ERR_SPI_BUSY;
        }
        SpiIrqHandle->spi = device->spi;
        SpiIrqHandle->write_len = w_words;
        SpiIrqHandle->read_len = r_words;
        SpiIrqHandle->bitpw = device->datwidth;
        SpiIrqHandle->wbuf = (void *)wbuffer;
        SpiIrqHandle->rbuf = NULL;
        SpiIrqHandle->wf_len = 0;
        SpiIrqHandle->rf_len = 0;
        SpiIrqHandle->w_xfer = 0;
        GD_SPI_Transfer_Mode(SpiIrqHandle);
        GD_SPI_StartTransfer(SpiIrqHandle);
        while(SpiIrqHandle->finished == 0)
        {
            i++;
            if(i>=0xffffffff)
            {
                return GD_ERR_SPI_BUSY;
	 	    }
	 	    rt_thread_yield();
        }
    }
    
    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Closes a serial peripheral interface driver instance
**
** This function closes an open instance of the serial peripheral interface driver
**
** \param pHandle The address of a variable containing the handle of the
**                previously opened handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_WriteBytes( GD_HANDLE handle, U8* wbuffer, U32 w_size )
{
    GERR    ret;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);
    U8      data;
    U32     wbytes;
    U32     rbytes;
    /* check if handle is valid */
	
	ret = spiHandleCheck(handle);
	if (GD_OK != ret)
	{
		return ret;
	}
	
    if(device->used_irq == GFALSE)
    {

        wbytes = 0;
        rbytes = 0;
        /* fill the FIFO first */
        while ((wbytes < SPI_FIFO_LEVEL) && (wbytes < w_size))
        {
            data = wbuffer[wbytes++];
            GH_SPI_set_DW(device->spi, (U32)data);
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(handle);
		#endif			
        // remain data
        while (wbytes < w_size)
        {
            // read data first
            if (rbytes <= w_size)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U8)GH_SPI_get_DR(device->spi);
                    rbytes++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                data = wbuffer[wbytes++];
                GH_SPI_set_DW(device->spi, (U32)data);
            }
        }
        while (rbytes < w_size)
        {
            // read data
            if (GH_SPI_get_RXFLR(device->spi))
            {
                /* Consume the dummy data */
                data = (U8)GH_SPI_get_DR(device->spi);
                rbytes++;
            }
        }
		#ifndef USE_CS_OUTSIDE
			GD_SPI_ReleaseDevice(handle);
		#endif
    }
    else
    {
        GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[device->spi];
        int i = 0;
        if(SpiIrqHandle->rwmode != GD_SPI_UNUSED)
        {
            return GD_ERR_SPI_BUSY;
        }
        SpiIrqHandle->spihandle = handle;
        SpiIrqHandle->spi = device->spi;
        SpiIrqHandle->write_len = w_size;
        SpiIrqHandle->read_len = 0;
        SpiIrqHandle->bitpw = device->datwidth;
        SpiIrqHandle->wbuf = (void *)wbuffer;
        SpiIrqHandle->rbuf = NULL;
        SpiIrqHandle->wf_len = 0;
        SpiIrqHandle->rf_len = 0;
        SpiIrqHandle->w_xfer = 0;
        GD_SPI_Transfer_Mode(SpiIrqHandle);
        GD_SPI_StartTransfer(SpiIrqHandle);
        while(SpiIrqHandle->finished == 0)
        {
            i++;
            if(i>=0xffffffff)
            {
                return GD_ERR_SPI_BUSY;
	 	    }
	 	    rt_thread_yield();
        }
    }

    return( GD_OK );
}

GERR GD_SPI_WriteThenReadBytes( GD_HANDLE handle, U8* wbuffer, U32 w_size, U8* rbuffer, U32 r_size )
{
    GERR    ret = GD_OK;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);
    U8      data;
    U32     wbytes;
    U32     rbytes;
    U32     spi_duration;
    U32     preload = SPI_FIFO_LEVEL;
    U32     postload = SPI_FIFO_LEVEL;
    U32     i,retry,fifo_size;
    
	ret = spiHandleCheck(handle);
	if (GD_OK != ret)
	{
		return ret;
	}
	
    if(device->used_irq == GFALSE)
    {
        wbytes = 0;
        rbytes = 0;

        //GH_SPI_set_CTRLR0_TMOD(device->spi, SPI_WRITE_READ);
        //GH_SPI_set_IMR(device->spi, SPI_TXEIS_MASK | SPI_TXOIS_MASK);
        /* Find the duration of SPI TX and RX */
        spi_duration = w_size + r_size;

        /* Fill the TX FIFO up with the data to be sent */
        if (w_size < preload)
        {
            preload = w_size;
            if (spi_duration < SPI_FIFO_LEVEL)
                postload = spi_duration;
        }
        while (wbytes < preload)
        {
            data = wbuffer[wbytes++];
            GH_SPI_set_DW(device->spi, (U32)data);
        }

        while (wbytes < postload )
        {
            GH_SPI_set_DW(device->spi, SPI_DUMMY_DATA);
            wbytes++;
        }

        /* Enable SPI slave device */
		#ifndef USE_CS_OUTSIDE
			GD_SPI_GetDevice(handle);
		#endif

        // remain data
        while (wbytes < w_size)
        {
            // read data first
            if (rbytes < w_size)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U8)GH_SPI_get_DR(device->spi);
                    rbytes++;
                }
            }
            else
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    data = (U8)GH_SPI_get_DR(device->spi);
                    *rbuffer++ = data;
                    rbytes++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                data = wbuffer[wbytes++];
                GH_SPI_set_DW(device->spi, (U32)data);
            }
        }

        while (wbytes < spi_duration)
        {
            // read data first
            if (rbytes < w_size)
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    /* Consume the dummy data */
                    data = (U8)GH_SPI_get_DR(device->spi);
                    rbytes++;
                }
            }
            else
            {
                if (GH_SPI_get_RXFLR(device->spi))
                {
                    data = (U8)GH_SPI_get_DR(device->spi);
                    *rbuffer++ = data;
                    rbytes++;
                }
            }
            // FIFO not full
            if (GH_SPI_get_SR_TFNF(device->spi))
            {
                GH_SPI_set_DW(device->spi, SPI_DUMMY_DATA);
                wbytes++;

            }
        }

        /* Read the remaining data in RX FIFO */
        while (rbytes < spi_duration)//r_size)
        {
            fifo_size = GH_SPI_get_RXFLR(device->spi);
            if (fifo_size)
            {
                for (i = 0; i < fifo_size; i++)
                {
                    if (rbytes < w_size)
                    {
                        /* Consume the dummy data */
                        data = (U8)GH_SPI_get_DR(device->spi);
                    }
                    else
                    {
                        data = (U8)GH_SPI_get_DR(device->spi);
                        *rbuffer++ = data;
                    }
                    rbytes++;
                }
                retry = 0;
            }
            else
            {
                retry++;
                if (retry >= SPI_RX_TIMEOUT)
                {
                    break;
                }
            }
        }
        /* Disable the SPI TX/RX */
		#ifndef USE_CS_OUTSIDE
			GD_SPI_ReleaseDevice(handle);
		#endif
    }
    else
    {
        GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[device->spi];
        i = 0;
        if(SpiIrqHandle->rwmode != GD_SPI_UNUSED)
        {
            return GD_ERR_SPI_BUSY;
        }
        SpiIrqHandle->spihandle = handle;
        SpiIrqHandle->spi = device->spi;
        SpiIrqHandle->write_len = w_size;
        SpiIrqHandle->read_len = r_size;
        SpiIrqHandle->bitpw = device->datwidth;
        SpiIrqHandle->wbuf = (void *)wbuffer;
        SpiIrqHandle->rbuf = (void *)rbuffer;
        SpiIrqHandle->wf_len = 0;
        SpiIrqHandle->rf_len = 0;
        SpiIrqHandle->w_xfer = 0;
        GD_SPI_Transfer_Mode(SpiIrqHandle);
        GD_SPI_StartTransfer(SpiIrqHandle);
        while(SpiIrqHandle->finished == 0)
        {
            i++;
            if(i>=0xffffffff)
            {
                return GD_ERR_SPI_BUSY;
	 	    }
	 	    rt_thread_yield();
        }
    }
    return( GD_OK );
}

static GISR1 GD_SPI_ISR0( void )
{
    U32 irqsta;

    GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[0];
    
    irqsta = GH_SPI_get_ISR(SpiIrqHandle->spi);
    if(irqsta)
    {
        GD_SPI_FinishTransfer(SpiIrqHandle);
    }
    if(SpiIrqHandle->finished != 1)
    {
        GD_SPI_StartTransfer(SpiIrqHandle);
    }
}
static GISR1 GD_SPI_ISR1( void )
{
    U32 irqsta;

    GD_SPI_ISR_PARAMS_S *SpiIrqHandle = &SpiIsr[1];

    irqsta = GH_SPI_get_ISR(SpiIrqHandle->spi);
    if(irqsta)
    {
        GD_SPI_FinishTransfer(SpiIrqHandle);
    }
    if(SpiIrqHandle->finished != 1)
    {
        GD_SPI_StartTransfer(SpiIrqHandle);
    }
}

GERR GD_SPI_GetDevice(GD_HANDLE handle)
{
    GERR            ret = GD_OK;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);

    if(device->cs)
    {
        GD_GPIO_Write(device->cs, 0);
    }
    switch(device->slave)
    {
    case GD_SPI_SLAVE0:
        GH_SPI_set_SER(device->spi, 0x01);
        break;
    case GD_SPI_SLAVE1:
        GH_SPI_set_SER(device->spi, 0x02);
        break;
    case GD_SPI_SLAVE2:
        GH_SPI_set_SER(device->spi, 0x10);
        break;
    case GD_SPI_SLAVE3:
        GH_SPI_set_SER(device->spi, 0x20);
        break;
    case GD_SPI_SLAVE4:
        GH_SPI_set_SER(device->spi, 0x40);
        break;
    case GD_SPI_SLAVE5:
        GH_SPI_set_SER(device->spi, 0x80);
        break;
    }
    return ret;
}


GERR GD_SPI_SetDatFormat(GD_HANDLE handle, U8 dat_width)
{
    GERR    ret = GD_OK;
    U8      ssi_enb;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);
    if(dat_width>16)
    {
        ret = GD_ERR_BAD_PARAMETER;
    }
    else
    {
        ssi_enb = GH_SPI_get_SSIENR_ssi_enb(device->spi);
        
        GH_SPI_set_SSIENR_ssi_enb(device->spi, 0);//SPI FIFO will be reset

        device->datwidth = dat_width;
        GH_SPI_set_CTRLR0_CFS(device->spi, dat_width-1);
        GH_SPI_set_CTRLR0_DFS(device->spi, dat_width-1);

        GH_SPI_set_SSIENR_ssi_enb(device->spi, ssi_enb);       
    }
    return ret;
}


GERR GD_SPI_ReleaseDevice(GD_HANDLE handle)
{
    GERR            ret = GD_OK;
    GD_SPI_STATUS_PARAMS_S    *device = (GD_SPI_STATUS_PARAMS_S *)(handle);

    if(device->cs)
    {
        GD_GPIO_Write(device->cs, 1);
    }
    GH_SPI_set_SER(device->spi, 0x00);
    return ret;
}

