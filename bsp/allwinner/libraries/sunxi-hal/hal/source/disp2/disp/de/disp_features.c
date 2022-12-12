/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#include "include.h"
#include "disp_features.h"
#include <sunxi_hal_common.h>
s32 bsp_disp_feat_get_num_screens(void)
{
    return de_feat_get_num_screens();
}

s32 bsp_disp_feat_get_num_devices(void)
{
    return de_feat_get_num_devices();
}

s32 bsp_disp_feat_get_num_channels(u32 disp)
{
    return de_feat_get_num_chns(disp);
}

s32 bsp_disp_feat_get_num_layers(u32 disp)
{
    return de_feat_get_num_layers(disp);
}

s32 bsp_disp_feat_get_num_layers_by_chn(u32 disp, u32 chn)
{
    return de_feat_get_num_layers_by_chn(disp, chn);
}

/**
 * Query whether specified timing controller support the output_type spcified
 * @disp: the index of timing controller
 * @output_type: the display output type
 * On support, returns 1. Otherwise, returns 0.
 */
s32 bsp_disp_feat_is_supported_output_types(u32 disp,
                        u32 output_type)
{
    return de_feat_is_supported_output_types(disp, output_type);
}

s32 bsp_disp_feat_is_support_smbl(u32 disp)
{
    return de_feat_is_support_smbl(disp);
}

s32 bsp_disp_feat_is_support_capture(u32 disp)
{
    return de_feat_is_support_wb(disp);
}

s32 bsp_disp_feat_is_support_enhance(u32 disp)
{
    return de_feat_is_support_vep(disp);
}

s32 disp_init_feat(void)
{
    return de_feat_init();
}

s32 disp_exit_feat(void)
{
    return de_feat_exit();
}

u32 bsp_disp_feat_get_num_vdpo(void)
{
    return de_feat_get_number_of_vdpo();
}
