/******************************************************************************
**
** \file      gd_fe_rda5880h.c
**
** \brief     Front-end device driver for Goke rda5880h cable frontend.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_fe_tda18250.c,v 1.3 2013/06/04 06:56:00 Steven Yu Exp $
**
******************************************************************************/

//*--------------------------------------------------------------------------------------
//* Include Driver files
//*--------------------------------------------------------------------------------------
#include "gtypes.h"
#include "gd_sensor.h"
#include "ov2710_pri.h"

/*---------------------------------------------------------------------------*/
/* local Definitions                                                         */
/*---------------------------------------------------------------------------*/
#define OV2710_I2C_ADDR                0x6C

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static char             ov2710_name[30]="ov2710";
static GD_SENSOR_INFO_S info;

/*---------------------------------------------------------------------------*/
/* callback functions                                                        */
/*---------------------------------------------------------------------------*/
GERR GD_SENSOR_OV2710_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData);
GERR GD_SENSOR_OV2710_Close(GD_HANDLE* pHandle);
GERR GD_SENSOR_OV2710_Reset(GD_HANDLE* pHandle);
GERR GD_SENSOR_OV2710_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

/*---------------------------------------------------------------------------*/
/* extern functions                                                        */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/

//*--------------------------------------------------------------------------------------
//* Template of function to be provided by customer
//*--------------------------------------------------------------------------------------

/*---------------------------------------------------------------------------*/
/* call back functions                                                       */
/*---------------------------------------------------------------------------*/
GERR GD_SENSOR_OV2710_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData)
{
    if (pDeviceData == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if (pDeviceData->systemType != GD_SENSOR_SYSTEM_TYPE_OV2710)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    /* fill device data structure with call back functions */
    pDeviceData->sensorCloseFct = GD_SENSOR_OV2710_Close;
    pDeviceData->sensorResetFct = GD_SENSOR_OV2710_Reset;
    pDeviceData->sensorDoCmdFct = GD_SENSOR_OV2710_DoCmd;

    pDeviceData->pinfo          = (void*)&info;

    info.current_video_index    = -1;
    info.frame_rate             = GD_VIDEO_FPS_29_97;
    info.pll_index              = -1;
    info.bayer_pattern          = GD_VIN_SRC_BAYER_PATTERN_GR;
    info.min_agc_index          = 0;
    info.max_agc_index          = OV2710_GAIN_ROWS - 1;
    info.agc_info.db_max        = 0x24000000;    // 36dB
    info.agc_info.db_min        = 0x00000000;    // 0dB
    info.agc_info.db_step       = 0x00600000;    // 0.375dB

    return GD_OK;
}

GERR GD_SENSOR_OV2710_Close(GD_HANDLE* pHandle)
{
    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

GERR GD_SENSOR_OV2710_Reset(GD_HANDLE* pHandle)
{
    return GD_SENSOR_OV2710_DoCmd(pHandle, GD_VIN_SRC_RESET, NULL);
}

GERR GD_SENSOR_OV2710_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    return ov2710_docmd(pHandle, cmd, args);
}

GERR GD_SENSOR_DetectOpen_OV2710_parallel(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle)
{
    GERR err;
    pOpenParams->systemType     = GD_SENSOR_SYSTEM_TYPE_OV2710;
    pOpenParams->usei2c         = GTRUE;

    pOpenParams->i2cAddrSensor  = OV2710_I2C_ADDR;
    pOpenParams->sensorOpenFct  = GD_SENSOR_OV2710_Open;
    pOpenParams->name           = ov2710_name;

    err = GD_SENSOR_Open(pOpenParams, pHandle);

    return err;
}

GERR GD_SENSOR_Detect_OV2710_parallel(GD_I2C_OPEN_PARAMS_S* pI2COpenParams)
{
    GERR gerr = GD_OK;
    GD_HANDLE               I2C_handle;
    U8                      i2cBuffer[6];

    if (pI2COpenParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    GD_I2C_SetOperationMode(pI2COpenParams->channel, GD_I2C_AUTO_MASTER_MODE);
    gerr = GD_I2C_Open(pI2COpenParams, &I2C_handle);
    if (gerr != GD_OK)
    {
        return GD_ERR_SENSOR_I2C;
    }
    GD_I2C_SetProtocol(&I2C_handle, GD_I2C_RESTART_PROTOCOL);
    {
        i2cBuffer[0] = (OV2710_PIDH >> 8) & 0xff;
        i2cBuffer[1] = (OV2710_PIDH & 0xff);
        i2cBuffer[2] = 0xFF;
        i2cBuffer[3] = (OV2710_PIDL >> 8);
        i2cBuffer[4] = (OV2710_PIDL & 0xff) & 0xff;
        i2cBuffer[5] = 0xFF;

        gerr = GD_I2C_Read(&I2C_handle, OV2710_I2C_ADDR, &(i2cBuffer[0]), 2, &(i2cBuffer[2]), 1);
        if(gerr == GD_OK)
        {
            gerr = GD_I2C_Read(&I2C_handle, OV2710_I2C_ADDR, &(i2cBuffer[3]), 2, &(i2cBuffer[5]), 1);
            if(gerr == GD_OK)
            {
                if((i2cBuffer[2] == 0x27) && (i2cBuffer[5] == 0x10))
                {
                    gerr = GD_OK;
                }
                else
                {
                    gerr = GD_ERR_FEATURE_NOT_SUPPORTED;
                }
            }
        }
    }

    GD_I2C_Close(&I2C_handle);
    return gerr;
}

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/

/* Version History */
/******************************************************************************


******************************************************************************/
