/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-18     Shell        add cromfs support
 */

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <dfs_cromfs.h>
#include <dfs_posix.h>
#include <dfs_fs.h>
#include <ioremap.h>
#include <mmu.h>
#include <rtthread.h>

#include <unistd.h>

struct _mount_table
{
    char *dev_name;
    char *mount_point;
    char *fs_name;
    long rwflag;
    void *data;
};

struct _mount_table _mount_table[] = {
    [0] = {NULL, "/", "crom", 0, 0},

};

static int _wait_device_ready(const char* devname)
{
    int k;

    for(k = 0; k < 10; k++)
    {
        if (rt_device_find(devname) != RT_NULL)
        {
            return 1;
        }
        rt_thread_mdelay(50);
    }

    return 0;
}

int mnt_init(void)
{
    int i;
    uint32_t crom_data_len = 0;
    uint32_t length;

    _mount_table[0].data = cromfs_get_partition_data(&length);
    crom_data_len = length;

    if (_mount_table[0].data && (crom_data_len > 0))
    {
        for (i = 0; i < sizeof(_mount_table) / sizeof(_mount_table[0]); i++)
        {
            if (_mount_table[i].dev_name && !_wait_device_ready(_mount_table[i].dev_name))
            {
                LOG_E("device %s find timeout", _mount_table[i].dev_name);
                continue;
            }

            if (dfs_mount(_mount_table[i].dev_name, _mount_table[i].mount_point,
                        _mount_table[i].fs_name, _mount_table[i].rwflag, _mount_table[i].data) != 0)
            {
                LOG_E("Dir %s %s mount failed!", _mount_table[i].mount_point,
                    _mount_table[i].dev_name ? _mount_table[i].dev_name : _mount_table[i].fs_name);
            }
            else
            {
                LOG_I("Dir %s %s mount ok!", _mount_table[i].mount_point,
                    _mount_table[i].dev_name ? _mount_table[i].dev_name : _mount_table[i].fs_name);
            }
        }
    }
    else
    {
        LOG_E("No mount data found!");
    }

    mkdir("/dev/shm", 0777);

    if (dfs_mount(NULL, "/dev/shm", "tmp", 0, 0) != 0)
    {
        LOG_E("Dir %s %s mount failed!", "/dev/shm", "tmp");
    }
    else
    {
        LOG_I("Dir %s %s mount ok!", "/dev/shm", "tmp");
    }

    LOG_I("file system initialization done!\n");

    return 0;
}
INIT_ENV_EXPORT(mnt_init);
