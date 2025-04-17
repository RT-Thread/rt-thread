/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mipi_dsi_cmd.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t MIPI_DSI_DCS_SoftReset(mipi_dsi_device_t *device)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData         = (uint8_t)kMIPI_DCS_SoftReset;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_SetDisplayOn(mipi_dsi_device_t *device, bool on)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    if (on)
    {
        txData = (uint8_t)kMIPI_DCS_SetDisplayOn;
    }
    else
    {
        txData = (uint8_t)kMIPI_DCS_SetDisplayOff;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_SetPixelFormat(mipi_dsi_device_t *device,
                                     mipi_dsc_pixel_format_t dbiFormat,
                                     mipi_dsc_pixel_format_t dpiFormat)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData[2];

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrOneParam;
    dsiXfer.txDataSize     = 2;
    dsiXfer.txData         = txData;

    txData[0] = (uint8_t)kMIPI_DCS_SetPixelFormat;
    txData[1] = ((uint8_t)dbiFormat << 0U) | ((uint8_t)dpiFormat << 4U);

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_EnterSleepMode(mipi_dsi_device_t *device, bool enter)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    if (enter)
    {
        txData = (uint8_t)kMIPI_DCS_EnterSleepMode;
    }
    else
    {
        txData = (uint8_t)kMIPI_DCS_ExitSleepMode;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_EnterPartialMode(mipi_dsi_device_t *device, bool enter)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    if (enter)
    {
        txData = (uint8_t)kMIPI_DCS_EnterPartialMode;
    }
    else
    {
        txData = (uint8_t)kMIPI_DCS_EnterNormalMode;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_EnterInvertMode(mipi_dsi_device_t *device, bool enter)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    if (enter)
    {
        txData = (uint8_t)kMIPI_DCS_EnterInvertMode;
    }
    else
    {
        txData = (uint8_t)kMIPI_DCS_ExitInvertMode;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_EnterIdleMode(mipi_dsi_device_t *device, bool enter)
{
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData;

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsShortWrNoParam;
    dsiXfer.txDataSize     = 1;
    dsiXfer.txData         = &txData;

    if (enter)
    {
        txData = (uint8_t)kMIPI_DCS_EnterIdleMode;
    }
    else
    {
        txData = (uint8_t)kMIPI_DCS_ExitIdleMode;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_Write(mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize)
{
    dsi_transfer_t dsiXfer = {0};

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataSize     = (uint16_t)txDataSize;
    dsiXfer.txData         = txData;

    if (0 == txDataSize)
    {
        /* For DSC command, the data size should not be 0. */
        return kStatus_InvalidArgument;
    }
    else if (1 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataDcsShortWrNoParam;
    }
    else if (2 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataDcsShortWrOneParam;
    }
    else
    {
        dsiXfer.txDataType = kDSI_TxDataDcsLongWr;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_GenericWrite(mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize)
{
    dsi_transfer_t dsiXfer = {0};

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataSize     = (uint16_t)txDataSize;
    dsiXfer.txData         = txData;

    if (0 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrNoParam;
    }
    else if (1 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrOneParam;
    }
    else if (2 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortWrTwoParam;
    }
    else
    {
        dsiXfer.txDataType = kDSI_TxDataGenLongWr;
    }

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_DCS_SetMaxReturnPktSize(mipi_dsi_device_t *device, uint16_t sizeBytes)
{
    dsi_transfer_t dsiXfer = {0};

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataSetMaxReturnPktSize;
    dsiXfer.txDataSize     = 2;
    dsiXfer.txData         = (uint8_t *)&sizeBytes;

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_GenericRead(
    mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize, uint8_t *rxData, int32_t *rxDataSize)
{
    status_t status;
    dsi_transfer_t dsiXfer = {0};

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataSize     = (uint16_t)txDataSize;
    dsiXfer.txData         = txData;
    dsiXfer.rxDataSize     = (uint16_t)*rxDataSize;
    dsiXfer.rxData         = rxData;

    *rxDataSize = 0;

    if (0 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortRdNoParam;
    }
    else if (1 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortRdOneParam;
    }
    else if (2 == txDataSize)
    {
        dsiXfer.txDataType = kDSI_TxDataGenShortRdTwoParam;
    }
    else
    {
        return kStatus_InvalidArgument;
    }

    status = device->xferFunc(&dsiXfer);

    /* Return actual received size. */
    *rxDataSize = (int32_t)dsiXfer.rxDataSize;

    return status;
}

status_t MIPI_DSI_ReadCMD(mipi_dsi_device_t *device, enum _mipi_dcs dcsCmd, uint8_t *rxData, int32_t *rxDataSize)
{
    uint8_t txData[2];
    status_t status = kStatus_Fail;

    txData[0] = (uint8_t)dcsCmd;
    if (kStatus_Success == MIPI_DSI_DCS_SetMaxReturnPktSize(device, (uint16_t)*rxDataSize))
    {
        status = MIPI_DSI_GenericRead(device, txData, 1, rxData, rxDataSize);
    }

    return status;
}

status_t MIPI_DSI_SelectArea(mipi_dsi_device_t *device, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY)
{
    status_t status;
    dsi_transfer_t dsiXfer = {0};
    uint8_t txData[4];

    dsiXfer.virtualChannel = device->virtualChannel;
    dsiXfer.txDataType     = kDSI_TxDataDcsLongWr;
    dsiXfer.txDataSize     = 4;
    dsiXfer.txData         = txData;
    dsiXfer.sendDscCmd     = true;
    dsiXfer.dscCmd         = (uint8_t)kMIPI_DCS_SetColumnAddress;

    txData[0] = (uint8_t)((startX >> 8U) & 0xFFU);
    txData[1] = (uint8_t)(startX & 0xFFU);
    txData[2] = (uint8_t)((endX >> 8U) & 0xFFU);
    txData[3] = (uint8_t)(endX & 0xFFU);

    status = device->xferFunc(&dsiXfer);

    if (kStatus_Success != status)
    {
        return status;
    }

    dsiXfer.dscCmd = (uint8_t)kMIPI_DCS_SetPageAddress;
    txData[0]      = (uint8_t)((startY >> 8U) & 0xFFU);
    txData[1]      = (uint8_t)(startY & 0xFFU);
    txData[2]      = (uint8_t)((endY >> 8U) & 0xFFU);
    txData[3]      = (uint8_t)(endY & 0xFFU);

    return device->xferFunc(&dsiXfer);
}

status_t MIPI_DSI_WriteMemory(mipi_dsi_device_t *device, const uint8_t *data, uint32_t length)
{
    return device->memWriteFunc(device->virtualChannel, data, length);
}

status_t MIPI_DSI_WriteMemory2D(
    mipi_dsi_device_t *device, const uint8_t *data, uint32_t minorLoop, uint32_t minorLoopOffset, uint32_t majorLoop)
{
    if (device->memWriteFunc2D != NULL)
    {
        return device->memWriteFunc2D(device->virtualChannel, data, minorLoop, minorLoopOffset, majorLoop);
    }
    else
    {
        return kStatus_Fail;
    }
}

void MIPI_DSI_SetMemoryDoneCallback(mipi_dsi_device_t *device, mipi_dsi_mem_done_callback_t callback, void *userData)
{
    device->callback = callback;
    device->userData = userData;
}

void MIPI_DSI_MemoryDoneDriverCallback(status_t status, void *userData)
{
    mipi_dsi_device_t *device = (mipi_dsi_device_t *)userData;

    if (NULL != device->callback)
    {
        device->callback(status, device->userData);
    }
}
