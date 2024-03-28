/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     breo.com     first version
 */

#include "drv_common.h"
#include "board.h"

#ifdef RT_USING_SERIAL
    #ifdef RT_USING_SERIAL_V2
        #include "drv_usart_v2.h"
    #else
        #include "drv_usart.h"
    #endif
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */


