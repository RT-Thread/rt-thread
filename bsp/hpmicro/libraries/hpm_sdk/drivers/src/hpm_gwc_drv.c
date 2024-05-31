/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_gwc_drv.h"

void gwc_get_default_config(gwc_config_t *cfg)
{
    cfg->clk_pol = gwc_clk_pol_normal;
}

void gwc_init(GWC_Type *ptr, gwc_config_t *cfg)
{
    ptr->GLB_CTRL = cfg->clk_pol;
}

void gwc_enable(GWC_Type *ptr)
{
    ptr->GLB_CTRL |= GWC_GLB_CTRL_GWC_EN_MASK;
}

void gwc_disable(GWC_Type *ptr)
{
    ptr->GLB_CTRL &= ~GWC_GLB_CTRL_GWC_EN_MASK;
}

void gwc_freeze_interrupt_control(GWC_Type *ptr)
{
    ptr->IRQ_MASK |= GWC_IRQ_MASK_MASK_RREEZ_MASK;
}

void gwc_ch_init(GWC_Type *ptr, uint8_t ch_index, gwc_ch_config_t *cfg)
{
    assert(ch_index <= GWC_CHANNEL_CH15);
    ptr->CHANNEL[ch_index].CFG0 = GWC_CHANNEL_CFG0_START_ROW_SET(cfg->start_row) |
                                GWC_CHANNEL_CFG0_START_COL_SET(cfg->start_col) |
                                (cfg->freeze ? GWC_CHANNEL_CFG0_FREEZE_MASK : 0);
    ptr->CHANNEL[ch_index].CFG1 = GWC_CHANNEL_CFG1_END_ROW_SET(cfg->end_row) |
                                GWC_CHANNEL_CFG1_END_COL_SET(cfg->end_col);
    ptr->CHANNEL[ch_index].REFCRC = cfg->ref_crc;
}