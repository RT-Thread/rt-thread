#include <rtthread.h>
#include "board.h"

#include <shell.h>

int platform_init(void)
{
    finsh_system_init();

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

#if defined(RT_USING_MTD_NAND)
    rt_hw_mtd_nand_init();
#endif

#if defined(RT_USING_MTD_NOR)
    sst25vfxx_mtd_init("nor", 0, RT_UINT32_MAX);
#endif

#endif /* RT_USING_DFS */

    return 0;
}

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
