/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _DISP_SMBL_H_
#define _DISP_SMBL_H_

#include "disp_private.h"

struct disp_smbl *disp_get_smbl(u32 disp);
s32 disp_smbl_shadow_protect(struct disp_smbl *smbl, bool protect);
s32 disp_init_smbl(struct disp_bsp_init_para *para);

#endif
