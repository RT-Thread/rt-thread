/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

int rt_application_init(void)
{
    /* Set finsh device */
#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
#endif
    return 0;
}


/*@}*/
