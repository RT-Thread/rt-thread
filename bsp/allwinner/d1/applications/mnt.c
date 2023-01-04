#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs_romfs.h>

int mnt_init(void)
{

    rt_thread_mdelay(200);

    if (dfs_mount("boot", "/", "elm", 0, 0) != 0)
    {
        rt_kprintf("Dir /boot mount failed!\n");
    }

    rt_kprintf("file system initialization done!\n");
    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
