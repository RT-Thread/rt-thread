/*
 * Copyright (c) 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DC_FB_LCDIFV2_H_
#define _FSL_DC_FB_LCDIFV2_H_

#include "fsl_dc_fb.h"
#include "fsl_lcdifv2.h"

/*
 * Change log:
 *
 *   1.0.2
 *     - Add more pixel format support.
 *
 *   1.0.1
 *     - Fix MISRA-C 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dc_fb_lcdifv2
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DC_FB_LCDIFV2_MAX_LAYER                    ((uint32_t)LCDIFV2_LAYER_COUNT)
#define DC_FB_LCDIFV2_DEFAULT_BUF_PER_LAYER        3U
#define DC_FB_LCDIFV2_DEFAULT_PIXEL_FORMAT         kVIDEO_PixelFormatRGB565
#define DC_FB_LCDIFV2_DEFAULT_PIXEL_FORMAT_LCDIFV2 kLCDIFV2_PixelFormatRGB565
#define DC_FB_LCDIFV2_DEFAULT_BYTE_PER_PIXEL       2U

/*! @brief Data for LCDIFV2 display controller layer. */
typedef struct _dc_fb_lcdifv2_layer
{
    bool enabled;                    /*!< The layer is enabled. */
    volatile bool framePending;      /*!< New frame pending. */
    volatile bool shadowLoadPending; /*!< Shadow load pending. */
    void *activeBuffer;              /*!< The frame buffer which is shown. */
    void *inactiveBuffer;            /*!< The frame buffer which will be shown. */
    dc_fb_callback_t callback;       /*!< Callback for buffer switch off. */
    void *cbParam;                   /*!< Callback parameter. */
} dc_fb_lcdifv2_layer_t;

/*! @brief Data for LCDIFV2 display controller driver handle. */
typedef struct _dc_fb_lcdifv2_handle
{
    LCDIFV2_Type *lcdifv2;                                 /*!< LCDIFV2 peripheral. */
    uint8_t initTimes;                                     /*!< How many times the DC is initialized. */
    uint16_t height;                                       /*!< Panel height. */
    uint16_t width;                                        /*!< Panel width. */
    uint8_t domain;                                        /*!< Domain used for interrupt. */
    dc_fb_lcdifv2_layer_t layers[DC_FB_LCDIFV2_MAX_LAYER]; /*!< Information of the layer. */
} dc_fb_lcdifv2_handle_t;

/*! @brief Configuration for LCDIFV2 display controller driver handle. */
typedef struct _dc_fb_lcdifv2_config
{
    LCDIFV2_Type *lcdifv2;          /*!< LCDIFV2 peripheral. */
    uint16_t width;                 /*!< Width of the panel. */
    uint16_t height;                /*!< Height of the panel. */
    uint16_t hsw;                   /*!< HSYNC pulse width. */
    uint16_t hfp;                   /*!< Horizontal front porch. */
    uint16_t hbp;                   /*!< Horizontal back porch. */
    uint16_t vsw;                   /*!< VSYNC pulse width. */
    uint16_t vfp;                   /*!< Vertical front porch. */
    uint16_t vbp;                   /*!< Vertical back porch. */
    uint32_t polarityFlags;         /*!< Control flags, OR'ed value of @ref _lcdifv2_polarity_flags. */
    lcdifv2_line_order_t lineOrder; /*!< Line order. */
    uint8_t domain;                 /*!< Domain used to for interrupt. */
} dc_fb_lcdifv2_config_t;

extern const dc_fb_ops_t g_dcFbOpsLcdifv2;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t DC_FB_LCDIFV2_Init(const dc_fb_t *dc);
status_t DC_FB_LCDIFV2_Deinit(const dc_fb_t *dc);
status_t DC_FB_LCDIFV2_EnableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_LCDIFV2_DisableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_LCDIFV2_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_LCDIFV2_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_LCDIFV2_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer);
uint32_t DC_FB_LCDIFV2_GetProperty(const dc_fb_t *dc);
void DC_FB_LCDIFV2_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param);
void DC_FB_LCDIFV2_IRQHandler(const dc_fb_t *dc);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DC_FB_LCDIFV2_H_ */
