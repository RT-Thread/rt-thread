/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    the first version
 */

#include <rtthread.h>

#ifdef RT_USING_MSH
#include <shell.h>
#include <msh.h>
#endif

/**
 * @addtogroup LPC2478
 */
/*@{*/
int rt_application_init()
{
#ifdef RT_USING_MSH
    /* init finsh */
    finsh_system_init();
#endif

    return 0;
}

/*@}*/
