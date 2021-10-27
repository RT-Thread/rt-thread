/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-03-01     Yangfs       the first version
 * 2015-03-27     Bernard      code cleanup.
 */

/**
 * @addtogroup NRF51822
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_MSH
#include <msh.h>
#include <shell.h>
#endif

int rt_application_init(void)
{
    /* Set finsh device */
#ifdef RT_USING_MSH
    /* initialize finsh */
    finsh_system_init();
#endif
    return 0;
}


/*@}*/
