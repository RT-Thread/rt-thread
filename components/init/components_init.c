#include <rtthread.h>
#include "components_init.h"

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#endif

#ifdef RT_USING_DFS
#endif

void rt_components_init(void)
{
#ifdef RT_USING_LWIP
	/* initialize lwip stack */
    extern void lwip_sys_init(void);

    /* register ethernetif device */
    eth_system_device_init();

    /* initialize lwip system */
    lwip_sys_init();
    rt_kprintf("TCP/IP initialized!\n");
#endif

#ifdef RT_USING_DFS
	/* initialize the device filesystem */
	dfs_init();

#ifdef RT_USING_DFS_ELMFAT
	/* initialize the elm chan FatFS filesystam*/
	elm_init();
#endif

#if defined(RT_USING_DFS_NFS) && defined(RT_USING_LWIP)
	extern void nfs_init(void);
	/* initialize NFSv3 client filesystem */
	nfs_init();
#endif

#ifdef RT_USING_DFS_YAFFS2
	yaffs2_init();
#endif

#ifdef RT_USING_DFS_UFFS
	uffs_init();
#endif

#ifdef RT_USING_DFS_JFFS2
	jffs2_init();
#endif

#ifdef RT_USING_DFS_ROMFS
	romfs_init();
#endif

#ifdef RT_USING_DFS_DEVFS
	devfs_init();
#endif

#endif

#ifdef RT_USING_RTGUI
#endif

	return;
}
