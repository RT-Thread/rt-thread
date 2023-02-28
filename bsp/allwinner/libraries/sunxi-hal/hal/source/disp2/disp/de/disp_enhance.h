/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _DISP_ENHANCE_H_
#define _DISP_ENHANCE_H_

#include "disp_private.h"

static s32 disp_enhance_shadow_protect(struct disp_enhance *enhance,
                       bool protect);
s32 disp_init_enhance(struct disp_bsp_init_para *para);

s32 disp_enhance_set_para(struct disp_enhance *enhance,
              struct disp_enhance_para *para);

#endif
