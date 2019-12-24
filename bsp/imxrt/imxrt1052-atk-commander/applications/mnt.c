#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    rt_thread_delay(RT_TICK_PER_SECOND);

    if (dfs_mount("W25Q256", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("W25Q256 mount successful!\n");
    }
    else
    {
        rt_kprintf("W25Q256 mount failed!\n");
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif

