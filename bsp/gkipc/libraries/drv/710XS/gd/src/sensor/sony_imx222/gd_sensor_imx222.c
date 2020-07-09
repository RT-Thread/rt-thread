/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/sony_imx222/gd_sensor_imx222.c
**
** \version     $Id: gd_sensor_imx222.c 330 2014-12-04 03:07:34Z yulindeng $
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/


//*--------------------------------------------------------------------------------------
//* Include Driver files
//*--------------------------------------------------------------------------------------
#include "gtypes.h"
#include "gd_sensor.h"
#include "imx222_pri.h"
#include "gd_spi.h"

/*---------------------------------------------------------------------------*/
/* local Definitions                                                         */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static char             imx222_name[30]="spidev-imx122";
static GD_SENSOR_INFO_S info;

/*---------------------------------------------------------------------------*/
/* callback functions                                                        */
/*---------------------------------------------------------------------------*/
GERR GD_SENSOR_IMX222_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData);
GERR GD_SENSOR_IMX222_Close(GD_HANDLE* pHandle);
GERR GD_SENSOR_IMX222_Reset(GD_HANDLE* pHandle);
GERR GD_SENSOR_IMX222_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

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
GERR GD_SENSOR_IMX222_Open(GD_SENSOR_DEVICE_DATA_S* pDeviceData)
{
    if (pDeviceData == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    if (pDeviceData->systemType != GD_SENSOR_SYSTEM_TYPE_SONYIMX222)
    {
        return GD_ERR_BAD_PARAMETER;
    }

    /* fill device data structure with call back functions */
    pDeviceData->sensorCloseFct = GD_SENSOR_IMX222_Close;
    pDeviceData->sensorResetFct = GD_SENSOR_IMX222_Reset;
    pDeviceData->sensorDoCmdFct = GD_SENSOR_IMX222_DoCmd;

    pDeviceData->pinfo          = (void*)&info;

    info.current_video_index    = -1;
    info.frame_rate             = GD_VIDEO_FPS_29_97;
    info.pll_index              = -1;
    info.bayer_pattern          = GD_VIN_SRC_BAYER_PATTERN_GR;//GD_VIN_SRC_BAYER_PATTERN_GB
    info.min_agc_index          = 0;
    info.max_agc_index          = IMX222_GAIN_ROWS - 1;
    info.agc_info.db_max        = 0x2A000000;    // 42dB
    info.agc_info.db_min        = 0x00000000;    // 0dB
    info.agc_info.db_step       = 0x004CCCCD;    // 0.3dB

    return GD_OK;
}

GERR GD_SENSOR_IMX222_Close(GD_HANDLE* pHandle)
{
    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    return GD_OK;
}

GERR GD_SENSOR_IMX222_Reset(GD_HANDLE* pHandle)
{
    return GD_SENSOR_IMX222_DoCmd(pHandle, GD_VIN_SRC_RESET, NULL);
}

GERR GD_SENSOR_IMX222_DoCmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    return imx222_docmd(pHandle, cmd, args);
}

GERR GD_SENSOR_DetectOpen_IMX222(GD_SENSOR_OPEN_PARAMS_S* pOpenParams, GD_HANDLE* pHandle)
{
    GERR err;
    pOpenParams->systemType     = GD_SENSOR_SYSTEM_TYPE_SONYIMX222;
    pOpenParams->usei2c         = GFALSE;

    pOpenParams->sensorOpenFct  = GD_SENSOR_IMX222_Open;
    pOpenParams->name           = imx222_name;

    err = GD_SENSOR_Open(pOpenParams, pHandle);

    return err;
}

GERR GD_SENSOR_Detect_IMX222(GD_SPI_OPEN_PARAMS_S* pSPIOpenParams)
{
    GERR gerr = GD_OK;
    GD_HANDLE               SPI_handle;
    U8                      spiBuffer[6];
    if (pSPIOpenParams == NULL)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    gerr = GD_SPI_Open(pSPIOpenParams, &SPI_handle);
    if (gerr != GD_OK)
    {
        return GD_ERR_SENSOR_SPI;
    }
    // 0x82 04
    spiBuffer[0] = 0x41;//((IMX222_HMAX_MSB >> 8) & 0xff) | 0x80;
    spiBuffer[1] = 0x20;//(IMX222_HMAX_MSB & 0xff);
    spiBuffer[2] = 0x00;//(IMX222_HMAX_MSB & 0xff);
    gerr = GD_SPI_WriteThenReadBytes(SPI_handle, &spiBuffer[0], 2, &spiBuffer[3], 1);
    if(gerr == GD_OK)
    {
        if((spiBuffer[3] == 0x00) || (spiBuffer[3] == 0xFF))
        {
            gerr = GD_ERR_NO_DEVICE_DETECT;
        }
    }
    GD_SPI_Close(&SPI_handle);
    return gerr;
}

/*---------------------------------------------------------------------------*/
/* local functions                                                           */
/*---------------------------------------------------------------------------*/

/* Version History */
/******************************************************************************


******************************************************************************/
