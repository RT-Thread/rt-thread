/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_soc_feature.h"
#include "hpm_plb_drv.h"

void plb_type_b_set_lut(PLB_Type *plb, plb_chn_t chn, plb_type_b_lut_slice_t slice, plb_type_b_slice_opt_t opt)
{
    if (opt >= plb_slice_opt_shift_left) {
        opt = opt >> 8;
        plb->TYPE_B[chn].MODE |= PLB_TYPE_B_MODE_OPT_SEL_SET(1);
    } else {
        plb->TYPE_B[chn].MODE &= ~PLB_TYPE_B_MODE_OPT_SEL_MASK;
    }
    if (slice >= plb_type_b_slice_8) {
        plb->TYPE_B[chn].LUT[1] = (plb->TYPE_B[chn].LUT[1] & (~PLB_TYPE_B_LUT_LOOKUP_TABLE_SET(PLB_SLICE_HIGH_BIT_MASK_SET(slice)))) | PLB_TYPE_B_LUT_LOOKUP_TABLE_SET(opt << PLB_SLICE_HIGH_BIT_SHIFT(slice));
    } else {
        plb->TYPE_B[chn].LUT[0] = (plb->TYPE_B[chn].LUT[0] & (~PLB_TYPE_B_LUT_LOOKUP_TABLE_SET(PLB_SLICE_LOW_BIT_MASK_SET(slice)))) | PLB_TYPE_B_LUT_LOOKUP_TABLE_SET(opt << PLB_SLICE_LOW_BIT_SHIFT(slice));
    }
}
