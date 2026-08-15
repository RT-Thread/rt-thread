/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 * 2021-12-28     GuEe-GUI       add smp support
 */

#include <setup.h>
#include <board.h>

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
