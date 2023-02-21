/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ov5640.h"

hpm_stat_t camera_device_init(camera_context_t *camera_context, camera_config_t *camera_config)
{
    assert(camera_context->delay_ms != NULL);

    hpm_stat_t stat = status_success;

#ifdef HPM_CAM_EXECUTE_POWER_UP_SEQUENCE
    /* execute power up sequence */
    ov5640_power_up(camera_context);
#endif

    /* software reset */
    stat = ov5640_software_reset(camera_context);
    if (stat != status_success) {
        return stat;
    }
    camera_context->delay_ms(20);

    stat = ov5640_init(camera_context, camera_config);

    return stat;
}

