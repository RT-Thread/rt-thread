/*
 * g2d_bsp/g2d_bsp.h
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef __G2D_BSP_H
#define __G2D_BSP_H
#include <log.h>

#include <stdlib.h>
#include <string.h>


#include <sunxi_hal_common.h>
#include <hal_log.h>
#include "g2d_driver.h"
#include <hal_mem.h>

#define G2D_FINISH_IRQ		(1<<8)
#define G2D_ERROR_IRQ			(1<<9)

extern __u32 dbg_info;

#define G2D_INFO_MSG(fmt, ...) \
	do {\
		if (dbg_info)\
			hal_log_info("g2d: [%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);\
	} while (0)

#define G2D_ERR_MSG(fmt, ...) \
	do {\
			hal_log_err("g2d: [%s %d]"fmt, __func__, __LINE__, ##__VA_ARGS__);\
	} while (0)

typedef struct {
	unsigned long g2d_base;
} g2d_init_para;

typedef struct {
	g2d_init_para init_para;
} g2d_dev_t;

typedef enum {
	G2D_RGB2YUV_709,
	G2D_YUV2RGB_709,
	G2D_RGB2YUV_601,
	G2D_YUV2RGB_601,
	G2D_RGB2YUV_2020,
	G2D_YUV2RGB_2020,
} g2d_csc_sel;

typedef enum {
	VSU_FORMAT_YUV422 = 0x00,
	VSU_FORMAT_YUV420 = 0x01,
	VSU_FORMAT_YUV411 = 0x02,
	VSU_FORMAT_RGB = 0x03,
	VSU_FORMAT_BUTT = 0x04,
} vsu_pixel_format;

#define VSU_ZOOM0_SIZE	1
#define VSU_ZOOM1_SIZE	8
#define VSU_ZOOM2_SIZE	4
#define VSU_ZOOM3_SIZE	1
#define VSU_ZOOM4_SIZE	1
#define VSU_ZOOM5_SIZE	1

#define VSU_PHASE_NUM            32
#define VSU_PHASE_FRAC_BITWIDTH  19
#define VSU_PHASE_FRAC_REG_SHIFT 1
#define VSU_FB_FRAC_BITWIDTH     32

#define VI_LAYER_NUMBER 1
#define UI_LAYER_NUMBER 3


#endif	/* __G2D_BSP_H */

