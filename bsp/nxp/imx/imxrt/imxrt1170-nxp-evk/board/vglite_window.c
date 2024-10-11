/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "vglite_support.h"
#include "vg_lite_platform.h"
#include "vglite_window.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if !DEMO_BUFFER_FIXED_ADDRESS
AT_NONCACHEABLE_SECTION_ALIGN(
    static uint8_t s_frameBuffer[APP_BUFFER_COUNT][DEMO_BUFFER_HEIGHT][DEMO_BUFFER_WIDTH][DEMO_BUFFER_BYTE_PER_PIXEL],
    FRAME_BUFFER_ALIGN);

#define DEMO_BUFFER0_ADDR (uint32_t) s_frameBuffer[0]

#if APP_BUFFER_COUNT > 1
#define DEMO_BUFFER1_ADDR (uint32_t) s_frameBuffer[1]
#endif

#if APP_BUFFER_COUNT > 2
#define DEMO_BUFFER2_ADDR (uint32_t) s_frameBuffer[2]
#endif

#endif

static const uint32_t s_frameBufferAddress[APP_BUFFER_COUNT] = {DEMO_BUFFER0_ADDR,
#if APP_BUFFER_COUNT > 1
                                                                DEMO_BUFFER1_ADDR,
#endif
#if APP_BUFFER_COUNT > 2
                                                                DEMO_BUFFER2_ADDR
#endif
};
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static vg_lite_buffer_format_t video_format_to_vglite(video_pixel_format_t format)
{
    vg_lite_buffer_format_t fmt;
    switch (format)
    {
        case kVIDEO_PixelFormatRGB565:
            fmt = VG_LITE_BGR565;
            break;

        case kVIDEO_PixelFormatBGR565:
            fmt = VG_LITE_RGB565;
            break;

        case kVIDEO_PixelFormatXRGB8888:
            fmt = VG_LITE_BGRX8888;
            break;

        default:
            fmt = VG_LITE_RGB565;
            break;
    }

    return fmt;
}

vg_lite_error_t VGLITE_CreateDisplay(vg_lite_display_t *display)
{
    if (!display)
        return VG_LITE_INVALID_ARGUMENT;

    FBDEV_Open(&display->g_fbdev, &g_dc, 0);

    return VG_LITE_SUCCESS;
}

vg_lite_error_t VGLITE_CreateWindow(vg_lite_display_t *display, vg_lite_window_t *window)
{
    vg_lite_error_t ret = VG_LITE_SUCCESS;
    status_t status;
    void *buffer;
    vg_lite_buffer_t *vg_buffer;
    fbdev_t *g_fbdev          = &(display->g_fbdev);
    fbdev_fb_info_t *g_fbInfo = &(display->g_fbInfo);

    window->bufferCount = APP_BUFFER_COUNT;
    window->display     = display;
    window->width       = DEMO_BUFFER_WIDTH;
    window->height      = DEMO_BUFFER_HEIGHT;
    window->current     = -1;
    FBDEV_GetFrameBufferInfo(g_fbdev, g_fbInfo);

    g_fbInfo->bufInfo.pixelFormat = DEMO_BUFFER_PIXEL_FORMAT;
    g_fbInfo->bufInfo.startX      = DEMO_BUFFER_START_X;
    g_fbInfo->bufInfo.startY      = DEMO_BUFFER_START_Y;
    g_fbInfo->bufInfo.width       = window->width;
    g_fbInfo->bufInfo.height      = window->height;
    g_fbInfo->bufInfo.strideBytes = DEMO_BUFFER_STRIDE_BYTE;

    g_fbInfo->bufferCount = window->bufferCount;
    for (uint8_t i = 0; i < window->bufferCount; i++)
    {
        vg_buffer            = &(window->buffers[i]);
        g_fbInfo->buffers[i] = (void *)s_frameBufferAddress[i];
        vg_buffer->memory    = g_fbInfo->buffers[i];
        vg_buffer->address   = s_frameBufferAddress[i];
        vg_buffer->width     = g_fbInfo->bufInfo.width;
        vg_buffer->height    = g_fbInfo->bufInfo.height;
        vg_buffer->stride    = g_fbInfo->bufInfo.strideBytes;
        vg_buffer->format    = video_format_to_vglite(DEMO_BUFFER_PIXEL_FORMAT);
    }

    status = FBDEV_SetFrameBufferInfo(g_fbdev, g_fbInfo);
    if (status != kStatus_Success)
    {
        while (1)
            ;
    }

    buffer = FBDEV_GetFrameBuffer(g_fbdev, 0);

    assert(buffer != NULL);

    memset(buffer, 0, g_fbInfo->bufInfo.height * g_fbInfo->bufInfo.strideBytes);

    FBDEV_SetFrameBuffer(g_fbdev, buffer, 0);

    FBDEV_Enable(g_fbdev);

    return ret;
}

vg_lite_error_t VGLITE_DestoryWindow(void)
{
    return VG_LITE_SUCCESS;
}

vg_lite_error_t VGLITE_DestroyDisplay(void)
{
    return VG_LITE_SUCCESS;
}

vg_lite_buffer_t *VGLITE_GetRenderTarget(vg_lite_window_t *window)
{
    vg_lite_buffer_t *rt = NULL;
    void *memory         = FBDEV_GetFrameBuffer(&window->display->g_fbdev, 0);
    for (uint8_t i = 0; i < window->bufferCount; i++)
    {
        rt = &(window->buffers[i]);
        if (memory == rt->memory)
        {
            window->current = i;
            return rt;
        }
    }
    return NULL;
}

void VGLITE_SwapBuffers(vg_lite_window_t *window)
{
    vg_lite_buffer_t *rt;
    if (window->current >= 0 && window->current < window->bufferCount)
        rt = &(window->buffers[window->current]);
    else
        return;

    vg_lite_finish();

    FBDEV_SetFrameBuffer(&window->display->g_fbdev, rt->memory, 0);
}
