/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-11     liYony       the first version
 * 2024-07-07     GuEe-GUI     init common
 */

#include <setup.h>

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
