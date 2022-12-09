/*
 * source/ekernel/drivers/drv/source/disp2/soc/platform_resource/platform_resource.h
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
#ifndef _PLATFORM_RESOURCE_H
#define _PLATFORM_RESOURCE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <hal_clk.h>
#include <hal_reset.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * clk_info
 */
struct clk_info_t {
    char name[20];
    hal_clk_id_t clk_id;
    hal_clk_id_t clk_parent_id;
    hal_reset_id_t rst_id;
    hal_clk_t clk;
    hal_clk_t clk_parent;
    struct reset_control *rst;
};

s32 plat_get_reg_base(u32 index, u32 *data);

s32 plat_get_irq_no(u32 index, u32 *data);

s32 plat_get_clk(char *name, hal_clk_id_t *data);

s32 plat_get_clk_parent(hal_clk_id_t clk, hal_clk_id_t * parent);

s32 plat_get_clk_from_id(hal_clk_id_t clk_id, hal_clk_t *clk, struct reset_control **rst);

s32 plat_get_rst_by_name(char *name, struct reset_control **rst);
#ifdef __cplusplus
}
#endif

#endif /*End of file*/
