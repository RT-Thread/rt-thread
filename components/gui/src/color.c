/*
 * File      : color.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtgui/color.h>

const rtgui_color_t red     = RTGUI_RGB(0xff, 0x00, 0x00);
const rtgui_color_t green   = RTGUI_RGB(0x00, 0xff, 0x00);
const rtgui_color_t blue    = RTGUI_RGB(0x00, 0x00, 0xff);
const rtgui_color_t black   = RTGUI_RGB(0x00, 0x00, 0x00);
const rtgui_color_t white   = RTGUI_RGB(0xff, 0xff, 0xff);

const rtgui_color_t high_light  = RTGUI_RGB(0xfc, 0xfc, 0xfc);
const rtgui_color_t dark_grey   = RTGUI_RGB(0x7f, 0x7f, 0x7f);
const rtgui_color_t light_grey  = RTGUI_RGB(0xc0, 0xc0, 0xc0);

const static rt_uint8_t pixel_bits_table[] =
{
    1, /* mono */
    2, /* 4 level for gray */
    4, /* 16 level for gray */
    8, /* RGB332 */
    12, /* RGB444 */
    16, /* RGB565 */
    16, /* BGR565 */
    18, /* RGB666 */
    24, /* RGB888 */
    32, /* ARGB888 */
};

rt_uint8_t rtgui_color_get_bits(rt_uint8_t pixel_format)
{
    if (pixel_format <= RTGRAPHIC_PIXEL_FORMAT_ARGB888)
        return pixel_bits_table[pixel_format];

    /* use 32 as the default */
    return 32;
}
RTM_EXPORT(rtgui_color_get_bits);

rt_uint8_t rtgui_color_get_bpp(rt_uint8_t pixel_format)
{
    rt_uint8_t bpp = 4;

    if (pixel_format <= RTGRAPHIC_PIXEL_FORMAT_ARGB888)
    {
        bpp = _UI_BITBYTES(pixel_bits_table[pixel_format]);
    }

    return bpp;
}
RTM_EXPORT(rtgui_color_get_bpp);
