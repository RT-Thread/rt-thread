/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "board.h"

int platform_init(void)
{
#ifdef RT_USING_LWIP
#ifdef RT_USING_TAPNETIF
    tap_netif_hw_init();
#else
    pcap_netif_hw_init();
#endif
#endif

#ifdef RT_USING_DFS
    /* initialize sd card */
    rt_hw_sdcard_init();

#ifdef RT_USING_MTD_NAND
    rt_hw_mtd_nand_init();
#endif /* RT_USING_MTD_NAND */

#ifdef RT_USING_MTD_NOR
    sst25vfxx_mtd_init("nor", 0, RT_UINT32_MAX);
#endif /* RT_USING_MTD_NOR */

#endif /* RT_USING_DFS */

    return 0;
}
INIT_COMPONENT_EXPORT(platform_init);

int platform_post_init(void)
{
#ifdef PKG_USING_GUIENGINE
    {
        extern void rt_hw_sdl_start(void);
        extern int rtgui_system_server_init(void);

        rtgui_system_server_init();
        rt_hw_sdl_start();
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(platform_post_init);
