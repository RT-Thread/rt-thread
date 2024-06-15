/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ov5640.h"

static camera_param_dvp_t camera_dvp_param = {
    .hsync_active_low = true,
    .vsync_active_low = false,
};

static camera_param_mipi_t camera_mipi_param = {
    .de_active_low = true,
    .hsync_active_low = false,
    .vsync_active_low = false,
};

hpm_stat_t camera_device_init(camera_context_t *camera_context, camera_config_t *camera_config)
{
    assert(camera_context->delay_ms != NULL);

    hpm_stat_t stat = status_success;

    /* execute power up sequence */
    ov5640_power_up(camera_context);

    /* software reset */
    stat = ov5640_software_reset(camera_context);
    if (stat != status_success) {
        return stat;
    }
    camera_context->delay_ms(20);

    stat = ov5640_init(camera_context, camera_config);

    return stat;
}

hpm_stat_t camera_device_get_dvp_param(camera_context_t *camera_context, camera_config_t *camera_config)
{
    (void)camera_context;
    camera_config->interface_param = (void *)&camera_dvp_param;
    return status_success;
}

hpm_stat_t camera_device_get_mipi_param(camera_context_t *camera_context, camera_config_t *camera_config)
{
    (void)camera_context;
    camera_config->interface_param = (void *)&camera_mipi_param;
    return status_success;
}
