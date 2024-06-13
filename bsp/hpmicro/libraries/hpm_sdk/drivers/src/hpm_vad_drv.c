/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_vad_drv.h"

void vad_get_default_config(VAD_Type *ptr, vad_config_t *config)
{
    (void) ptr;
    config->enable_buffer = true;
    config->enable_pdm_clock_out = true;
    config->enable_two_channels = true;
    config->capture_delay = 1;
    config->pdm_half_div = 3;
    config->fifo_threshold = 4;
    config->channel_polarity_high[0] = false;
    config->channel_polarity_high[1] = true;
    config->post_scale = 20;
}

void vad_init(VAD_Type *ptr, vad_config_t *config)
{
    vad_reset(ptr);
    ptr->CTRL = VAD_CTRL_PDM_CLK_HFDIV_SET(config->pdm_half_div)
        | VAD_CTRL_PDM_CLK_OE_SET(config->enable_pdm_clock_out)
        | VAD_CTRL_MEMBUF_DISABLE_SET(!config->enable_buffer)
        | VAD_CTRL_FIFO_THRSH_SET(config->fifo_threshold)
        | VAD_CTRL_CAPT_DLY_SET(config->capture_delay)
        | VAD_CTRL_CHNUM_SET(config->enable_two_channels)
        | VAD_CTRL_CH_POL_SET((config->channel_polarity_high[1] << 1)
                | config->channel_polarity_high[0]);
    ptr->FILTCTRL = VAD_FILTCTRL_DECRATIO_SET(2)
        | VAD_FILTCTRL_IIR_SLOT_EN_SET(0xff);
    ptr->CIC_CFG = (ptr->CIC_CFG & ~VAD_CIC_CFG_POST_SCALE_MASK)
        | VAD_CIC_CFG_POST_SCALE_SET(config->post_scale);

    vad_enable_fifo(ptr);
}

void vad_reset(VAD_Type *ptr)
{
    if (vad_is_running(ptr)) {
        vad_stop(ptr);
    }
    vad_software_reset(ptr);
}

