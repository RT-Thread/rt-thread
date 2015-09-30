#include <rtthread.h>
#include "board.h"

void platform_init(void)
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

#if defined(RT_USING_MTD_NAND)
    rt_hw_mtd_nand_init();
#endif

#if defined(RT_USING_MTD_NOR)
    sst25vfxx_mtd_init("nor", 0, RT_UINT32_MAX);
#endif

#endif /* RT_USING_DFS */
}

