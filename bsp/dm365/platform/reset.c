/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */


#include <rthw.h>
#include <rtthread.h>
#include "dm36x.h"

/**
 * @addtogroup DM36X
 */
/*@{*/

/**
 * reset cpu by dog's time-out
 *
 */
void machine_reset()
{
    reset_system();
}

/**
 *  shutdown CPU
 *
 */
void machine_shutdown()
{

}

#ifdef RT_USING_FINSH

#include <finsh.h>

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
