/*
 * Copyright (c) 2019-2020, 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_dc_fb_lcdifv2.h"
#if defined(USE_RTOS)
#include "rtthread.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
const dc_fb_ops_t g_dcFbOpsLcdifv2 = {
    .init                  = DC_FB_LCDIFV2_Init,
    .deinit                = DC_FB_LCDIFV2_Deinit,
    .enableLayer           = DC_FB_LCDIFV2_EnableLayer,
    .disableLayer          = DC_FB_LCDIFV2_DisableLayer,
    .setLayerConfig        = DC_FB_LCDIFV2_SetLayerConfig,
    .getLayerDefaultConfig = DC_FB_LCDIFV2_GetLayerDefaultConfig,
    .setFrameBuffer        = DC_FB_LCDIFV2_SetFrameBuffer,
    .getProperty           = DC_FB_LCDIFV2_GetProperty,
    .setCallback           = DC_FB_LCDIFV2_SetCallback,
};

typedef struct
{
    video_pixel_format_t videoFormat;
    lcdifv2_pixel_format_t lcdifv2Format;
} dc_fb_lcdifv2_pixel_foramt_map_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t DC_FB_LCDIFV2_GetPixelFormat(video_pixel_format_t input, lcdifv2_pixel_format_t *output);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static const dc_fb_lcdifv2_pixel_foramt_map_t s_lcdifv2PixelFormatMap[] = {
    {kVIDEO_PixelFormatRGB565, kLCDIFV2_PixelFormatRGB565},
    {kVIDEO_PixelFormatRGB888, kLCDIFV2_PixelFormatRGB888},
    {kVIDEO_PixelFormatXRGB8888, kLCDIFV2_PixelFormatARGB8888},
    {kVIDEO_PixelFormatXBGR8888, kLCDIFV2_PixelFormatABGR8888},
    {kVIDEO_PixelFormatLUT8, kLCDIFV2_PixelFormatIndex8BPP},
    {kVIDEO_PixelFormatXRGB4444, kLCDIFV2_PixelFormatARGB4444},
    {kVIDEO_PixelFormatXRGB1555, kLCDIFV2_PixelFormatARGB1555}};

/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t DC_FB_LCDIFV2_GetPixelFormat(video_pixel_format_t input, lcdifv2_pixel_format_t *output)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(s_lcdifv2PixelFormatMap); i++)
    {
        if (s_lcdifv2PixelFormatMap[i].videoFormat == input)
        {
            *output = s_lcdifv2PixelFormatMap[i].lcdifv2Format;
            return kStatus_Success;
        }
    }

    return kStatus_InvalidArgument;
}

status_t DC_FB_LCDIFV2_Init(const dc_fb_t *dc)
{
    status_t status = kStatus_Success;
    const dc_fb_lcdifv2_config_t *dcConfig;

    lcdifv2_display_config_t lcdifv2Config = {0};

    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    if (0U == dcHandle->initTimes++)
    {
        dcConfig = (const dc_fb_lcdifv2_config_t *)(dc->config);

        LCDIFV2_DisplayGetDefaultConfig(&lcdifv2Config);

        lcdifv2Config.panelWidth    = dcConfig->width;
        lcdifv2Config.panelHeight   = dcConfig->height;
        lcdifv2Config.hsw           = (uint8_t)dcConfig->hsw;
        lcdifv2Config.hfp           = (uint8_t)dcConfig->hfp;
        lcdifv2Config.hbp           = (uint8_t)dcConfig->hbp;
        lcdifv2Config.vsw           = (uint8_t)dcConfig->vsw;
        lcdifv2Config.vfp           = (uint8_t)dcConfig->vfp;
        lcdifv2Config.vbp           = (uint8_t)dcConfig->vbp;
        lcdifv2Config.polarityFlags = dcConfig->polarityFlags;
        lcdifv2Config.lineOrder     = dcConfig->lineOrder;

        dcHandle->height  = dcConfig->height;
        dcHandle->width   = dcConfig->width;
        dcHandle->lcdifv2 = dcConfig->lcdifv2;
        dcHandle->domain  = dcConfig->domain;

        LCDIFV2_Init(dcHandle->lcdifv2);

        LCDIFV2_SetDisplayConfig(dcHandle->lcdifv2, &lcdifv2Config);

        LCDIFV2_EnableInterrupts(dcHandle->lcdifv2, dcHandle->domain, (uint32_t)kLCDIFV2_VerticalBlankingInterrupt);

        LCDIFV2_EnableDisplay(dcHandle->lcdifv2, true);
    }

    return status;
}

status_t DC_FB_LCDIFV2_Deinit(const dc_fb_t *dc)
{
    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    if (dcHandle->initTimes > 0U)
    {
        if (--dcHandle->initTimes == 0U)
        {
            LCDIFV2_DisableInterrupts(dcHandle->lcdifv2, dcHandle->domain,
                                      (uint32_t)kLCDIFV2_VerticalBlankingInterrupt);
            LCDIFV2_Deinit(dcHandle->lcdifv2);
        }
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIFV2_EnableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);

    status_t status                  = kStatus_Success;
    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    /* If the layer is not started. */
    if (!dcHandle->layers[layer].enabled)
    {
        LCDIFV2_SetLayerBackGroundColor(dcHandle->lcdifv2, layer, 0U);
        LCDIFV2_EnableLayer(dcHandle->lcdifv2, layer, true);
        LCDIFV2_TriggerLayerShadowLoad(dcHandle->lcdifv2, layer);
        dcHandle->layers[layer].shadowLoadPending = true;

        while (true == dcHandle->layers[layer].shadowLoadPending)
        {
#if defined(USE_RTOS)
            rt_thread_delay(1);
#endif
        }

        dcHandle->layers[layer].activeBuffer = dcHandle->layers[layer].inactiveBuffer;
        dcHandle->layers[layer].enabled      = true;
    }

    return status;
}

status_t DC_FB_LCDIFV2_DisableLayer(const dc_fb_t *dc, uint8_t layer)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);

    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    if (dcHandle->layers[layer].enabled)
    {
        LCDIFV2_EnableLayer(dcHandle->lcdifv2, layer, false);
        LCDIFV2_TriggerLayerShadowLoad(dcHandle->lcdifv2, layer);
        dcHandle->layers[layer].enabled = false;
    }

    return kStatus_Success;
}

status_t DC_FB_LCDIFV2_SetLayerConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);

    lcdifv2_buffer_config_t bufferConfig = {0};
    lcdifv2_pixel_format_t pixelFormat;
    LCDIFV2_Type *lcdifv2;
    status_t status;

    dc_fb_lcdifv2_handle_t *dcHandle = (dc_fb_lcdifv2_handle_t *)(dc->prvData);

    lcdifv2 = dcHandle->lcdifv2;

    status = DC_FB_LCDIFV2_GetPixelFormat(fbInfo->pixelFormat, &pixelFormat);
    if (kStatus_Success != status)
    {
        return status;
    }

    LCDIFV2_SetLayerSize(lcdifv2, layer, fbInfo->width, fbInfo->height);
    LCDIFV2_SetLayerOffset(lcdifv2, layer, fbInfo->startX, fbInfo->startY);

    bufferConfig.strideBytes = fbInfo->strideBytes;
    bufferConfig.pixelFormat = pixelFormat;
    LCDIFV2_SetLayerBufferConfig(lcdifv2, layer, &bufferConfig);

    return kStatus_Success;
}

status_t DC_FB_LCDIFV2_GetLayerDefaultConfig(const dc_fb_t *dc, uint8_t layer, dc_fb_info_t *fbInfo)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);

    dc_fb_lcdifv2_handle_t *dcHandle = (dc_fb_lcdifv2_handle_t *)(dc->prvData);

    fbInfo->startX      = 0;
    fbInfo->startY      = 0;
    fbInfo->width       = dcHandle->width;
    fbInfo->height      = dcHandle->height;
    fbInfo->strideBytes = DC_FB_LCDIFV2_DEFAULT_BYTE_PER_PIXEL * dcHandle->width;
    fbInfo->pixelFormat = DC_FB_LCDIFV2_DEFAULT_PIXEL_FORMAT;

    return kStatus_Success;
}

status_t DC_FB_LCDIFV2_SetFrameBuffer(const dc_fb_t *dc, uint8_t layer, void *frameBuffer)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);
    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    LCDIFV2_SetLayerBufferAddr(dcHandle->lcdifv2, layer, (uint32_t)(uint8_t *)frameBuffer);
    dcHandle->layers[layer].inactiveBuffer = frameBuffer;

    if (dcHandle->layers[layer].enabled)
    {
        LCDIFV2_TriggerLayerShadowLoad(dcHandle->lcdifv2, layer);
        dcHandle->layers[layer].shadowLoadPending = true;
        dcHandle->layers[layer].framePending      = true;
    }
    else
    {
    }

    return kStatus_Success;
}

void DC_FB_LCDIFV2_SetCallback(const dc_fb_t *dc, uint8_t layer, dc_fb_callback_t callback, void *param)
{
    assert(layer < DC_FB_LCDIFV2_MAX_LAYER);
    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;

    dcHandle->layers[layer].callback = callback;
    dcHandle->layers[layer].cbParam  = param;
}

uint32_t DC_FB_LCDIFV2_GetProperty(const dc_fb_t *dc)
{
    return (uint32_t)kDC_FB_ReserveFrameBuffer;
}

void DC_FB_LCDIFV2_IRQHandler(const dc_fb_t *dc)
{
    uint32_t intStatus;
    dc_fb_lcdifv2_handle_t *dcHandle = dc->prvData;
    dc_fb_lcdifv2_layer_t *layer;
    void *oldActiveBuffer;

    intStatus = LCDIFV2_GetInterruptStatus(dcHandle->lcdifv2, dcHandle->domain);
    LCDIFV2_ClearInterruptStatus(dcHandle->lcdifv2, dcHandle->domain, intStatus);

    if (0U == (intStatus & (uint32_t)kLCDIFV2_VerticalBlankingInterrupt))
    {
        return;
    }

    for (uint8_t i = 0; i < DC_FB_LCDIFV2_MAX_LAYER; i++)
    {
        if (dcHandle->layers[i].shadowLoadPending)
        {
            dcHandle->layers[i].shadowLoadPending = false;
        }

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
