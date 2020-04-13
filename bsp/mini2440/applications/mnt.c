#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include "dfs_ramfs.h"

int mnt_init(void)
{
	if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
	{
		rt_kprintf("File System initialized!\n");
	}
	else
	{
		rt_kprintf("File System initialzation failed!\n");
	}
   
	return RT_EOK;
}
INIT_ENV_EXPORT(mnt_init);
#endif

