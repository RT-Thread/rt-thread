/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      modified from mini2440
 */

#include <rthw.h>
#include <rtthread.h>
#include "at91sam926x.h"

/**
 * @addtogroup AT91SAM926X
 */
/*@{*/

void machine_reset(void)
{
    at91_sys_write(AT91_RSTC_CR, AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST);
}

void machine_shutdown(void)
{
    at91_sys_write(AT91_SHDW_CR, AT91_SHDW_KEY | AT91_SHDW_SHDW);
}

#ifdef RT_USING_FINSH

#ifdef FINSH_USING_MSH
int cmd_reset(int argc, char** argv)
{
    rt_hw_cpu_reset();
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_reset, reset, restart the system);

int cmd_shutdown(int argc, char** argv)
{
    rt_hw_cpu_shutdown();
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_shutdown, shutdown, shutdown the system);

#endif
#endif

/*@}*/
