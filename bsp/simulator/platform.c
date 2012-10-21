#include <rtthread.h>
#include "board.h"

void rt_platform_init(void)
{
#ifdef RT_USING_DFS
    /* initilize sd card */
#ifdef RT_USING_DFS_ELMFAT
    rt_hw_sdcard_init();
#endif 

#ifdef RT_USING_MTD_NAND
    rt_hw_mtd_nand_init();
#endif 

#ifdef RT_USING_MTD_NOR
    sst25vfxx_mtd_init("nor", 0, RT_UINT32_MAX);
#endif 

#endif /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
    /* initilize touch panel */
    rtgui_touch_hw_init("spi21");

    /* initilize ra8875 lcd controller */
    ra8875_init();

    /* initilize key module */
    rt_hw_key_init();
#endif /* RT_USING_RTGUI */

    rt_thread_delay(50);
    rt_device_init_all();
}

