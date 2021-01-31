/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>

#include <stdio.h>
#include <stdlib.h>

#ifdef RT_USING_GMAC
#include <drv_gmac.h>
#endif

int main(void)
{
#ifdef RT_USING_GMAC
    rt_app_gk_gmac_init();
#endif

    printf("Hello\n");

    return 0;
}
