/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */


#include <rtthread.h>
#include "dm36x.h"

extern int davinci_clk_init(void);

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{
    davinci_clk_init();
}

