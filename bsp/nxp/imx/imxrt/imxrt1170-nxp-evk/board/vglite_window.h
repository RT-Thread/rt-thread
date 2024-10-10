/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _VGLITE_WINDOW_H_
#define _VGLITE_WINDOW_H_

#include "fsl_common.h"
#include "vg_lite.h"
#include "vglite_support.h"
#include "display_support.h"
#include "fsl_fbdev.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define APP_BUFFER_COUNT 2

typedef struct vg_lite_display
{
    fbdev_t g_fbdev;
    fbdev_fb_info_t g_fbInfo;
} vg_lite_display_t;

typedef struct vg_lite_window
{
    vg_lite_display_t *display;
    vg_lite_buffer_t buffers[APP_BUFFER_COUNT];
    int width;
    int height;
    int bufferCount;
    int current;
} vg_lite_window_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

vg_lite_error_t VGLITE_CreateDisplay(vg_lite_display_t *display);

vg_lite_error_t VGLITE_CreateWindow(vg_lite_display_t *display, vg_lite_window_t *window);

vg_lite_error_t VGLITE_DestoryWindow(void);

vg_lite_error_t VGLITE_DestroyDisplay(void);

vg_lite_buffer_t *VGLITE_GetRenderTarget(vg_lite_window_t *window);

void VGLITE_SwapBuffers(vg_lite_window_t *window);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _VGLITE_WINDOW_H_ */
