#include <rtthread.h>
#include <board.h>

#ifdef RT_USING_LWIP
#include "stm32_eth.h"
#endif /* RT_USING_LWIP */

void rt_platform_init(void)
{
#ifdef RT_USING_LWIP
    /* initialize eth interface */
    rt_hw_stm32_eth_init();
#endif /* RT_USING_LWIP */

#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
    /* init sdcard driver */
    {
        extern void rt_hw_msd_init(void);
        rt_hw_msd_init();
    }
#endif /* RT_USING_DFS && RT_USING_DFS_ELMFAT */
}
