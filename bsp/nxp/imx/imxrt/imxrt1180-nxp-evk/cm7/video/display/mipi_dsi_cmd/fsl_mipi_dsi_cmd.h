/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MIPI_DSI_CMD_H_
#define _FSL_MIPI_DSI_CMD_H_

#include "fsl_common.h"
#include "fsl_mipi_dsi.h"

/*
 * Change log:
 *
 *   1.0.2
 *     - Fix MISRA-C 2012 issues.
 *
 *   1.0.1
 *     - Add more functions for panel works in command mode.
 *
 *   1.0.0
 *     - Initial version
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

enum _mipi_dcs
{
    kMIPI_DCS_Nop                  = 0x00,
    kMIPI_DCS_SoftReset            = 0x01,
    kMIPI_DCS_GetRedChannel        = 0x06,
    kMIPI_DCS_GetGreenChannel      = 0x07,
    kMIPI_DCS_GetBlueChannel       = 0x08,
    kMIPI_DCS_GetPowerMode         = 0x0A,
    kMIPI_DCS_GetAddressMode       = 0x0B,
    kMIPI_DCS_GetPixelFormat       = 0x0C,
    kMIPI_DCS_GetDisplayMode       = 0x0D,
    kMIPI_DCS_GetSignalMode        = 0x0E,
    kMIPI_DCS_GetDiagnosticResult  = 0x0F,
    kMIPI_DCS_EnterSleepMode       = 0x10,
    kMIPI_DCS_ExitSleepMode        = 0x11,
    kMIPI_DCS_EnterPartialMode     = 0x12,
    kMIPI_DCS_EnterNormalMode      = 0x13,
    kMIPI_DCS_ExitInvertMode       = 0x20,
    kMIPI_DCS_EnterInvertMode      = 0x21,
    kMIPI_DCS_SetGammaCurve        = 0x26,
    kMIPI_DCS_SetDisplayOff        = 0x28,
    kMIPI_DCS_SetDisplayOn         = 0x29,
    kMIPI_DCS_SetColumnAddress     = 0x2a,
    kMIPI_DCS_SetPageAddress       = 0x2b,
    kMIPI_DCS_WriteMemoryStart     = 0x2C,
    kMIPI_DCS_WriteLUT             = 0x2D,
    kMIPI_DCS_ReadMemoryStart      = 0x2E,
    kMIPI_DCS_SetPartialRows       = 0x30,
    kMIPI_DCS_SetPartialColumns    = 0x31,
    kMIPI_DCS_SetScrollArea        = 0x33,
    kMIPI_DCS_SetTearOff           = 0x34,
    kMIPI_DCS_SetTearOn            = 0x35,
    kMIPI_DCS_SetAddressMode       = 0x36,
    kMIPI_DCS_SetScrollStart       = 0x37,
    kMIPI_DCS_ExitIdleMode         = 0x38,
    kMIPI_DCS_EnterIdleMode        = 0x39,
    kMIPI_DCS_SetPixelFormat       = 0x3A,
    kMIPI_DCS_WriteMemoryContinue  = 0x3C,
    kMIPI_DCS_Set3DControl         = 0x3D,
    kMIPI_DCS_ReadMemoryContinue   = 0x3E,
    kMIPI_DCS_Get3DControl         = 0x3F,
    kMIPI_DCS_SetVsyncTiming       = 0x40,
    kMIPI_DCS_SetTearScanline      = 0x44,
    kMIPI_DCS_GetScanline          = 0x45,
    kMIPI_DCS_SetDisplayBrightness = 0x51,
    kMIPI_DCS_GetDisplayBrightness = 0x52,
    kMIPI_DCS_WriteControlDisplay  = 0x53,
    kMIPI_DCS_GetControlDisplay    = 0x54,
    kMIPI_DCS_WritePowerSave       = 0x55,
    kMIPI_DCS_GetPowerSave         = 0x56,
    kMIPI_DCS_SetCABCMinBrightness = 0x5E,
    kMIPI_DCS_GetCABCMinBrightness = 0x5F,
    kMIPI_DCS_ReadDDBStart         = 0xA1,
    kMIPI_DCS_ReadDDBContinue      = 0xA8,
};

/*!
 * @brief Pixel format used by DSC command.
 */
typedef enum _mipi_dsc_pixel_format
{
    kMIPI_DCS_Pixel3Bits  = 1U, /*!< 3-bit per pixel. */
    kMIPI_DCS_Pixel8Bits  = 2U, /*!< 8-bit per pixel. */
    kMIPI_DCS_Pixel12Bits = 3U, /*!< 12-bit per pixel. */
    kMIPI_DCS_Pixel16Bits = 5U, /*!< 16-bit per pixel. */
    kMIPI_DCS_Pixel18Bits = 6U, /*!< 18-bit per pixel. */
    kMIPI_DCS_Pixel24Bits = 7U, /*!< 24-bit per pixel. */
} mipi_dsc_pixel_format_t;

/*!
 * @brief Callback function when the write memory finished.
 *
 * If transfer done successfully, the @p status is kStatus_Success.
 */
typedef void (*mipi_dsi_mem_done_callback_t)(status_t status, void *userData);

/*! @brief MIPI DSI transfer function. */
typedef status_t (*mipi_dsi_transfer_func_t)(dsi_transfer_t *xfer);

/*! @brief MIPI DSI memory write function. */
typedef status_t (*mipi_dsi_mem_write_func_t)(uint8_t virtualChannel, const uint8_t *data, uint32_t length);

/*! @brief MIPI DSI memory write function using 2-dimensional way. */
typedef status_t (*mipi_dsi_mem_write_func_2D_t)(
    uint8_t virtualChannel, const uint8_t *data, uint32_t minorLoop, uint32_t minorLoopOffset, uint32_t majorLoop);

/*! @brief MIPI DSI device. */
typedef struct _mipi_dsi_device
{
    uint8_t virtualChannel;
    mipi_dsi_transfer_func_t xferFunc;
    mipi_dsi_mem_write_func_t memWriteFunc;      /*!< Function to write display memory,
                                                   it should be non-blocking function and
                                                   notify upper layer using callback when finished.
                                                   Not used when panel works in video mode. */
    mipi_dsi_mem_write_func_2D_t memWriteFunc2D; /*!< Function to write display memory using 2-dimensional way,
                                              it should be non-blocking function and
                                              notify upper layer using callback when finished.
                                              Not used when panel works in video mode. */
    mipi_dsi_mem_done_callback_t callback;       /*!< The callback function to notify upper layer
                                                    that memory write done. Not used when panel
                                                    works in video mode. */
    void *userData;                              /*!< Parameter for the memory write done callback.
                                                 not used when panel works in video mode. */
} mipi_dsi_device_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Send software reset to MIPI DSI device.
 *
 * @param device The MIPI DSI device.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_SoftReset(mipi_dsi_device_t *device);

/*!
 * @brief Set display on or off.
 *
 * @param device The MIPI DSI device.
 * @param on Set true to turn on, false to turn off.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_SetDisplayOn(mipi_dsi_device_t *device, bool on);

/*!
 * @brief Enter or exit sleep mode.
 *
 * @param device The MIPI DSI device.
 * @param enter Set true to enter sleep mode, false to exit.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_EnterSleepMode(mipi_dsi_device_t *device, bool enter);

/*!
 * @brief Enter or exit partial mode.
 *
 * @param device The MIPI DSI device.
 * @param enter Set true to enter partial mode, false to exit.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_EnterPartialMode(mipi_dsi_device_t *device, bool enter);

/*!
 * @brief Enter or exit invert mode.
 *
 * @param device The MIPI DSI device.
 * @param enter Set true to enter invert mode, false to exit.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_EnterInvertMode(mipi_dsi_device_t *device, bool enter);

/*!
 * @brief Enter or exit idle mode.
 *
 * @param device The MIPI DSI device.
 * @param enter Set true to enter idle mode, false to exit.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_EnterIdleMode(mipi_dsi_device_t *device, bool enter);

/*!
 * @brief Send DCS command.
 *
 * @param device The MIPI DSI device.
 * @param txData The data to send.
 * @param txDataSize Size of the data to send (in bytes).
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_Write(mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize);

/*!
 * @brief Send generic data.
 *
 * @param device The MIPI DSI device.
 * @param txData The data to send.
 * @param txDataSize Size of the data to send (in bytes).
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_GenericWrite(mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize);

/*!
 * @brief Set the maximum return data length.
 *
 * @param device The MIPI DSI device.
 * @param sizeBytes Maximum return data length.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_SetMaxReturnPktSize(mipi_dsi_device_t *device, uint16_t sizeBytes);

/*!
 * @brief Generic read.
 *
 * @param device The MIPI DSI device.
 * @param txData The data to send before read.
 * @param txDataSize Size of the data to send (in bytes).
 * @param rxData The data to read.
 * @param rxDataSize Size of the data to read (in bytes), after this function returns,
 * it is the actual read length.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_GenericRead(
    mipi_dsi_device_t *device, const uint8_t *txData, int32_t txDataSize, uint8_t *rxData, int32_t *rxDataSize);

/*!
 * @brief Read DCS command(read type command, such as: Get Display ID).
 *
 * @param device The MIPI DSI device.
 * @param dcsCmd The command to send before read.
 * @param rxData The data to read.
 * @param rxDataSize Size of the data to read (in bytes), after this function returns,
 * it is the actual read length.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_ReadCMD(mipi_dsi_device_t *device, enum _mipi_dcs dcsCmd, uint8_t *rxData, int32_t *rxDataSize);

/*!
 * @brief Set the panel pixel format.
 *
 * @param device The MIPI DSI device.
 * @param dbiFormat The DBI interface pixel format.
 * @param dpiFormat The DPI interface pixel format.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_DCS_SetPixelFormat(mipi_dsi_device_t *device,
                                     mipi_dsc_pixel_format_t dbiFormat,
                                     mipi_dsc_pixel_format_t dpiFormat);

/*!
 * @brief Select area to write or read pixels.
 *
 * @param device The MIPI DSI device.
 * @param startX Start point X coordination.
 * @param startY Start point Y coordination.
 * @param endX End point X coordination.
 * @param endY End point Y coordination.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_SelectArea(mipi_dsi_device_t *device, uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY);

/*!
 * @brief Send pixel data to the display controller's frame memory.
 *
 * The pixels will be shown in the region selected by @ref MIPI_DSI_SelectArea.
 * This function is non-blocking function, user should install callback function
 * using @ref MIPI_DSI_SetMemoryDoneCallback to get informed when write finished.
 *
 * @param device The MIPI DSI device.
 * @param data The pixel data to send.
 * @param length Length of the data in byte.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_WriteMemory(mipi_dsi_device_t *device, const uint8_t *data, uint32_t length);

/*!
 * @brief Send pixel data to the display controller's frame memory in 2-dinmensional way.
 *
 * The pixels will be shown in the region selected by @ref MIPI_DSI_SelectArea.
 * This function is non-blocking function, user should install callback function
 * using @ref MIPI_DSI_SetMemoryDoneCallback to get informed when write finished.
 *
 * @verbatim
 * +---------------------------------------------------+
 * |                                                   |
 * |         data                                      |
 * |           +-------------------+                   |
 * |           |    minorLoop     |                   |
 * |           |                   |                   |
 * |           |                   | majorLoop        |
 * |           |                   |                   |
 * |           |                   |                   |
 * |           +-------------------+                   |
 * |                                                   |
 * |     minorLoop + minorLoopOffset                |
 * +---------------------------------------------------+
 * @endverbatim
 *
 * @param device The MIPI DSI device.
 * @param data The pixel data to send.
 * @param minorLoop Count of the data in one line in byte.
 * @param minorLoopOffset The offset between line stride and the count of one line in byte.
 * @param majorLoop Count of the lines in byte.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
status_t MIPI_DSI_WriteMemory2D(
    mipi_dsi_device_t *device, const uint8_t *data, uint32_t minorLoop, uint32_t minorLoopOffset, uint32_t majorLoop);

/*!
 * @brief Install the callback called when write memory finished.
 *
 * Upper layer should install callback function using this function to
 * get memory write done notification.
 *
 * @param device The MIPI DSI device.
 * @param callback The callback function to inform upper layer that memory write done.
 * @param userData Parameter used by the callback.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
void MIPI_DSI_SetMemoryDoneCallback(mipi_dsi_device_t *device, mipi_dsi_mem_done_callback_t callback, void *userData);

/*!
 * @brief The callback function lower layer should call when write memory finished.
 *
 * When implement the @ref mipi_dsi_device_t, this function should be called when
 * the memory writing finished. The parameter @p userData should be pointer to the
 * @ref mipi_dsi_device_t.
 *
 * @param status The memory writing result. @ref kStatus_Success if success.
 * @param userData Must be pointer to the @ref mipi_dsi_device_t instance.
 */
void MIPI_DSI_MemoryDoneDriverCallback(status_t status, void *userData);

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_MIPI_DSI_CMD_H_ */
