/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-27     huanghe      first version
 * 2023-07-14   liqiaozhong    add SD file sys mount func
 *
 */
#include <rtthread.h>
#if defined(RT_USING_DFS)
#include <rtdbg.h>

#include <dfs_fs.h>
#include <dfs_file.h>

static int ram_disk_mount(const char *mount_point)
{
#ifdef RT_USING_DFS_RAMFS
    extern struct dfs_ramfs *dfs_ramfs_create(rt_uint8_t *pool, rt_size_t size);

    rt_uint8_t *pool = RT_NULL;
    rt_size_t size = 8 * 1024 * 1024;

    pool = rt_malloc(size);
    if (pool == RT_NULL)
        LOG_E("Malloc fail!");

    if (dfs_mount(RT_NULL, mount_point, "ram", 0, (const void *)dfs_ramfs_create(pool, size)) == 0)
        LOG_I("RAM file system initializated!");
    else
        LOG_E("RAM file system initializate failed!");
#endif

    return RT_EOK;
}

#ifdef BSP_USING_SDCARD_FATFS
extern void fsdif_change(void);
static int sd_disk_try_mount(char *device_name, char *mount_point, char *fs_type_name, int mkfs_count)
{
    struct statfs fs_stat;
    int rc = 0;

    LOG_I("mount(\"%s\",\"%s\",\"%s\");", device_name, mount_point, fs_type_name);

    if (rt_device_find(device_name) == NULL)
    {
        LOG_I("%s not find!!!", device_name);
        return -RT_EIO;
    }

    mkdir(mount_point, 0);
_remount:
    rc = dfs_mount(device_name, mount_point, fs_type_name, 0, 0);
    if (rc == 0)
    {
        LOG_I("mounted %s on %s", device_name, mount_point);
        if (dfs_statfs(mount_point, &fs_stat) >= 0)
        {
            LOG_I("%s size:%d, total: %d, free: %d", mount_point,
                  fs_stat.f_bsize, fs_stat.f_blocks, fs_stat.f_bfree);
        }
    }
    else
    {
        if (mkfs_count > 0)
        {
            /* LOG_I("[%s]try mkfs -t %s %s ", mkfs_count, fs_type_name, device_name);
            dfs_mkfs(fs_type_name, device_name); */
            mkfs_count--; 
            LOG_E("%s is not in %s, please format first !!!", device_name, fs_type_name);
            goto _remount;
        }

        LOG_I("mount failed :%d ", rc);
        return -RT_EIO;
    }

    return RT_EOK;
}

static void sd_filesytem_task_entry(void *parameter)
{
    int result;
    LOG_D("sdio host change: %d", change);
    mmcsd_wait_cd_changed(0); /* clear */
    fsdif_change();        /* send cd change to host */

    /* block until plug/unplug event happens */
    result = mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
    if (result == MMCSD_HOST_PLUGED)
    {
        rt_kprintf("mmcsd change pluged \n");
        /* mount sdcard partition as / */
        if (RT_EOK == sd_disk_try_mount(BSP_USING_SDCARD_PARTITION, "/", "elm", 0))
        {
            ram_disk_mount("/ram"); /* mount ramdisk if configured */
        }
    }
}

int filesystem_mount(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("sd_filesytem", sd_filesytem_task_entry, 
                           RT_NULL,
                           4096, 
                           RT_THREAD_PRIORITY_MAX - 2, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd mount task error!");
    }

    return RT_EOK;
}
INIT_APP_EXPORT(filesystem_mount);

#else
static int filesystem_mount(void)
{
    return ram_disk_mount("/"); /* mount ramdisk as / */
}
INIT_APP_EXPORT(filesystem_mount);
#endif // #ifdef BSP_USING_SDCARD_FATFS
#endif // #if defined(RT_USING_DFS)