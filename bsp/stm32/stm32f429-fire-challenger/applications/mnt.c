#include <rtthread.h>

#if ((defined RT_USING_DFS_ELMFAT) && (defined BSP_USING_SPI_FLASH))
#include <dfs_fs.h>

int mnt_init(void)
{
    if (dfs_mount("W25Q128", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("W25Q128 mount successful!\n");
    }
    else
    {
        rt_kprintf("W25Q128 mount failed!\n");
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
