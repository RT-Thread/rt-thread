/*
 * File      : sd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 */

#ifndef __SD_H__
#define __SD_H__

#include <rtthread.h>
#include <drivers/mmcsd_host.h>

#ifdef __cplusplus
extern "C" {
#endif

rt_err_t mmcsd_send_if_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr);
rt_err_t mmcsd_send_app_op_cond(struct rt_mmcsd_host *host, rt_uint32_t ocr, rt_uint32_t *rocr);
rt_int32_t init_sd(struct rt_mmcsd_host *host, rt_uint32_t ocr);

#ifdef __cplusplus
}
#endif

#endif
