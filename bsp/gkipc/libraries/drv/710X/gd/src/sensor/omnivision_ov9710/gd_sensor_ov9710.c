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
#include "ov9710_pri.h"

/*---------------------------------------------------------------------------*/
/* local Definitions                                                         */
/*---------------------------------------------------------------------------*/
#define OV9710_I2C_ADDR                0x60

/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static char             ov9710_name[30]="ov9710";
static GD_SENSOR_INFO_S info;

/*---------------------------------------------------------------------------*/
/* callback functions                                                        */
/*---------------------------------------------------------------------------*/
GERR GD_SENSOR_OV9710_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData);
GERR GD_SENSOR_OV9710_Close(GD_HANDLE* pHandle);
GERR GD_SENSOR_OV9710_Reset(GD_HANDLE* pHandle);
GERR GD_SENSOR_OV9710_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

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
GERR GD_SENSOR_OV9710_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData)
{
    if (pDeviceData == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if (pDeviceData->systemType != GD_SENSOR_SYSTEM_TYPE_OV9710)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    /* fill device data structure with call back functions */
    pDeviceData->sensorCloseFct = GD_SENSOR_OV9710_Close;
    pDeviceData->sensorResetFct = GD_SENSOR_OV9710_Reset;
    pDeviceData->sensorDoCmdFct = GD_SENSOR_OV9710_DoCmd;

    pDeviceData->pinfo          = (void*)&info;

    info.current_video_index    = -1;
    info.frame_rate             = GD_VIDEO_FPS_AUTO;
    info.pll_index              = -1;
    info.bayer_pattern          = GD_VIN_SRC_BAYER_PATTERN_BG;
    info.mirror_pattern         = GD_VIN_SRC_MIRROR_NONE;
    info.min_agc_index          = 0;
    info.max_agc_index          = OV9710_GAIN_ROWS - 1;
    info.agc_info.db_max        = 0x1e000000;    // 30dB
    info.agc_info.db_min        = 0x00000000;    // 0dB
    info.agc_info.db_step       = 0x00600000;    // 0.375dB

    return GD_OK;
}

GERR GD_SENSOR_OV9710_Close(GD_HANDLE* pHandle)
{
    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

GERR GD_SENSOR_OV9710_Reset(GD_HANDLE* pHandle)
{
    return GD_SENSOR_OV9710_DoCmd(pHandle, GD_VIN_SRC_RESET, NULL);
}

GERR GD_SENSOR_OV9710_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    return ov9710_docmd(pHandle, cmd, args);
}

GERR GD_SENSOR_DetectOpen_OV9710(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle)
{
    GERR err;
    pOpenParams->systemType     = GD_SENSOR_SYSTEM_TYPE_OV9710;
    pOpenParams->usei2c         = GTRUE;

    pOpenParams->i2cAddrSensor  = OV9710_I2C_ADDR;
    pOpenParams->sensorOpenFct  = GD_SENSOR_OV9710_Open;
    pOpenParams->name           = ov9710_name;

    err = GD_SENSOR_Open(pOpenParams, pHandle);

    return err;
}

GERR GD_SENSOR_Detect_OV9710(GD_I2C_OPEN_PARAMS_S* pI2COpenParams)
{
    GERR gerr = GD_OK;
    GD_HANDLE               I2C_handle;
    U8                      i2cBuffer[4];

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
        i2cBuffer[0] = OV9710_PIDH;
        i2cBuffer[1] = 0xFF;
        i2cBuffer[2] = OV9710_PIDL;

        gerr = GD_I2C_Read(&I2C_handle, OV9710_I2C_ADDR, &(i2cBuffer[0]), 1, &(i2cBuffer[1]), 1);
        if(gerr == GD_OK)
        {
            gerr = GD_I2C_Read(&I2C_handle, OV9710_I2C_ADDR, &(i2cBuffer[2]), 1, &(i2cBuffer[3]), 1);
            if(gerr == GD_OK)
            {
                if((i2cBuffer[1] == 0x97) && (i2cBuffer[2] == 0x10))
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
