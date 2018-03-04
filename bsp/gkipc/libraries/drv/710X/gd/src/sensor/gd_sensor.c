/******************************************************************************
**
** \file      gd_sensor.c
**
** \brief     Generic sensor driver.
**
**            (C) Goke Microelectronics China 2002 - 2014
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_sensor.c, v1.00 2014/07/14 08:13:54 $
**
******************************************************************************/
/*---------------------------------------------------------------------------*/
/* configuration                                                             */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* include files                                                             */
/*---------------------------------------------------------------------------*/
#include "gtypes.h"
#include "gd_sensor.h"
#include "gd_gpio.h"

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static GBOOL                    initialized = GFALSE;
static GD_HANDLE                handle;
static GD_SENSOR_DEVICE_DATA_S  device;
static GD_I2C_OPEN_PARAMS_S     I2C_Open_para = {0};
static GD_SPI_OPEN_PARAMS_S     SPI_Open_para = {0};

static void deviceClear(void)
{
    device.sensorDoCmdFct = NULL;
    device.sensorCloseFct = NULL;
    device.sensorResetFct = NULL;
    device.resetGPIO      = NULL;
    device.powerGPIO      = NULL;
    device.handleI2C      = NULL;
}
/*!
*******************************************************************************
**
** \brief  Inits the sensor driver.
**
**         This function has to be called during boot-up of the system.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_ALREADY_INITIALIZED
**
** \sa     GD_SENSOR_Open()
**
******************************************************************************/
GERR GD_SENSOR_Init(void)
{
    if (initialized == GTRUE)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    handle = (GD_HANDLE)0;
    deviceClear();
    initialized = GTRUE;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Opens a sensor instance.
**
** \param  pOpenParams  Pointer to open parameters.
** \param  pHandle      Pointer to handle which will be filled if the
**                      sensor could be opened successfully.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_NOT_INITIALIZED
**         - #GD_ERR_BAD_PARAMETER
**         - #GD_ERR_ALREADY_OPEN
**         - #GD_ERR_SENSOR_GPIO
**         - #GD_ERR_SENSOR_I2C
**
** \sa     GD_SENSOR_Close()
**
******************************************************************************/
GERR GD_SENSOR_Open(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle)
{
    GERR   gerr;

    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    /* check parameters for dummy sensor */

    if(pOpenParams->usei2c)
    {
        /* open I2C channel */
        if (pOpenParams->pI2COpenParams == NULL)
        {
            pOpenParams->pI2COpenParams = &I2C_Open_para;
            // use default
            pOpenParams->pI2COpenParams->channel    = GD_I2C_CHANNEL_ONE;
            pOpenParams->pI2COpenParams->speed      = GD_I2C_100KBPS; // GD_I2C_400KBPS;
            pOpenParams->pI2COpenParams->mode       = GD_I2C_INTERRUPT;
        }
        GD_I2C_SetOperationMode(pOpenParams->pI2COpenParams->channel,GD_I2C_AUTO_MASTER_MODE);
        gerr = GD_I2C_Open(pOpenParams->pI2COpenParams, &(device.handleI2C));
        if ((gerr != GD_OK) && (gerr != GD_ERR_ALREADY_OPEN))
        {
            return GD_ERR_SENSOR_I2C;
        }
        GD_I2C_SetProtocol(&(device.handleI2C),GD_I2C_RESTART_PROTOCOL);
    }
    else
    {
        /* open SPI channel */
        if (pOpenParams->pSPIOpenParams == NULL)
        {
            pOpenParams->pSPIOpenParams = & SPI_Open_para;
            // use default
            pOpenParams->pSPIOpenParams->spi         = GD_SPI_CHANNEL_0;
            pOpenParams->pSPIOpenParams->slave       = GD_SPI_SLAVE0;
            pOpenParams->pSPIOpenParams->baudrate    = GD_SPI_FREQ_10M;
        }
        gerr = GD_SPI_Open(pOpenParams->pSPIOpenParams, &(device.handleSPI));
        if ((gerr != GD_OK) && (gerr != GD_ERR_ALREADY_OPEN))
        {
            return GD_ERR_SENSOR_SPI;
        }
    }

    if (pOpenParams->resetGPIO < GD_GPIO_NUM)
    {
        GD_GPIO_Open(pOpenParams->resetGPIO,
            GD_GPIO_TYPE_OUTPUT_1, NULL, &(device.resetGPIO));
    }
    else
    {
        device.resetGPIO = (GD_HANDLE)0;
    }

    if (pOpenParams->powerGPIO < GD_GPIO_NUM)
    {
        GD_GPIO_Open(pOpenParams->powerGPIO,
            GD_GPIO_TYPE_OUTPUT_1, NULL, &(device.powerGPIO));
    }
    else
    {
        device.powerGPIO = (GD_HANDLE)0;
    }

    /* copy data from open parameters */
    device.i2cAddrSensor = pOpenParams->i2cAddrSensor;
    device.systemType    = pOpenParams->systemType;
    device.name          = pOpenParams->name;

    /* call open function */
    gerr = GD_OK;
    if (pOpenParams->sensorOpenFct == NULL)
    {
        deviceClear();
        gerr = GD_ERR_BAD_PARAMETER;
    }
    else
    {
        /* open custom driver */
        gerr = pOpenParams->sensorOpenFct(&device);
    }

    if (gerr != GD_OK)
    {
        if (device.handleI2C != (GD_HANDLE)0)
        {
            GD_I2C_Close(&(device.handleI2C));
        }
        if (device.resetGPIO != (GD_HANDLE)0)
        {
            GD_GPIO_Close(&(device.resetGPIO));
        }
        if (device.powerGPIO != (GD_HANDLE)0)
        {
            GD_GPIO_Close(&(device.powerGPIO));
        }
        deviceClear();
        return gerr;
    }

    /* create handle */
    handle = (GD_HANDLE)(&device);
    *pHandle = handle;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Closes a sensor instance.
**
** \param  pHandle  Pointer to handle which will be set to null.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_NOT_INITIALIZED
**         - #GD_ERR_INVALID_HANDLE
**         - #GD_ERR_BAD_PARAMETER
**
** \sa     GD_SENSOR_Open()
**
******************************************************************************/
GERR GD_SENSOR_Close(GD_HANDLE* pHandle)
{
    GERR gerr;

    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    /* call close function if any */
    if (device.sensorCloseFct != NULL)
    {
        gerr = device.sensorCloseFct(pHandle);
        if (gerr != GD_OK)
        {
            return gerr;
        }
    }

    /* close I2C */
    if (device.handleI2C != (GD_HANDLE)0)
    {
        GD_I2C_Close(&(device.handleI2C));
    }
    if (device.resetGPIO != (GD_HANDLE)0)
    {
        GD_GPIO_Close(&(device.resetGPIO));
    }
    if (device.powerGPIO != (GD_HANDLE)0)
    {
        GD_GPIO_Close(&(device.powerGPIO));
    }
    deviceClear();

    /* reset handle */
    handle = (GD_HANDLE)0;
    *pHandle = (GD_HANDLE)0;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Resets the sensor.
**
** \param  handle  Handle of sensor to reset.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_NOT_INITIALIZED
**         - #GD_ERR_INVALID_HANDLE
**         - #GD_ERR_FEATURE_NOT_SUPPORTED
**         - #GD_ERR_BAD_PARAMETER
**
******************************************************************************/
GERR GD_SENSOR_Reset(GD_HANDLE* pHandle)
{
    GERR gerr;

    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device.sensorResetFct != NULL)
    {
        gerr = device.sensorResetFct(pHandle);
    }
    else
    {
        gerr = GD_ERR_FEATURE_NOT_SUPPORTED;
    }
    return gerr;
}

GERR GD_SENSOR_Sleep(U32 nMesc)
{
    U32 i,j;
    for (i=0; i<nMesc; i++)
    {
        for (j=0; j<0x100; j++)
        {
            ;
        }
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Resets the sensor.
**
** \param  handle  Handle of sensor to reset.
**
** \return Possible return codes:
**         - #GD_OK
**         - #GD_ERR_NOT_INITIALIZED
**         - #GD_ERR_INVALID_HANDLE
**         - #GD_ERR_FEATURE_NOT_SUPPORTED
**         - #GD_ERR_BAD_PARAMETER
**
******************************************************************************/
GERR GD_SENSOR_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    GERR gerr;

    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    if (device.sensorDoCmdFct != NULL)
    {
        gerr = device.sensorDoCmdFct(pHandle, cmd, args);
    }
    else
    {
        gerr = GD_ERR_FEATURE_NOT_SUPPORTED;
    }
    return gerr;
}

/* Version History */
/******************************************************************************


******************************************************************************/
