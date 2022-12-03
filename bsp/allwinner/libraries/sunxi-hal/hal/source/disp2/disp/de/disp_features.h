/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _DISP_FEATURES_H_
#define _DISP_FEATURES_H_

/*#include "include.h"*/
#if defined(CONFIG_ARCH_SUN8IW6)
#include "lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW7)
#include "lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW8)
#include "lowlevel_sun8iw8/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW9)
#include "lowlevel_sun8iw9/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW10)
#include "./lowlevel_sun8iw10/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW11)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN50IW1)
#include "./lowlevel_sun50iw1/de_feat.h"
#elif defined(CONFIG_ARCH_SUN50IW2)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN50IW8)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW12) || defined(CONFIG_ARCH_SUN8IW16)\
    || defined(CONFIG_ARCH_SUN8IW19) || defined(CONFIG_ARCH_SUN20IW1)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN8IW15) || defined(CONFIG_ARCH_SUN8IW17)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN50IW10)
#include "./lowlevel_v2x/de_feat.h"
#elif defined(CONFIG_ARCH_SUN50IW3) || defined(CONFIG_ARCH_SUN50IW6)
#include "./lowlevel_v3x/de_feat.h"
#else
#error "undefined platform!!!"
#endif

#define DISP_DEVICE_NUM DEVICE_NUM
#define DISP_SCREEN_NUM DE_NUM

struct disp_features {
    const s32 num_screens;
    const s32 *num_channels;
    const s32 *num_layers;
    const s32 *is_support_capture;
    const s32 *supported_output_types;
};

s32 bsp_disp_feat_get_num_screens(void);
s32 bsp_disp_feat_get_num_devices(void);
s32 bsp_disp_feat_get_num_channels(u32 disp);
s32 bsp_disp_feat_get_num_layers(u32 screen_id);
s32 bsp_disp_feat_get_num_layers_by_chn(u32 disp, u32 chn);
s32 bsp_disp_feat_is_supported_output_types(u32 screen_id,
                        u32 output_type);
s32 bsp_disp_feat_is_support_capture(u32 disp);
s32 bsp_disp_feat_is_support_smbl(u32 disp);
s32 bsp_disp_feat_is_support_enhance(u32 disp);
u32 bsp_disp_feat_get_num_vdpo(void);
s32 disp_init_feat(void);
s32 disp_exit_feat(void);

#endif
