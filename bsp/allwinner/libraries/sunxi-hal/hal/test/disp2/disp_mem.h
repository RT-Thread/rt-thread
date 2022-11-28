/*
 * source/ekernel/drivers/test/disp2/disp_mem/disp_mem.h
 *
 * Copyright (c) 2007-2020 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
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
#ifndef _DISP_MEM_H
#define _DISP_MEM_H

#ifdef __cplusplus
extern "C" {
#endif
#include <video/sunxi_display2.h>

int disp_mem(u32 mem_id, u32 width, u32 height, u32 clear_flag, char *filename);
int disp_mem_clear(u32 mem_id);
u32 disp_mem_getadr(u32 memid);

#ifdef __cplusplus
}
#endif

#endif /*End of file*/
