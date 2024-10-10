/*
 * Copyright  2017-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DISPLAY_H_
#define _FSL_DISPLAY_H_

#include "fsl_video_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Display common configuration. */
typedef struct _display_common_cfg_t
{
    uint16_t width;
    uint16_t height;
    uint16_t hsw; /*!< HSYNC pulse width. */
    uint16_t hfp; /*!< Horizontal front porch. */
    uint16_t hbp; /*!< Horizontal back porch. */
    uint16_t vsw; /*!< VSYNC pulse width. */
    uint16_t vfp; /*!< Vrtical front porch. */
    uint16_t vbp; /*!< Vertical back porch. */
    uint32_t clock; /* !< pixecl clock in kHz>. */
} display_common_cfg;

/*! @brief Display control flags. */
enum _display_flags
{
    kDISPLAY_VsyncActiveLow         = 0U,         /*!< VSYNC active low. */
    kDISPLAY_VsyncActiveHigh        = (1U << 0U), /*!< VSYNC active high. */
    kDISPLAY_HsyncActiveLow         = 0U,         /*!< HSYNC active low. */
    kDISPLAY_HsyncActiveHigh        = (1U << 1U), /*!< HSYNC active high. */
    kDISPLAY_DataEnableActiveHigh   = 0U,         /*!< Data enable line active high. */
    kDISPLAY_DataEnableActiveLow    = (1U << 2U), /*!< Data enable line active low. */
    kDISPLAY_DataLatchOnRisingEdge  = 0U,         /*!< Latch data on rising clock edge. */
    kDISPLAY_DataLatchOnFallingEdge = (1U << 3U), /*!< Latch data on falling clock edge. */
};

/*! @brief Display configuration. */
typedef struct _display_config
{
    uint32_t resolution;              /*!< Resolution, see @ref video_resolution_t and @ref FSL_VIDEO_RESOLUTION. */
    uint16_t hsw;                     /*!< HSYNC pulse width. */
    uint16_t hfp;                     /*!< Horizontal front porch. */
    uint16_t hbp;                     /*!< Horizontal back porch. */
    uint16_t vsw;                     /*!< VSYNC pulse width. */
    uint16_t vfp;                     /*!< Vrtical front porch. */
    uint16_t vbp;                     /*!< Vertical back porch. */
    uint32_t controlFlags;            /*!< Control flags, OR'ed value of @ref _display_flags. */
    uint8_t dsiLanes;                 /*!< MIPI DSI data lanes number. */
    uint32_t pixelClock_Hz;           /*!< Pixel clock in Hz. */
    video_pixel_format_t pixelFormat; /*!< Pixel format. */
} display_config_t;

typedef struct _display_handle display_handle_t;

/*! @brief Display device operations. */
typedef struct _display_operations
{
    status_t (*init)(display_handle_t *handle, const display_config_t *config); /*!< Init the device. */
    status_t (*deinit)(display_handle_t *handle);                               /*!< Deinit the device. */
    status_t (*start)(display_handle_t *handle);                                /*!< Start the device. */
    status_t (*stop)(display_handle_t *handle);                                 /*!< Stop the device. */
} display_operations_t;

/*! @brief Display handle. */
struct _display_handle
{
    const void *resource;
    const display_operations_t *ops;
    uint16_t width;
    uint16_t height;
    video_pixel_format_t pixelFormat;
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the display device with user defined configuration.
 *
 * @param handle Display device handle.
 * @param config Pointer to the user-defined configuration structure.
 * @return Returns @ref kStatus_Success if initialize success, otherwise returns
 * error code.
 */
static inline status_t DISPLAY_Init(display_handle_t *handle, const display_config_t *config)
{
    return handle->ops->init(handle, config);
}

/*!
 * @brief Deinitialize the display device.
 *
 * @param handle Display device handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
static inline status_t DISPLAY_Deinit(display_handle_t *handle)
{
    return handle->ops->deinit(handle);
}

/*!
 * @brief Start the display device.
 *
 * @param handle Display device handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
static inline status_t DISPLAY_Start(display_handle_t *handle)
{
    return handle->ops->start(handle);
}

/*!
 * @brief Stop the display device.
 *
 * @param handle Display device handle.
 * @return Returns @ref kStatus_Success if success, otherwise returns error code.
 */
static inline status_t DISPLAY_Stop(display_handle_t *handle)
{
    return handle->ops->stop(handle);
}

#if defined(__cplusplus)
}
#endif

#endif /* _FSL_DISPLAY_H_ */
