/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_dao_drv.h"

void dao_get_default_config(DAO_Type *ptr, dao_config_t *config)
{
    config->enable_mono_output = false;
    config->default_output_level = DAO_DEFAULT_OUTPUT_ALL_LOW;
    config->channel_count = 2;
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
    ptr->RX_CFGR = DAO_RX_CFGR_CH_MAX_SET(config->channel_count);
    if (config->channel_count < 31) {
        ptr->RXSLT = (1 << config->channel_count) - 1;
    } else if (config->channel_count == 32) {
        ptr->RXSLT = 0xFFFFFFFF;
    } else {
        /* channel count is not correct */
        return status_fail;
    }
    return status_success;
}

