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

#ifdef RT_USING_DFS_PTYFS
static int mnt_ptyfs(void)
{
    mkdir("/dev/pts", 0755);

    if (dfs_mount(RT_NULL, "/dev/pts", "ptyfs", 0, RT_NULL) != RT_EOK)
    {
        rt_kprintf("ptyfs mounted on /dev/pts failed!\n");
        return -RT_ERROR;
    }

    rt_kprintf("ptyfs mounted on /dev/pts success!\n");
    return RT_EOK;
}
#endif

int mnt_init(void)
{
#if defined(BSP_USING_SDIO) && \
    (defined(BSP_ROOTFS_TYPE_ELMFAT) || defined(BSP_ROOTFS_TYPE_EXT4))
    int timeout = 50;
    const char *filesystem;

#ifdef BSP_ROOTFS_TYPE_EXT4
    filesystem = "ext";
#else
    filesystem = "elm";
#endif

    while (mmcsd_wait_cd_changed(100) != MMCSD_HOST_PLUGED)
    {
        if (--timeout <= 0)
        {
            rt_kprintf("Timeout waiting for MMCSD host to be plugged!\n");
            return -1;
        }
        rt_thread_mdelay(100);
    }

    if (dfs_mount(BSP_SD_MNT_DEVNAME, "/", filesystem, 0, 0) != 0)
    {
        rt_kprintf("%s mounted on / failed!\n", BSP_SD_MNT_DEVNAME);
    }
    else
    {
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

#ifdef RT_USING_DFS_PTYFS
    (void)mnt_ptyfs();
#endif

    rt_kprintf("file system initialization done!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

#if defined(RT_USING_DFS_PROCFS) && !defined(RT_USING_DM)
static int mnt_procfs(void)
{
    mkdir("/proc", 0755);

    if (dfs_mount(RT_NULL, "/proc", "procfs", 0, RT_NULL) != RT_EOK)
    {
        rt_kprintf("procfs mounted on /proc failed!\n");
        return -RT_ERROR;
    }

    rt_kprintf("procfs mounted on /proc success!\n");
    return RT_EOK;
}
INIT_FS_EXPORT(mnt_procfs);
#endif

#endif /* RT_USING_DFS */
