/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_RESET_H__
#define __SUNXI_RESET_H__

#include <rtthread.h>

struct sunxi_reset_line
{
    rt_uint16_t reg;
    rt_uint32_t mask;
};

struct sunxi_reset_data
{
    const struct sunxi_reset_line *lines;
    rt_size_t lines_nr;
    rt_uint32_t assert_delay_us;
};

extern const struct sunxi_reset_data sun252i_f101_reset_data;

#endif /* __SUNXI_RESET_H__ */
