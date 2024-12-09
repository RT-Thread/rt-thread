/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DC_FB_H_
#define _FSL_DC_FB_H_

#include "fsl_video_common.h"

/*!
 * @addtogroup dc_fb
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief frame buffer information. */
typedef struct _dc_fb_info
{
    uint16_t startX;                  /*!< The start position in the panel. */
    uint16_t startY;                  /*!< The start position in the panel. */
    uint16_t width;                   /*!< How many pixels in one line of the frame buffer.*/
    uint16_t height;                  /*!< How many lines in one frame buffer. */
    uint16_t strideBytes;             /*!< Stride of the frame buffer */
    video_pixel_format_t pixelFormat; /*!< Pixel format of the frame buffer */
} dc_fb_info_t;

/*! @brief Display controller frame callback. */
typedef void (*dc_fb_callback_t)(void *param, void *inactiveBuffer);

/*! @brief Display controller. */
typedef struct _dc_fb dc_fb_t;

/*! @brief Display controller operations. */
typedef struct _dc_fb_ops
{
    status_t (*init)(const dc_fb_t *dc);
    status_t (*deinit)(const dc_fb_t *dc);
    status_t (*enableLayer)(const dc_fb_t *dc, uint8_t layer);
    status_t (*disableLayer)(const dc_fb_t *dc, uint8_t layer);
    status_t (*setLayerConfig)(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
    status_t (*getLayerDefaultConfig)(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
    status_t (*setFrameBuffer)(const dc_fb_t *dc, uint8_t layer, void *frameBuffer);
    uint32_t (*getProperty)(const dc_fb_t *dc);
    void (*setCallback)(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param);
} dc_fb_ops_t;

/*! @brief Display controller property. */
enum _dc_fb_property
{
    kDC_FB_ReserveFrameBuffer      = (1 << 0), /*< One frame buffer is always used as the DC active buffer. */
    kDC_FB_TwoDimensionMemoryWrite = (1 << 1), /*< Support writing memory to device in two dimension way. */
};

/*! @brief Display controller driver handle. */
struct _dc_fb
{
    const dc_fb_ops_t *ops; /* Display controller operations. */
    void *prvData;          /* Private data for the display controller. */
    const void *config;     /* Configuration for the display controller. */
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DC_FB_H_ */
