/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DISP_VDEVICE_H__
#define __DISP_VDEVICE_H__

#include "disp_private.h"
#include "disp_display.h"

extern struct disp_dev_t gdisp;
struct disp_device *disp_vdevice_register(struct disp_vdevice_init_data *data);
s32 disp_vdevice_unregister(struct disp_device *vdevice);
s32 disp_vdevice_get_source_ops(struct disp_vdevice_source_ops *ops);

#endif
