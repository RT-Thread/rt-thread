/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_DC_FB_ELCDIF_H_
#define _FSL_DC_FB_ELCDIF_H_

#include "fsl_dc_fb.h"
#include "fsl_elcdif.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fixed MISRA-C 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup dc_fb_elcdif
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DC_FB_ELCDIF_MAX_LAYER                   1U /* Only support one layer currently. */
#define DC_FB_ELCDIF_DEFAULT_PIXEL_FORMAT        kVIDEO_PixelFormatRGB565
#define DC_FB_ELCDIF_DEFAULT_PIXEL_FORMAT_ELCDIF kELCDIF_PixelFormatRGB565

/*! @brief Data for ELCDIF display controller layer. */
typedef struct _dc_fb_elcdif_layer
{
    bool enabled;               /*!< The layer is enabled. */
    volatile bool framePending; /*!< New frame pending. */
    void *activeBuffer;         /*!< The frame buffer which is shown. */
    void *inactiveBuffer;       /*!< The frame buffer which will be shown. */
    dc_fb_callback_t callback;  /*!< Callback for buffer switch off. */
    void *cbParam;              /*!< Callback parameter. */
} dc_fb_elcdif_layer_t;

/*! @brief Data for ELCDIF display controller driver handle. */
typedef struct _dc_fb_elcdif_handle
{
    LCDIF_Type *elcdif;                                  /*!< eLCDIF peripheral. */
    uint8_t initTimes;                                   /*!< How many times the DC is initialized. */
    uint16_t height;                                     /*!< Panel height. */
    uint16_t width;                                      /*!< Panel width. */
    dc_fb_elcdif_layer_t layers[DC_FB_ELCDIF_MAX_LAYER]; /*!< Information of the layer. */
} dc_fb_elcdif_handle_t;

/*! @brief Configuration for ELCDIF display controller driver handle. */
typedef struct _dc_fb_elcdif_config
{
    LCDIF_Type *elcdif;            /*!< ELCDIF peripheral. */
    uint16_t width;                /*!< Width of the panel. */
    uint16_t height;               /*!< Height of the panel. */
    uint16_t hsw;                  /*!< HSYNC pulse width. */
    uint16_t hfp;                  /*!< Horizontal front porch. */
    uint16_t hbp;                  /*!< Horizontal back porch. */
    uint16_t vsw;                  /*!< VSYNC pulse width. */
    uint16_t vfp;                  /*!< Vertical front porch. */
    uint16_t vbp;                  /*!< Vertical back porch. */
    uint32_t polarityFlags;        /*!< Control flags, OR'ed value of @ref _elcdif_polarity_flags. */
    elcdif_lcd_data_bus_t dataBus; /*!< LCD data bus. */
} dc_fb_elcdif_config_t;

extern const dc_fb_ops_t g_dcFbOpsElcdif;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t DC_FB_ELCDIF_Init(const dc_fb_t *dc);
status_t DC_FB_ELCDIF_Deinit(const dc_fb_t *dc);
status_t DC_FB_ELCDIF_EnableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_ELCDIF_DisableLayer(const dc_fb_t *dc, uint8_t layer);
status_t DC_FB_ELCDIF_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_ELCDIF_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo);
status_t DC_FB_ELCDIF_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer);
uint32_t DC_FB_ELCDIF_GetProperty(const dc_fb_t *dc);
void DC_FB_ELCDIF_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param);
void DC_FB_ELCDIF_IRQHandler(const dc_fb_t *dc);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_DC_FB_ELCDIF_H_ */
