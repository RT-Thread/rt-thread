/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-10     Rbb666       the first version
 */
#include <rtthread.h>
#include <lcd_port.h>
#include <stdlib.h>

#include "drv_g2d.h"

#ifdef BSP_USING_G2D

static d2_device *_d2_handle;
static d2_renderbuffer *renderbuffer;

static uint32_t _GetD2Mode(void)
{
    uint32_t r;
    r = d2_mode_rgb565;

    return r;
}

int G2d_Drv_HWInit(void)
{
    d2_s32 d2_err;

    // Initialize D/AVE 2D driver
    _d2_handle = (d2_device *)rt_malloc(sizeof(_d2_handle));
    _d2_handle = d2_opendevice(0);

    d2_err = d2_inithw(_d2_handle, 0);
    if (d2_err != D2_OK)
    {
        rt_kprintf("Could NOT d2_inithw\n");
        d2_closedevice(_d2_handle);
        return RT_ERROR;
    }

    // Clear both buffers
    d2_framebuffer(_d2_handle,
                   &fb_background[0],
                   480,
                   480,
                   272,
                   (d2_s32) _GetD2Mode());
    d2_clear(_d2_handle, 0x000000);

    // Set various D2 parameters
    d2_setalphablendmode(_d2_handle, d2_bm_one, d2_bm_one_minus_alpha);
    d2_setblendmode(_d2_handle, d2_bm_alpha, d2_bm_one_minus_alpha);

    d2_setalphamode(_d2_handle, d2_am_constant);
    d2_setalpha(_d2_handle, UINT8_MAX);
    d2_setantialiasing(_d2_handle, 1);
    d2_setlinecap(_d2_handle, d2_lc_butt);
    d2_setlinejoin(_d2_handle, d2_lj_miter);

    renderbuffer = d2_newrenderbuffer(_d2_handle, 20, 20);
    if (!renderbuffer)
    {
        rt_kprintf("NO renderbuffer\n");
        d2_closedevice(_d2_handle);
    }

    return RT_EOK;
}

void _GraphicsHWDeInit(void)
{
    // Stop graphics LCD controller
    while (FSP_SUCCESS != R_GLCDC_Stop(g_display0.p_ctrl))
    {
        /* Wait for GLCDC register update to complete before closing driver. */
    }

    R_GLCDC_Close(g_display0.p_ctrl);

    // Deinitialize D/AVE 2D driver
    d2_freerenderbuffer(_d2_handle, renderbuffer);
    d2_deinithw(_d2_handle);
    d2_closedevice(_d2_handle);
}

static int32_t _CircleAA(int32_t x0, int32_t y0, int32_t r, int32_t w)
{
    uint32_t         Mode;
    int32_t          ret;

    Mode = _GetD2Mode();

    // Generate render operations
    d2_framebuffer(_d2_handle,
                   (uint16_t *)&fb_background[0],
                   LCD_WIDTH,
                   LCD_WIDTH,
                   LCD_HEIGHT,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(_d2_handle, renderbuffer);
    d2_setcolor(_d2_handle, 0, 0xF800);    // green
    d2_cliprect(_d2_handle, 0, 0, LCD_WIDTH, LCD_HEIGHT);
    ret = d2_rendercircle(_d2_handle,
                          (d2_point)(x0 << 4),
                          (d2_point)(y0 << 4),
                          (d2_width)(r << 4),
                          (d2_width)(w << 4));

    // Execute render operations
    d2_executerenderbuffer(_d2_handle, renderbuffer, 0);
    d2_flushframe(_d2_handle);
    while (d2_commandspending(_d2_handle))
    {
        /* Do nothing */
    }

    return ret;
}

int G2D_Test_Draw_Circle()
{
    _CircleAA(240, 100, 50, 10);

    return 0;
}
MSH_CMD_EXPORT(G2D_Test_Draw_Circle, G2D_Draw_Circle);

#ifdef PKG_USING_LVGL
void lv_port_gpu_blit(int32_t      x,
                      int32_t      y,
                      const void  *p,
                      const lv_area_t *area)
{
    uint32_t Mode;
    uint32_t ModeSrc;

    Mode    = _GetD2Mode();
    ModeSrc = d2_mode_rgb565;

    lv_coord_t img_w, img_h;
    img_w = lv_area_get_width(area);
    img_h = lv_area_get_height(area);

    // Generate render operations
    d2_framebuffer(_d2_handle,
                   (uint16_t *)&fb_background[0],
                   LCD_WIDTH,
                   LCD_WIDTH,
                   LCD_HEIGHT,
                   (d2_s32) Mode);

    d2_selectrenderbuffer(_d2_handle, renderbuffer);
    d2_cliprect(_d2_handle, 0, 0, LCD_WIDTH, LCD_HEIGHT);
    d2_setblitsrc(_d2_handle, (void *) p, img_w, img_w, img_h, ModeSrc);
    d2_blitcopy(_d2_handle, img_w, img_h, 0, 0, (d2_width)(img_w << 4), (d2_width)(img_h << 4),
                (d2_point)(x << 4), (d2_point)(y << 4), 0);

    // Execute render operations
    d2_executerenderbuffer(_d2_handle, renderbuffer, 0);

    // In single-buffered mode always wait for DRW to finish before returning
    d2_flushframe(_d2_handle);
}
#endif

void _LCD_FillRect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
{
    uint32_t         Mode;
    int32_t          xSize;
    int32_t          ySize;

    Mode = _GetD2Mode();

    // Generate render operations
    d2_framebuffer(_d2_handle,
                   (uint16_t *)&fb_background[0],
                   LCD_WIDTH,
                   LCD_WIDTH,
                   LCD_HEIGHT,
                   (d2_s32) Mode);
    d2_selectrenderbuffer(_d2_handle, renderbuffer);
    d2_setcolor(_d2_handle, 0, (uint16_t)color);
    d2_setalpha(_d2_handle, 0xff);
    d2_cliprect(_d2_handle, x0, y0, x1, y1);
    xSize = (x1 - x0) + 1;
    ySize = (y1 - y0) + 1;
    d2_renderbox(_d2_handle, (d2_point)(x0 << 4), (d2_point)(y0 << 4), (d2_width)(xSize << 4),
                 (d2_width)(ySize << 4));

    rt_kprintf("color:%#x\n", color);

    // Execute render operations
    d2_executerenderbuffer(_d2_handle, renderbuffer, 0);
    d2_flushframe(_d2_handle);
    d2_setalpha(_d2_handle, UINT8_MAX);

    d2_u8 fillmode_bkup = d2_getfillmode(_d2_handle);
    d2_setfillmode(_d2_handle, fillmode_bkup);
}

int G2D_Test_Draw_FillRect(int argc, const char *argv[])
{
    if (argc > 0)
    {
        _LCD_FillRect(100, 100, 150, 150, 0x00F800);
        _LCD_FillRect(100, 100, 120, 120, 0x0000FF);
        rt_kprintf("x0:%d y0:%d x1:%d y1:%d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    }

    return 0;
}
MSH_CMD_EXPORT(G2D_Test_Draw_FillRect, G2D_Test_Draw_FillRect);
#endif
