#include <rtthread.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>

#ifdef BSP_ROOTFS_TYPE_CROMFS
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
#endif

int mnt_init(void)
{
#if defined(BSP_USING_SDIO) && defined(BSP_ROOTFS_TYPE_ELMFAT)
    int timeout = 50; // Timeout after 50 iterations (5 seconds if each iteration waits 100ms)
    while (mmcsd_wait_cd_changed(100) != MMCSD_HOST_PLUGED)
    {
        if (--timeout <= 0)
        {
            rt_kprintf("Timeout waiting for MMCSD host to be plugged!\n");
            return -1; // Return an error code to indicate failure
        }
        rt_thread_mdelay(100); // Yield to the scheduler
    }

    if (dfs_mount(BSP_SD_MNT_DEVNAME, "/", "elm", 0, 0) != 0)
    {
        rt_kprintf("%s mounted on / failed!\n", BSP_SD_MNT_DEVNAME);
    }
    else {
        rt_kprintf("%s mounted on / success!\n", BSP_SD_MNT_DEVNAME);
    }
#endif

#ifdef BSP_ROOTFS_TYPE_CROMFS
    rt_err_t ret;

    ret = mnt_cromfs();
    if (ret != RT_EOK)
    {
        rt_kprintf("CromFS mount failed!\n");
        return ret;
    }
    else
    {
        rt_kprintf("CromFS mount success!\n");
    }
#endif

    mkdir("/dev/shm", 0x777);

    if (dfs_mount(RT_NULL, "/dev/shm", "tmp", 0, 0) != 0)
    {
        rt_kprintf("tmpfs mounted on /dev/shm failed!\n");
    }
    else {
        rt_kprintf("tmpfs mounted on /dev/shm success!\n");
    }

    rt_kprintf("file system initialization done!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#endif /* RT_USING_DFS */
