/*
 * Copyright 2019-2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_elcdif.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsElcdif = {
    .init                  = DC_FB_ELCDIF_Init,
    .deinit                = DC_FB_ELCDIF_Deinit,
    .enableLayer           = DC_FB_ELCDIF_EnableLayer,
    .disableLayer          = DC_FB_ELCDIF_DisableLayer,
    .setLayerConfig        = DC_FB_ELCDIF_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_ELCDIF_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_ELCDIF_SetFrameBuffer,
    .getProperty           = DC_FB_ELCDIF_GetProperty,
    .setCallback           = DC_FB_ELCDIF_SetCallback,
};

typedef struct
{
    video_pixel_format_t videoFormat;
    elcdif_pixel_format_t elcdifFormat;
} dc_fb_elcdif_pixel_foramt_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t DC_FB_ELCDIF_GetPixelFormat(video_pixel_format_t input, elcdif_pixel_format_t *output);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const dc_fb_elcdif_pixel_foramt_map_t s_elcdifPixelFormatMap[] = {
    {kVIDEO_PixelFormatLUT8, kELCDIF_PixelFormatRAW8},
    {kVIDEO_PixelFormatRGB565, kELCDIF_PixelFormatRGB565},
    {
        kVIDEO_PixelFormatXRGB8888,
        kELCDIF_PixelFormatXRGB8888,
    },
    {
        kVIDEO_PixelFormatRGB888,
        kELCDIF_PixelFormatRGB888,
    }};

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t DC_FB_ELCDIF_GetPixelFormat(video_pixel_format_t input, elcdif_pixel_format_t *output)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_elcdifPixelFormatMap); i++)
    {
        if (s_elcdifPixelFormatMap[i].videoFormat == input)
        {
            *output = s_elcdifPixelFormatMap[i].elcdifFormat;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}

status_t DC_FB_ELCDIF_Init(const dc_fb_t *dc)
{
    const dc_fb_elcdif_config_t *dcConfig;
    elcdif_rgb_mode_config_t elcdifConfig = {0};

    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    if (0U == dcHandle->initTimes++)
    {
        dcConfig = (const dc_fb_elcdif_config_t *)(dc->config);

        elcdifConfig.panelWidth    = dcConfig->width;
        elcdifConfig.panelHeight   = dcConfig->height;
        elcdifConfig.hsw           = (uint8_t)dcConfig->hsw;
        elcdifConfig.hfp           = (uint8_t)dcConfig->hfp;
        elcdifConfig.hbp           = (uint8_t)dcConfig->hbp;
        elcdifConfig.vsw           = (uint8_t)dcConfig->vsw;
        elcdifConfig.vfp           = (uint8_t)dcConfig->vfp;
        elcdifConfig.vbp           = (uint8_t)dcConfig->vbp;
        elcdifConfig.bufferAddr    = 0;
        elcdifConfig.dataBus       = dcConfig->dataBus;
        elcdifConfig.pixelFormat   = DC_FB_ELCDIF_DEFAULT_PIXEL_FORMAT_ELCDIF;
        elcdifConfig.polarityFlags = dcConfig->polarityFlags;

        dcHandle->height = dcConfig->height;
        dcHandle->width  = dcConfig->width;
        dcHandle->elcdif = dcConfig->elcdif;

        ELCDIF_RgbModeInit(dcHandle->elcdif, &elcdifConfig);
    }

    return kStatus_Success;
}

status_t DC_FB_ELCDIF_Deinit(const dc_fb_t *dc)
{
    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    if (dcHandle->initTimes > 0U)
    {
        if ((--dcHandle->initTimes) == 0U)
        {
            ELCDIF_Deinit(dcHandle->elcdif);
        }
    }

    return kStatus_Success;
}

status_t DC_FB_ELCDIF_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);

    status_t status                 = kStatus_Success;
    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    /* If the layer is already started. */
    if (!dcHandle->layers[layer].enabled)
    {
        /* Must have valid frame buffer to show. */
        if (dcHandle->layers[layer].activeBuffer == NULL)
        {
            status = kStatus_Fail;
        }
        else
        {
            ELCDIF_RgbModeStart(dcHandle->elcdif);
            dcHandle->layers[layer].enabled = true;
            ELCDIF_EnableInterrupts(dcHandle->elcdif, (uint32_t)kELCDIF_CurFrameDoneInterruptEnable);
        }
    }

    return status;
}

status_t DC_FB_ELCDIF_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);

    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    if (dcHandle->layers[layer].enabled)
    {
        ELCDIF_RgbModeStop(dcHandle->elcdif);
        dcHandle->layers[layer].enabled = false;
        ELCDIF_DisableInterrupts(dcHandle->elcdif, (uint32_t)kELCDIF_CurFrameDoneInterruptEnable);
    }

    return kStatus_Success;
}

status_t DC_FB_ELCDIF_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);

    elcdif_pixel_format_t pixelFormat;
    status_t status;

    dc_fb_elcdif_handle_t *dcHandle = (dc_fb_elcdif_handle_t *)(dc->prvData);

    assert(fbInfo->startX == 0U);
    assert(fbInfo->startY == 0U);
    assert(fbInfo->width == dcHandle->width);
    assert(fbInfo->height == dcHandle->height);
    assert(fbInfo->strideBytes == VIDEO_GetPixelSizeBits(fbInfo->pixelFormat) * dcHandle->width / 8U);

    status = DC_FB_ELCDIF_GetPixelFormat(fbInfo->pixelFormat, &pixelFormat);
    if (kStatus_Success != status)
    {
        return status;
    }

    ELCDIF_RgbModeSetPixelFormat(dcHandle->elcdif, pixelFormat);

    return kStatus_Success;
}

status_t DC_FB_ELCDIF_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);

    dc_fb_elcdif_handle_t *dcHandle = (dc_fb_elcdif_handle_t *)(dc->prvData);

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = dcHandle->width;
    fbInfo->height      = dcHandle->height;
    fbInfo->strideBytes = 2U * dcHandle->width;
    fbInfo->pixelFormat = DC_FB_ELCDIF_DEFAULT_PIXEL_FORMAT;

    return kStatus_Success;
}

status_t DC_FB_ELCDIF_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);
    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    ELCDIF_SetNextBufferAddr(dcHandle->elcdif, (uint32_t)(uint8_t *)frameBuffer);
    dcHandle->layers[layer].inactiveBuffer = frameBuffer;

    /*
     * If the layer is not started, set the current buffer and next buffer to
     * new frame buffer, there is not pending frame.
     * If the layer already started, only set the next buffer, and the new frameBuffer
     * is pending until current buffer switched out.
     */
    if (!dcHandle->layers[layer].enabled)
    {
        dcHandle->elcdif->CUR_BUF            = ELCDIF_ADDR_CPU_2_IP((uint32_t)(uint8_t *)frameBuffer);
        dcHandle->layers[layer].activeBuffer = frameBuffer;
    }
    else
    {
        dcHandle->layers[layer].framePending = true;
    }

    return kStatus_Success;
}

void DC_FB_ELCDIF_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    assert(layer < DC_FB_ELCDIF_MAX_LAYER);
    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;

    dcHandle->layers[layer].callback = callback;
    dcHandle->layers[layer].cbParam  = param;
}

uint32_t DC_FB_ELCDIF_GetProperty(const dc_fb_t *dc)
{
    return (uint32_t)kDC_FB_ReserveFrameBuffer;
}

void DC_FB_ELCDIF_IRQHandler(const dc_fb_t *dc)
{
    dc_fb_elcdif_handle_t *dcHandle = dc->prvData;
    dc_fb_elcdif_layer_t *layer;
    void *oldActiveBuffer;
    ELCDIF_ClearInterruptStatus(dcHandle->elcdif, (uint32_t)kELCDIF_CurFrameDone);

    for (uint8_t i = 0; i < DC_FB_ELCDIF_MAX_LAYER; i++)
    {
        if (dcHandle->layers[i].framePending)
        {
            layer = &dcHandle->layers[i];

            oldActiveBuffer                  = layer->activeBuffer;
            layer->activeBuffer              = layer->inactiveBuffer;
            dcHandle->layers[i].framePending = false;

            layer->callback(layer->cbParam, oldActiveBuffer);
        }
    }
}
