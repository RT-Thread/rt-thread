/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_dao_drv.h"
#include "hpm_i2s_common.h"

void dao_get_default_config(DAO_Type *ptr, dao_config_t *config)
{
    (void) ptr;
    config->enable_mono_output = false;
    config->default_output_level = DAO_DEFAULT_OUTPUT_ALL_LOW;
    config->channel_count = 2;
#if defined(HPM_IP_FEATURE_DAO_DATA_FORMAT_CONFIG) && (HPM_IP_FEATURE_DAO_DATA_FORMAT_CONFIG == 1)
    config->enable_tdm_mode = false;
    config->frame_start_at_rising_edge = false;
    config->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
    config->channel_length = i2s_channel_length_32_bits;
    config->audio_depth = i2s_audio_depth_32_bits;
#endif
    config->channel_slot_mask = 0x3; /* 2 channel mask */
}

hpm_stat_t dao_init(DAO_Type *ptr, dao_config_t *config)
{
    if (dao_is_running(ptr)) {
        dao_stop(ptr);
    }
    dao_software_reset(ptr);

    ptr->CTRL = DAO_CTRL_MONO_SET(config->enable_mono_output)
        | DAO_CHANNEL_BOTH
        | DAO_CTRL_REMAP_MASK
        | DAO_CTRL_FALSE_LEVEL_SET(config->default_output_level);

#if defined(HPM_IP_FEATURE_DAO_DATA_FORMAT_CONFIG) && (HPM_IP_FEATURE_DAO_DATA_FORMAT_CONFIG == 1)
    ptr->RX_CFGR = DAO_RX_CFGR_FRAME_EDGE_SET(config->frame_start_at_rising_edge)
                | DAO_RX_CFGR_CH_MAX_SET(config->channel_count)
                | DAO_RX_CFGR_TDM_EN_SET(config->enable_tdm_mode)
                | DAO_RX_CFGR_STD_SET(config->protocol)
                | DAO_RX_CFGR_DATSIZ_SET(I2S_CFGR_DATASIZ(config->audio_depth))
                | DAO_RX_CFGR_CHSIZ_SET(I2S_CFGR_CHSIZ(config->channel_length));
#else
    ptr->RX_CFGR = DAO_RX_CFGR_CH_MAX_SET(config->channel_count);
#endif

    ptr->RXSLT = config->channel_slot_mask;

    return status_success;
}

