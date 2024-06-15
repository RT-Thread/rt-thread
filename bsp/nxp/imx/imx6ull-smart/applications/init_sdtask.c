/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>

#if defined(RT_USING_DFS)

#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>

#include <ioremap.h>
#include <drv_sdio.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void filesysytem_try_mount(char *device_name, char *mount_point, char *fs_type_name, int mkfs_count)
{
    struct statfs fs_stat;
    int rc = 0;

    LOG_I("mount(\"%s\",\"%s\",\"%s\");", device_name, mount_point, fs_type_name);

    if (rt_device_find(device_name) == NULL)
    {
        LOG_I("%s not find!!!", device_name);
        return;
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
            LOG_I("[%s]try mkfs -t %s %s ", mkfs_count, fs_type_name, device_name);
            dfs_mkfs(fs_type_name, device_name);
            mkfs_count--;
            goto _remount;
        }
        LOG_I("mount failed :%d ", rc);
    }
}

void filesysytem_try_unmount(char *mount_point)
{
    struct stat filestat = {0};
    LOG_I("unmount(\"%s\");", mount_point);
    if ((dfs_file_stat(mount_point, &filestat) >= 0) && (S_ISDIR(filestat.st_mode)))
    {
        dfs_unmount(mount_point);
    }
}

static void sd_task_entry(void *parameter)
{
    volatile unsigned int *IN_STATUS;

    IN_STATUS = (volatile unsigned int *)rt_ioremap((void *)0x2190030, 4); // cd status

    int change = 0;
    while (1)
    {
        rt_thread_mdelay(200);
        change = 0;
        if (((*IN_STATUS >> 6) & 0x1) == 1)
        {
            *IN_STATUS = 0x40;
            change = 1;
        }
        if (((*IN_STATUS >> 7) & 0x1) == 1)
        {
            *IN_STATUS = (0x80);
            change = 2;
        }
        if (change > 0)
        {
            LOG_D("sdio host change: %d", change);
            mmcsd_wait_cd_changed(0); // clear
            host_change();            // send cd change to host

            int result = mmcsd_wait_cd_changed(RT_TICK_PER_SECOND);
            if (result == MMCSD_HOST_PLUGED)
            {
                LOG_D("mmcsd change pluged");
                filesysytem_try_mount("sd0", "/mnt/sd0", "elm", 0);
            }
            else if (result == MMCSD_HOST_UNPLUGED)
            {
                LOG_D("mmcsd change unpluged");
                filesysytem_try_unmount("/mnt/sd0");
            }
            else
            {
                LOG_I("mmcsd wait_cd_changed %d", result);
            }
        }
    }
}

int sd_task_init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("tsdcard", sd_task_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX - 2, 20);
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
INIT_APP_EXPORT(sd_task_init);
#endif
