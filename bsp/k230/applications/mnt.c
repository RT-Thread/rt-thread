#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

rt_weak uint8_t *cromfs_get_partition_data(uint32_t *len)
{
    return RT_NULL;
}

static int mnt_cromfs(void)
{
    uint32_t length = 0;
    uint8_t *data = cromfs_get_partition_data(&length);
    int ret = -1;

    if (data && length)
    {
        ret = dfs_mount(NULL, "/", "crom", 0, data);
    }

    return ret;
}

int mnt_init(void)
{
    rt_err_t ret;

    ret = mnt_cromfs();
    if (ret != RT_EOK)
    {
        rt_kprintf("CromFS mount failed!\n");
        return ret;
    }

    mkdir("/dev/shm", 0x777);

    if (dfs_mount(RT_NULL, "/dev/shm", "tmp", 0, 0) != 0)
    {
        rt_kprintf("Dir /dev/shm mount failed!\n");
    }

#ifdef BSP_SD_SDIO_DEV
    while (mmcsd_wait_cd_changed(100) != MMCSD_HOST_PLUGED)
        ;

    if (dfs_mount(BSP_SD_MNT_DEVNAME, "/mnt", "elm", 0, 0) != 0)
    {
        rt_kprintf("Dir /mnt mount failed!\n");
    }
#endif

    rt_kprintf("file system initialization done!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
#endif
