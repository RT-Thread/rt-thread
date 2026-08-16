#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#include <dfs_romfs.h>

int mnt_init(void)
{
    if (dfs_mount(RT_NULL, "/", "rom", 0, &romfs_root) != 0)
    {
        rt_kprintf("Mount ROMFS on \"/\" failed!\n");
        return -RT_ERROR;
    }

    rt_kprintf("Mount ROMFS on \"/\" success.\n");
    return RT_EOK;
}
INIT_ENV_EXPORT(mnt_init);
#endif
