/*!
*****************************************************************************
** \file        gd_lib/GK7101/inc/gd_spieeprom.h
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
#ifndef _GD_SPIEEPROM_H_
#define _GD_SPIEEPROM_H_


#include <gtypes.h>
#include <gmodids.h>
#include "gd_gpio.h"
#include "gd_spi.h"


//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
typedef enum
{
    GD_SPI_EEPROM_AT25320B = 0,
    GD_SPI_EEPROM_AT25640B,
    GD_SPI_EEPROM_NUM
}GD_SPI_EEPROM_E;

/*!
*******************************************************************************
**
** \anchor
** \brief he base error code for the serial spi eeprom device driver.
**
*******************************************************************************
*/
#define GD_SPI_EEPROM_ERR_BASE (GD_SPI_EEPROM_MODULE_ID<<16)

/*!
*******************************************************************************
**
** \brief Flash driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_SPI_EEPROM_TYPE_NOT_SUPPORTED = GD_SPI_EEPROM_ERR_BASE, //!< Device not supported.
    GD_ERR_SPI_EEPROM_IN_USE,                                  //!< Read error.
    GD_ERR_SPI_EEPROM_READ,                                    //!< Read error.
    GD_ERR_SPI_EEPROM_WRITE,                                   //!< Write error.
};


//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
/*
*******************************************************************************
**
** serial spi eeprom specific commands and statis register bit definitions
**
*******************************************************************************
*/
typedef struct
{
    U8  writeEnable;   // command to WREN  Set Write Enable Latch
    U8  writeDisable;  // command to WRDI  Reset Write Enable Latch
    U8  readStatus;    // command to RDSR  Read Status Register
    U8  writeStatus;   // command to WRSR  Write Status Register
    U8  readData;      // command to READ  Read Data from Memory Array
    U8  WriteData;     // command to WRITE Write Data to Memory Array
}GD_SPI_EEPROM_CMD_S;

/*
*******************************************************************************
**
** serial spi eeprom specific geometry and information data structure
**
*******************************************************************************
*/
typedef struct
{
    char*            manufactureName; // Pointer to manufacture name
    char*            deviceName;      // Pointer to device name
    U32              deviceBytes;     // Size of spi eeprom device in bytes
    U32              sectorCount;     // Number of sectors
    U32              sectorBytes;     // Size of a single sector in bytes
    GD_SPI_EEPROM_CMD_S* commands;    // Device specific access commands
    GBOOL            wptoporbottom;
    GD_SPI_EEPROM_E  device;
    GD_HANDLE        spi;
    GD_HANDLE        wp;
    GD_HANDLE        hold;
}GD_SPI_EEPROM_DEV_S;

typedef struct
{
    GD_SPI_EEPROM_E         device;
    GD_SPI_CHANNEL_E        channel;
    GD_SPI_SLAVE_E          slave;
    GD_SPI_SPEED_MODE       speed;
    GD_SPI_POLARITY_MODE    polarity;
    GBOOL                   used_irq;
    GD_GPIO_PIN_E           csgpiopin;
    GD_GPIO_TYPE_E          csgpiotype;
    GD_GPIO_PIN_E           wpgpiopin;
    GD_GPIO_TYPE_E          wpgpiotype;
    GD_GPIO_PIN_E           holdgpiopin;
    GD_GPIO_TYPE_E          holdgpiotype;
} GD_SPI_EEPROM_OPEN_PARAMS_S;



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif

GERR GD_SPI_EEPROM_Init(void);
GERR GD_SPI_EEPROM_Exit(void);
GERR GD_SPI_EEPROM_Open(GD_SPI_EEPROM_OPEN_PARAMS_S *openParamsP, GD_HANDLE* pHandle);
GERR GD_SPI_EEPROM_Close(GD_HANDLE* pHandle);
GERR GD_SPI_EEPROM_Read(GD_HANDLE handle, U32 address, U8* buffer, U32 bytes);
GERR GD_SPI_EEPROM_Write(GD_HANDLE handle, U32 address, U8* buffer, U32 bytes);
GERR GD_SPI_EEPROM_GetNames(GD_HANDLE handle, char** manufactureName, char** deviceName);
GERR GD_SPI_EEPROM_GetNumberOfSectors(GD_HANDLE handle, U16* numberOfSectors);
GERR GD_SPI_EEPROM_GetSectorAddress(GD_HANDLE handle, U16 sector, U32* address);
GERR GD_SPI_EEPROM_GetSize(GD_HANDLE handle, U32* deviceBytes);
GERR GD_SPI_EEPROM_GetSectorSize(GD_HANDLE handle, U16 sector, U32* deviceBytes);
GERR GD_SPI_EEPROM_GetSector(GD_HANDLE handle, U32 address, U16* sector);
GERR GD_SPI_EEPROM_Unlock(GD_HANDLE handle);
GERR GD_SPI_EEPROM_Lock(GD_HANDLE handle);

#ifdef __cplusplus
}
#endif



#endif /* _GD_SPIEEPROM_H_ */

