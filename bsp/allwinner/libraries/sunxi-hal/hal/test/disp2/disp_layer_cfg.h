/*
 * disp_common/disp_common.h
 *
 * Copyright (c) 2007-2020 Allwinnertech Co., Ltd.
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
#ifndef _DISP_COMMON_H
#define _DISP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <rtthread.h>
#include <log.h>
#include <hal_mem.h>
#include <video/sunxi_display2.h>


struct test_layer_cfg
{
    int screen_id;
    int layer_id;
    int mem_id;
    struct disp_layer_config layer_cfg;
    int addr_map;
    int width,height;//screen size
    FILE *fh;//picture resource file handle
    void* mem;
    int clear;//is clear layer
    int fullscreen;//is full screen
    char filename[32];
};

int disp_layer_cfg(struct test_layer_cfg *test_cfg);
int disp_layer_clear_all(u32 screen_index);
int disp_layer_clear(u32 screen_index, u32 chn, u32 layer);
int disp_layer_get_resolution(u32 screen_index, u32 *width, u32 *height);

#ifdef __cplusplus
}
#endif

#endif /*End of file*/
