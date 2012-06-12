#include <rtthread.h>
#include "components_init.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <netif/ethernetif.h>
extern void lwip_system_init(void);
#endif

#ifdef RT_USING_DFS
#include <dfs_init.h>
#ifdef RT_USING_DFS_ELMFAT
#include <dfs_elm.h>
#endif
#ifdef RT_USING_DFS_NFS
#include <dfs_nfs.h>
#endif
#ifdef RT_USING_DFS_ROMFS
#include <dfs_romfs.h>
#endif
#ifdef RT_USING_DFS_DEVFS
#include <devfs.h>
#endif
#ifdef RT_USING_DFS_UFFS
#include <dfs_uffs.h>
#endif
#ifdef RT_USING_DFS_JFFS2
#include <dfs_jffs2.h>
#endif
#ifdef RT_USING_DFS_YAFFS2
#include <dfs_yaffs2.h>
#endif
#endif

#ifdef RT_USING_NEWLIB
#include <libc.h>
#endif
#ifdef RT_USING_PTHREADS
#include <pthread.h>
#endif

/**
 * RT-Thread Components Initialization
 */
void rt_components_init(void)
{
#ifdef RT_USING_MODULE
	rt_system_module_init();
#endif

#ifdef RT_USING_FINSH
	/* initialize finsh */
	finsh_system_init();
	finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_LWIP
	/* initialize lwip stack */
    /* register ethernetif device */
    eth_system_device_init();

    /* initialize lwip system */
    lwip_system_init();
    rt_kprintf("TCP/IP initialized!\n");
#endif

#ifdef RT_USING_DFS
	/* initialize the device file system */
	dfs_init();

#ifdef RT_USING_DFS_ELMFAT
	/* initialize the elm chan FatFS file systam*/
	elm_init();
#endif

#if defined(RT_USING_DFS_NFS) && defined(RT_USING_LWIP)
	extern void nfs_init(void);
	/* initialize NFSv3 client file system */
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

#ifdef RT_USING_NEWLIB
	libc_system_init(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_PTHREADS 
	pthread_system_init();
#endif

#ifdef RT_USING_RTGUI
	rtgui_system_server_init();
#endif

	return;
}
