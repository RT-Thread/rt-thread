#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("\n mount is start \n");
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }
    else
    {
        rt_kprintf("file system initialization failed\n");
    }
    

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif

