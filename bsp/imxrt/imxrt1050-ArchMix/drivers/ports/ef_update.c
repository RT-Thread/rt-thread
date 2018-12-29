/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-29     flybreak     first implementation
 */

#include <easyflash.h>
#include <rtthread.h>
#include <fsl_wdog.h>

void reset(void)
{
    SCB->AIRCR = 0x05fa0000 | 0x04UL;
    while (1)
    {
    }
}
MSH_CMD_EXPORT(reset, reset system.);

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) && defined(EF_USING_ENV)
#include <finsh.h>
#if defined(EF_USING_ENV)

static void update(uint8_t argc, char **argv)
{
    ef_set_env("check_upgrade", "1");
    ef_save_env();
    reset();
}
MSH_CMD_EXPORT(update, reset and check update.);

#endif /* defined(EF_USING_ENV) */
#endif /* defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) */
