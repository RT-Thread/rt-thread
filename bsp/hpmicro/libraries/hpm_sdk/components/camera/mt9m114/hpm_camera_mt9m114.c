/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_mt9m114.h"

static camera_param_dvp_t camera_dvp_param = {
    .hsync_active_low = true,
    .vsync_active_low = true,
};

hpm_stat_t camera_device_init(camera_context_t *camera_context, camera_config_t *camera_config)
{
    assert(camera_context->delay_ms != NULL);

    hpm_stat_t stat = status_success;

    /* first check chipid */
    stat = mt9m114_check_chip_id(camera_context);
    if (stat != status_success) {
        return stat;
    }

    /* software reset */
    stat = mt9m114_software_reset(camera_context);
    if (stat != status_success) {
        return stat;
    }
    camera_context->delay_ms(20);

    stat = mt9m114_init(camera_context, camera_config);

    return stat;
}

hpm_stat_t camera_device_get_dvp_param(camera_context_t *camera_context, camera_config_t *camera_config)
{
    camera_config->interface_param = (void *)&camera_dvp_param;
    return status_success;
}
