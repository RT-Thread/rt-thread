/*
 * drivers/char/sunxi_g2d/g2d_rcq/g2d_rotate.h
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
#ifndef _G2D_ROTATE_H
#define _G2D_ROTATE_H
#include "g2d_driver.h"

__s32 g2d_rotate_set_para(g2d_image_enh *src, g2d_image_enh *dst, __u32 flag);
__s32 g2d_lbc_rot_set_para(g2d_lbc_rot *para);
void g2d_rot_set_base(unsigned long base);
__s32 g2d_rot_irq_query(void);

#endif /*End of file*/

