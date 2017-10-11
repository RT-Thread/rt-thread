/*
 * File      : dc_trans.h
 * This file is part of RT-Thread GUI Engine
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-10     Bernard      first version
 */

#ifndef __RTGUI_DC_TRANS_H__
#define __RTGUI_DC_TRANS_H__

#include <rtgui/dc.h>
#include <rtgui/matrix.h>

struct rtgui_dc_trans;

/** Create a dc translator on the dc @owner
 *
 * @return RT_NULL is there is no memory.
 */
struct rtgui_dc_trans* rtgui_dc_trans_create(struct rtgui_dc *owner);

/** Rotate the dc clockwise.
 *
 * @param degree the degree to rotate.
 */
void rtgui_dc_trans_rotate(struct rtgui_dc_trans *dct, double degree);

void rtgui_dc_trans_set_aa(struct rtgui_dc_trans *dct, int use_aa);

void rtgui_dc_trans_scale(struct rtgui_dc_trans *dct, double sx, double sy);

/** Move the dc
 *
 * The unit of @dx and @dy is pixel.
 */
void rtgui_dc_trans_move(struct rtgui_dc_trans *dct, int dx, int dy);

void rtgui_dc_trans_get_new_wh(struct rtgui_dc_trans *dct, int *new_w, int *new_h);

void rtgui_dc_trans_blit(struct rtgui_dc_trans *dct,
                         struct rtgui_point *dc_point,
                         struct rtgui_dc *dest,
                         struct rtgui_rect *rect);

void rtgui_dc_trans_destroy(struct rtgui_dc_trans *dct);

#endif
