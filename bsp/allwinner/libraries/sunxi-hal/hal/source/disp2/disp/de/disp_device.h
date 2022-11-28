/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DISP_DEVICE_H__
#define __DISP_DEVICE_H__

#include "disp_private.h"

s32 disp_device_set_manager(struct disp_device *dispdev,
                struct disp_manager *mgr);
s32 disp_device_unset_manager(struct disp_device *dispdev);
s32 disp_device_get_resolution(struct disp_device *dispdev, u32 *xres,
                   u32 *yres);
s32 disp_device_get_timings(struct disp_device *dispdev,
                struct disp_video_timings *timings);
s32 disp_device_is_interlace(struct disp_device *dispdev);
s32 disp_device_get_status(struct disp_device *dispdev);
bool disp_device_is_in_safe_period(struct disp_device *dispdev);
u32 disp_device_usec_before_vblank(struct disp_device *dispdev);
s32 disp_device_register(struct disp_device *dispdev);
s32 disp_device_unregister(struct disp_device *dispdev);
struct disp_device *disp_device_get(int disp,
                    enum disp_output_type output_type);
struct disp_device *disp_device_find(int disp,
                     enum disp_output_type output_type);
struct list_head *disp_device_get_list_head(void);

/**
 * @name       :disp_device_get_from_priv
 * @brief      :get disp_device by comparing pointer of priv_data
 * @param[IN]  :priv_data:pointer of private date of disp_device
 * @return     :pointer of disp_device; NULL if not found
 */
struct disp_device *disp_device_get_from_priv(void *priv_data);
void disp_device_show_builtin_patten(struct disp_device *dispdev, u32 patten);

#endif
