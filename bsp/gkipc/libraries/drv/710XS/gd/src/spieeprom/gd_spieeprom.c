/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/spieeprom/gd_spieeprom.c
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include <stdio.h>
#include <string.h>
#include <gtypes.h>
#include "gd_spi.h"
#include "gd_spieeprom.h"


//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************
/*
*******************************************************************************
**
** serial spi eeprom specific commands for Spansion spi eeprom devices
**
*******************************************************************************
*/
static GD_SPI_EEPROM_CMD_S gd_spi_eeprom_commands_atmel =
{
    /* writeEnable   */ 0x06,
    /* writeDisable  */ 0x04,
    /* readStatus    */ 0x05,
    /* writeStatus   */ 0x01,
    /* readData      */ 0x03,
    /* writeData     */ 0x02,
};


/*
*******************************************************************************
**
** gd_spi_eeprom_devices_supported is an array containing spi eeprom
** geometry and information data of all supported devices, it will
** be used during GD_SPI_EEPROM_Init() to find the connected serial
** spi eeprom decive
**
*******************************************************************************
*/
static GD_SPI_EEPROM_DEV_S gd_spi_eeprom_devices_supported[] =
{
    {
        /* manufactureName */ "ATMEL",
        /* deviceName      */ "AT25320B",
        /* deviceBytes     */ 0x1000,
        /* sectorCount     */ 4,
        /* sectorBytes     */ 0x1000/4,
        /* commands        */ &gd_spi_eeprom_commands_atmel,
        /* wptoporbottom   */ GFALSE,
        /* device          */ GD_SPI_EEPROM_AT25320B,
    },
    {
        /* manufactureName */ "ATMEL",
        /* deviceName      */ "AT25640B",
        /* deviceBytes     */ 0x2000,
        /* sectorCount     */ 4,
        /* sectorBytes     */ 0x2000/4,
        /* commands        */ &gd_spi_eeprom_commands_atmel,
        /* wptoporbottom   */ GFALSE,
        /* device          */ GD_SPI_EEPROM_AT25640B,
    },
};

/*
*******************************************************************************
**
** gd_spi_eeprom_device is used to point to the device structure
** refering to the device found during GD_SPI_EEPROM_Init()
**
*******************************************************************************
*/
static GD_SPI_EEPROM_DEV_S* gd_spi_eeprom_device[GD_SPI_EEPROM_NUM] = {0};

/*
*******************************************************************************
**
** gd_spi_eeprom_handle is used to store information during GD_SPI_EEPROM_Open()
** according to H/W design, 1 or 2 instance could be supported
**
*******************************************************************************
*/
static GD_SPI_EEPROM_DEV_S* gd_spi_eeprom_handle[GD_SPI_EEPROM_NUM] = {0};


//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************
#if 0
static GERR spi_eepromWipDoneWait(GD_HANDLE handle);
#endif



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

/*!
********************************************************************************
**
** \brief Initialize the serial spi eeprom driver
**
** This function initializes the serial spi eeprom driver, it tries to detect a
** serial spi eeprom device by executing the readID commands for all supported
** vendors, the resulting mannufactor ID and device ID will be checked
** with the values from an internal array containing data for all supported
** devices.
**
** \return
** - GD_ERR_ALREADY_INITIALIZED if already initialized
** - GD_ERR_SPI_EEPROM_TYPE_NOT_SUPPORTED if the connected device is not (yet)
**   supported
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Init(void)
{
    U32 index;
    for(index=0; index<GD_SPI_EEPROM_NUM; index++)
    {
        if( gd_spi_eeprom_device[index] != NULL )
        {
            return( GD_ERR_ALREADY_INITIALIZED );
        }
    }

    for(index=0; index<GD_SPI_EEPROM_NUM; index++)
    {
        gd_spi_eeprom_device[index]         = &gd_spi_eeprom_devices_supported[index];
        gd_spi_eeprom_device[index]->spi    = 0;
        gd_spi_eeprom_device[index]->wp     = 0;
        gd_spi_eeprom_device[index]->hold   = 0;

        gd_spi_eeprom_handle[index]         = NULL;
    }

    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Terminates the serial spi eeprom driver
**
** This function terminates the serial spi eeprom driver.
**
** \return
** - GD_ERR_NOT_INITIALIZED if the driver was not initialized before
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Exit(void)
{
    U32 index;
    for(index=0; index<GD_SPI_EEPROM_NUM; index++)
    {
        if( gd_spi_eeprom_device[index] != NULL )
        {
            break;
        }
    }

    if( index == GD_SPI_EEPROM_NUM )
        return( GD_ERR_NOT_INITIALIZED );

    for(index=0; index<GD_SPI_EEPROM_NUM; index++)
    {
        if( gd_spi_eeprom_device[index]->spi != 0 )
        {
            GD_SPI_Close(&gd_spi_eeprom_device[index]->spi);
            gd_spi_eeprom_device[index]->spi = 0;
        }
        if( gd_spi_eeprom_device[index]->wp != 0 )
        {
            GD_GPIO_Close(&gd_spi_eeprom_device[index]->wp);
            gd_spi_eeprom_device[index]->wp = 0;
        }
        if( gd_spi_eeprom_device[index]->hold != 0 )
        {
            GD_GPIO_Close(&gd_spi_eeprom_device[index]->hold);
            gd_spi_eeprom_device[index]->hold = 0;
        }
        gd_spi_eeprom_device[index]  = NULL;
        gd_spi_eeprom_handle[index]  = NULL;
    }

    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Opens a new serial spi eeprom driver instance
**
** This function opens a new instance of the serial spi eeprom driver for
** application use. It first checks whether the driver is currently not in
** use because it is not allowed to open more that one instance.
**
** \param pHandle The address of a variable where to store the resulting handle
**
** \return
** - GD_ERR_BAD_PARAMETER if the given pHandle parameter points to 0
** - GD_ERR_SPI_EEPROM_IN_USE if the driver is already in use
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Open(GD_SPI_EEPROM_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle)
{
    GERR gerr;
    GD_HANDLE   spihandle;
    GD_HANDLE   wphandle;
    GD_HANDLE   holdhandle;
    GD_SPI_OPEN_PARAMS_S openParams;

    if( !pHandle || !openParamsP )
        return( GD_ERR_BAD_PARAMETER );

    if(openParamsP->device >= GD_SPI_EEPROM_NUM)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    if(openParamsP->channel >= GD_SPI_CHANNEL_NUM)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    if(openParamsP->slave >= GD_SPI_SLAVE_NUM)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    if((openParamsP->csgpiopin >= GD_GPIO_NUM))
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    if((openParamsP->wpgpiopin >= GD_GPIO_NUM) ||
       (openParamsP->holdgpiopin >= GD_GPIO_NUM))
    {
        openParamsP->wpgpiotype = GD_GPIO_TYPE_UNDEFINED;
        openParamsP->holdgpiotype = GD_GPIO_TYPE_UNDEFINED;
        printf("eeprom not user wp and hold pin\n");
    }
    if((openParamsP->csgpiotype != GD_GPIO_TYPE_OUTPUT_0) &&
        (openParamsP->csgpiotype != GD_GPIO_TYPE_OUTPUT_1))
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if( gd_spi_eeprom_handle[openParamsP->device] )
        return( GD_ERR_SPI_EEPROM_IN_USE );

    if( gd_spi_eeprom_device[openParamsP->device] == NULL )
        return( GD_ERR_NOT_INITIALIZED );

    openParams.spi      = openParamsP->channel;
    openParams.slave    = openParamsP->slave;
    openParams.baudrate = openParamsP->speed;
    openParams.polarity = openParamsP->polarity;
    openParams.csgpio   = openParamsP->csgpiopin;
    openParams.used_irq = openParamsP->used_irq;

    gerr = GD_SPI_Open(&openParams, &spihandle) ;
    if(gerr != GD_OK)
    {
        return gerr;
    }

    wphandle = 0;
    if(openParamsP->wpgpiotype != GD_GPIO_TYPE_UNDEFINED)
    {
        gerr = GD_GPIO_Open(openParamsP->wpgpiopin, openParamsP->wpgpiotype, NULL, &wphandle) ;
        if(gerr != GD_OK)
        {
            GD_SPI_Close(&spihandle);
            return gerr;
        }
    }

    holdhandle = 0;
    if(openParamsP->holdgpiotype != GD_GPIO_TYPE_UNDEFINED)
    {
        gerr = GD_GPIO_Open(openParamsP->holdgpiopin, openParamsP->holdgpiotype, NULL, &holdhandle) ;
        if(gerr != GD_OK)
        {
            GD_SPI_Close(&spihandle);
            GD_GPIO_Close(&wphandle);
            return gerr;
        }
    }
    gd_spi_eeprom_device[openParamsP->device] = &gd_spi_eeprom_devices_supported[openParamsP->device];
    gd_spi_eeprom_device[openParamsP->device]->spi  = spihandle;
    gd_spi_eeprom_device[openParamsP->device]->wp   = wphandle;
    gd_spi_eeprom_device[openParamsP->device]->hold = holdhandle;
    if(wphandle)
    {
        GD_GPIO_Write(wphandle, 1);
    }
    if(holdhandle)
    {
        GD_GPIO_Write(holdhandle, 1);
    }

    gd_spi_eeprom_handle[openParamsP->device] = gd_spi_eeprom_device[openParamsP->device];
    *pHandle = (GD_HANDLE)(void*)gd_spi_eeprom_handle[openParamsP->device];

    return( GD_OK );
}

/*!
********************************************************************************
**
** \brief Closes a serial spi eeprom driver instance
**
** This function closes an open instance of the serial spi eeprom driver
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
GERR GD_SPI_EEPROM_Close( GD_HANDLE* pHandle)
{
    GD_SPI_EEPROM_DEV_S* device;

    if(!pHandle)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    device = (GD_SPI_EEPROM_DEV_S*)(*pHandle);
    if(device != gd_spi_eeprom_handle[device->device])
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    GD_SPI_Close(&gd_spi_eeprom_device[device->device]->spi);
    GD_GPIO_Close(&gd_spi_eeprom_device[device->device]->wp);
    GD_GPIO_Close(&gd_spi_eeprom_device[device->device]->hold);
    gd_spi_eeprom_device[device->device]->spi   = 0;
    gd_spi_eeprom_device[device->device]->wp    = 0;
    gd_spi_eeprom_device[device->device]->hold  = 0;
    gd_spi_eeprom_handle[device->device]        = NULL;
    *pHandle = 0;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Reads serial spi eeprom data by read mode
**  This function is called by GD_SPI_EEPROM_Read()
**
** \param handle  The handle describing an opened serial spi eeprom device
** \param address The address to start reading at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial spi eeprom device
** \param buffer  The adress of a data buffer where to store the read data
** \param words   The number of long words to read from the serial spi eeprom
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     spi eeprom memory
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Read(GD_HANDLE handle, U32 address, U8* buffer, U32 bytes)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);
    U8  spibuffer[3];
#if 0
    U32 cmdBitSet = 0;
    U32 startAddr, endAddr, startPage, endPage;
    U32 delays;
#endif
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if((address + bytes) > device->deviceBytes)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    while(bytes)
    {
        spibuffer[0] = device->commands->readData;
        spibuffer[1] = (U8)((address & 0xFF00) >> 8);
        spibuffer[2] = (U8)(address & 0x00FF);

        GD_SPI_WriteThenReadBytes(device->spi, &spibuffer[0], 0x03, buffer, 1);

        bytes--;
        address++;
        buffer++;
        //delays = 0x1000;
        //while(delays)
        //{
        //    delays--;
        //}
    }

    //GD_SPI_SetCE(device->spi, 1);
    //result = spi_eepromWipDoneWait(handle);

    //if(result != GD_OK)
    //    break;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Writes serial spi eeprom data
**
** This function writes data to the serial spi eeprom from the given data buffer.
** The function starts writing at the given byte address which should be long
** word aligned, internally this address will be masked by 0xFFFFFFFC.
**
** \param handle  The handle describing an opened serial spi eeprom device
** \param address The address to start writing at, this address must be
**                long word aligned and refers to a relative address inside
**                the serial spi eeprom device
** \param buffer  The adress of a data buffer where to read data from
** \param words   The number of long words to write into the serial spi eeprom
**                device
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given buffer parameter points to 0
** - GD_ERR_BAD_PARAMETER if the last address to read from is out of serial
**     spi eeprom memory
** - GD_OK if successfull
**
** \note This function assumes that the serial spi eeprom is ready to be get
**       written, it does not check whether the sectors to write to are
**       empty.
**
** \note This function acts as a low level serial spi eeprom write function
**       used by the more user friendly function GD_SPI_EEPROM_Program
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Write(GD_HANDLE handle, U32 address, U8* buffer, U32 bytes)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);
    U8  spibuffer[4];
    U8  RDSR;
#if 0
    U16 cmdBitSet = 0;
    U32 startAddr, endAddr, startPage, endPage;
    U32 delays;
#endif
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!buffer)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if((address + bytes) > device->deviceBytes)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    // all operation need cs 1-->0-->1
    while(bytes)
    {
        // wait to write end
        spibuffer[0] = device->commands->readStatus;
        spibuffer[1] = 0x00;
        do
        {
            GD_SPI_WriteThenReadBytes(device->spi, &spibuffer[0], 0x01, &RDSR, 0x01);
        }while(RDSR & 0x01);

        // every write opertion need writeEnable
        GD_SPI_WriteBytes(device->spi, &device->commands->writeEnable, 0x01);

        spibuffer[0] = device->commands->WriteData;
        spibuffer[1] = (U8)((address & 0xFF00) >> 8);
        spibuffer[2] = (U8)(address & 0x00FF);
        spibuffer[3] = *buffer;
        GD_SPI_WriteBytes(device->spi, &spibuffer[0], 0x04);
        bytes--;
        address++;
        buffer++;
        //delays = 0x1000;
        //while(delays)
        //{
        //    delays--;
        //}
    }

    GD_SPI_WriteBytes(device->spi, &device->commands->writeDisable, 0x01);

    //GD_SPI_SetCE(device->spi, 1);
    return GD_OK;
}

/*!
********************************************************************************
**
** \brief Retrieve manufactor name and device name
**
** This function returns the manufactor name and the device name of the serial
** spi eeprom device initialized by the function GD_SPI_EEPROM_Init().
**
** \param handle          The handle describing an opened serial spi eeprom device
** \param manufactureName The address of a string pointer variable where to
**                          write the address to the manufactor name into
** \param deviceName      The address of a string pointer variable where to
**                          write the address to the device name into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given manufactureName points to 0
** - GD_ERR_BAD_PARAMETER if the given deviceName points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetNames(GD_HANDLE handle, char** manufactureName, char** deviceName)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!manufactureName)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!deviceName)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *deviceName = device->deviceName;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the sector count
**
** This function returns the number of sectors of the serial
** spi eeprom device initialized by the function GD_SPI_EEPROM_Init().
**
** \param handle      The handle describing an opened serial spi eeprom device
** \param sectorCount The address of a variable where to write the resulting
**                      count into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorCount points to 0
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetNumberOfSectors(GD_HANDLE handle, U16* sectorCount)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sectorCount = device->sectorCount;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the start address of a sector
**
** This function returns the start address of the serial spi eeprom device sector
** given by sectorIndex.
**
** \param handle        The handle describing an opened serial spi eeprom device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorAddress The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorAddress points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex is out of range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetSectorAddress(GD_HANDLE handle, U16 sectorIndex, U32* sectorAddress)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!sectorAddress)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }
    *sectorAddress = sectorIndex * device->sectorBytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the size of a given sector in long words
**
** This function returns the size of the serial spi eeprom device sector
** given by sectorIndex. The returned value is in long words not in bytes.
**
** \param handle        The handle describing an opened serial spi eeprom device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorWords points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex is out of range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetSectorSize(GD_HANDLE handle, U16 sectorIndex, U32* sectorBytes)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(sectorIndex >= device->sectorCount)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorBytes)
        return(GD_ERR_BAD_PARAMETER);

    *sectorBytes = device->sectorBytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the sector index of a given serial spi eeprom address
**
** This function returns the sector index for the given serial spi eeprom address.
**
** \param handle        The handle describing an opened serial spi eeprom device
** \param sectorIndex   The index of the sector to find the start address of                     count into
** \param sectorWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex points to 0
** - GD_ERR_BAD_PARAMETER if the given address is out of the memory range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetSector(GD_HANDLE handle, U32 address, U16* sectorIndex)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(address >= device->deviceBytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    if(!sectorIndex)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *sectorIndex = address / device->sectorBytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief Retrieve the size of the serial spi eeprom device in long words
**
** This function returns the size of the serial spi eeprom device specified by the
** given handle. The size is returned in long words not in bytes.
**
** \param handle        The handle describing an opened serial spi eeprom device
** \param deviceWords   The address of a variable where to write the resulting
**                        address value into
**
** \return
** - GD_ERR_INVALID_HANDLE if the given pHandle parameter points to 0
** - GD_ERR_BAD_PARAMETER if the given sectorIndex points to 0
** - GD_ERR_BAD_PARAMETER if the given address is out of the memory range
** - GD_OK if successfull
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_GetSize(GD_HANDLE handle, U32* deviceBytes)
{
    GD_SPI_EEPROM_DEV_S* device = (GD_SPI_EEPROM_DEV_S*)(handle);

    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    if(!deviceBytes)
    {
        return(GD_ERR_BAD_PARAMETER);
    }

    *deviceBytes = device->deviceBytes;
    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief unlock the serial spi eeprom
**
** This function unlock the serial spi eeprom.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_OK if unlock operation successfully
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Unlock(GD_HANDLE handle)
{
    GD_SPI_EEPROM_DEV_S* device;
#if 0
    U32 command;
    U32 cmdBitSet = 0;
    U32 spi_eepromData = 0;
    U8 status1, status2 = 0;
    U32 CESetting = 0x0E;
#endif

    device = (GD_SPI_EEPROM_DEV_S*)(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    return(GD_OK);
}

/*!
********************************************************************************
**
** \brief lock the serial spi eeprom
**
** This function lock the serial spi eeprom.
**
** \return
** - GD_ERR_INVALID_HANDLE if the given handle parameter points to 0
** - GD_ERR_TIMEOUT if lock operation failed
** - GD_OK if lock operation successfully
**
********************************************************************************
*/
GERR GD_SPI_EEPROM_Lock(GD_HANDLE handle)
{
    GD_SPI_EEPROM_DEV_S* device;
#if 0
    U32 command     = 0;
    U32 address     = 0;
    U32 cmdBitSet   = 0;
    U32 spi_eepromData  = 0;
    U8 status1, status2 = 0;
    U8 i;
    U32 CESetting = 0x0E;
#endif

    device = (GD_SPI_EEPROM_DEV_S*)(handle);
    if(!device)
    {
        return(GD_ERR_INVALID_HANDLE);
    }

    return(GD_OK);
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

/*
*******************************************************************************
**
** spi_eepromWipDoneWait is used to wait until the WIP (write-in-progress)
** flag is cleared by the device.
**
*******************************************************************************
*/
#if 0
static GERR spi_eepromWipDoneWait(GD_HANDLE handle)
{
    return GD_OK;
}
#endif

