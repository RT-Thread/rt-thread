/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2025-04-26     GuEe-GUI     init common
 */

#include <setup.h>

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
