#include <rtthread.h>
#include "board.h"

void rt_platform_init(void)
{
#ifdef RT_USING_DFS
    /* initilize sd card */
    rt_hw_sdcard_init();

#if defined(RT_USING_MTD_NAND)
    rt_hw_mtd_nand_init();
#endif 

#if defined(RT_USING_MTD_NOR)
    sst25vfxx_mtd_init("nor", 0, RT_UINT32_MAX);
#endif 

#endif /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
    /* initilize sdl */
    sdl_start();
#endif /* RT_USING_RTGUI */

    rt_thread_delay(50);
    rt_device_init_all();
}

