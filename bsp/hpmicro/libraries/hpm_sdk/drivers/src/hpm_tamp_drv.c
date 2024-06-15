/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_tamp_drv.h"

void tamp_init_ch_config(TAMP_Type *ptr, uint8_t ch, tamper_ch_config_t *config)
{
    ch >>= 1u;
    ptr->TAMP[ch].CONTROL = TAMP_TAMP_CONTROL_BYPASS_SET(config->filter_bypass)
                          | TAMP_TAMP_CONTROL_FILTER_SET(config->filter_len)
                          | TAMP_TAMP_CONTROL_VALUE_SET(config->expect_high_level)
                          | TAMP_TAMP_CONTROL_SPEED_SET(config->speed)
                          | TAMP_TAMP_CONTROL_RECOVER_SET(config->auto_recover)
                          | TAMP_TAMP_CONTROL_ACTIVE_SET(config->active_mode)
                          | TAMP_TAMP_CONTROL_ENABLE_SET(config->enable);
    ptr->TAMP[ch].POLY = config->poly;
    ptr->TAMP[ch].LFSR = config->lfsr;
}

void tamp_get_default_ch_config(TAMP_Type *ptr, tamper_ch_config_t *config)
{
    (void) ptr;
    config->enable = false;
    config->active_mode = false;
    config->expect_high_level = false;
    config->filter_bypass = false;
    config->filter_len = filter_len_128_cycles;
    config->speed = spd_1_time_per_sec;
    config->auto_recover = false;
    config->poly = 0;
    config->lfsr = 0;
}
