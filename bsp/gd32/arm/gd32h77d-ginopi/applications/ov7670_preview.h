/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef OV7670_PREVIEW_H
#define OV7670_PREVIEW_H

#include <rtthread.h>

struct ov7670_preview_status
{
    rt_bool_t ready;
    rt_bool_t active;
    rt_uint32_t frame_count;
    rt_uint32_t display_count;
    rt_uint32_t drop_count;
    rt_uint32_t error_count;
    rt_err_t last_result;
};

void ov7670_preview_init(void);
rt_err_t ov7670_preview_request_start(void);
rt_err_t ov7670_preview_request_stop(void);
void ov7670_preview_get_status(struct ov7670_preview_status *status);

#endif /* OV7670_PREVIEW_H */
