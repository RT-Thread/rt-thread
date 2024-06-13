/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_pdm_drv.h"
#define PDM_WORKING_CLOCK_FREQ_IN_HZ (48000UL)

void pdm_get_default_config(PDM_Type *ptr, pdm_config_t *config)
{
    (void) ptr;
    config->sof_at_ref_clk_falling_edge = true;
    config->bypass_pdm_clk_div = false;
    config->enable_pdm_clk_out = true;
    config->pdm_clk_div = 3;
    config->capture_delay = 1;
    config->dec_after_cic = 3;
    config->post_scale = 12;
    config->sigma_delta_order = PDM_CIC_SIGMA_DELTA_ORDER_6;
    config->cic_dec_ratio = 64;
    config->enable_hpf = true;
}

hpm_stat_t pdm_init(PDM_Type *ptr, pdm_config_t *config)
{
    if (pdm_is_running(ptr)) {
        pdm_stop(ptr);
    }
    /* pdm_software_reset(ptr); */

    /* ptr->CTRL = PDM_CTRL_DIS_CLK_GATE_MASK; */
    ptr->CTRL = PDM_CTRL_SOF_FEDGE_SET(config->sof_at_ref_clk_falling_edge)
        | PDM_CTRL_DEC_AFT_CIC_SET(config->dec_after_cic)
        | PDM_CTRL_CAPT_DLY_SET(config->capture_delay)
        | PDM_CTRL_PDM_CLK_HFDIV_SET(config->pdm_clk_div)
        | PDM_CTRL_PDM_CLK_DIV_BYPASS_SET(config->bypass_pdm_clk_div)
        | PDM_CTRL_PDM_CLK_OE_SET(config->enable_pdm_clk_out)
        | PDM_CTRL_HPF_EN_SET(config->enable_hpf);

    ptr->CH_CTRL = 0xF000FF;
    ptr->CH_CFG = 0x50000;
    ptr->CIC_CFG = PDM_CIC_CFG_POST_SCALE_SET(config->post_scale)
        | PDM_CIC_CFG_SGD_SET(config->sigma_delta_order)
        | PDM_CIC_CFG_CIC_DEC_RATIO_SET(config->cic_dec_ratio);

    return status_success;
}
