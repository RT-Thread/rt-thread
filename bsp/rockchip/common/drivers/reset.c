/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-08-30     Tao Huang    The first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "hal_base.h"
#include "hal_bsp.h"

#ifdef RT_USING_RESET
void rt_hw_cpu_reset(void)
{
#ifdef RT_USING_SND_GLB_RST
    HAL_CRU_SetGlbSrst(GLB_SRST_SND);
#else
    HAL_CRU_SetGlbSrst(GLB_SRST_FST);
#endif

    while (1);
}

#ifdef RT_USING_FINSH
#include <finsh.h>

static void reboot(uint8_t argc, char **argv)
{
    if (argc >= 2 && !strncmp(argv[1], "loader", 6))
    {
        BSP_SetLoaderFlag();
    }

    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */
#endif /* RT_USING_RESET */
