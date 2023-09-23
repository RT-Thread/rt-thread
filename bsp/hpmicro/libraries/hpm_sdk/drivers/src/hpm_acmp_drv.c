/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_acmp_drv.h"

hpm_stat_t acmp_channel_config(ACMP_Type *ptr, uint8_t ch, acmp_channel_config_t *config, bool enable)
{
    acmp_channel_enable_cmp(ptr, ch, false);
    ptr->CHANNEL[ch].CFG = ACMP_CHANNEL_CFG_CMPEN_SET(enable)
                    | ACMP_CHANNEL_CFG_MINSEL_SET(config->minus_input)
                    | ACMP_CHANNEL_CFG_PINSEL_SET(config->plus_input)
                    | ACMP_CHANNEL_CFG_FLTMODE_SET(config->filter_mode)
                    | ACMP_CHANNEL_CFG_HYST_SET(config->hyst_level)
                    | ACMP_CHANNEL_CFG_CMPOEN_SET(config->enable_cmp_output)
                    | ACMP_CHANNEL_CFG_WINEN_SET(config->enable_window_mode)
                    | ACMP_CHANNEL_CFG_OPOL_SET(config->invert_output)
                    | ACMP_CHANNEL_CFG_SYNCEN_SET(config->enable_clock_sync)
                    | ACMP_CHANNEL_CFG_FLTBYPS_SET(config->bypass_filter)
                    | ACMP_CHANNEL_CFG_DACEN_SET(config->enable_dac)
                    | ACMP_CHANNEL_CFG_HPMODE_SET(config->enable_hpmode)
                    | ACMP_CHANNEL_CFG_FLTLEN_SET(config->filter_length);
    if (enable) {
        acmp_channel_enable_cmp(ptr, ch, true);
    }
    return status_success;
}

void acmp_channel_get_default_config(ACMP_Type *ptr, acmp_channel_config_t *config)
{
    config->plus_input = ACMP_INPUT_DAC_OUT;
    config->minus_input = ACMP_INPUT_DAC_OUT;
    config->filter_mode = ACMP_FILTER_MODE_BYPASS;
    config->hyst_level = ACMP_HYST_LEVEL_0;
    config->enable_cmp_output = false;
    config->enable_window_mode = false;
    config->invert_output = false;
    config->enable_clock_sync = false;
    config->bypass_filter = true;
    config->enable_dac = false;
    config->enable_hpmode = false;
    config->filter_length = 0;
}

