/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-3-12       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#define LOG_TAG         "mnt"
#define DBG_ENABLE
#define DBG_SECTION_NAME "mnt"
#define DBG_LEVEL DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

#if defined(RT_USING_FAL)
    #include <fal.h>
#endif

#ifdef RT_USING_DFS_MNTTABLE

/*
const char   *device_name;
const char   *path;
const char   *filesystemtype;
unsigned long rwflag;
const void   *data;
*/

const struct dfs_mount_tbl mount_table[] =
{
    { "sd0", "/mnt/sd0", "elm", 0, RT_NULL },
    { "sd0p0", "/mnt/sd0p0", "elm", 0, RT_NULL },
    { "sd0p1", "/mnt/sd0p1", "elm", 0, RT_NULL },
    { "sd1", "/mnt/sd1", "elm", 0, RT_NULL },
    { "sd1p0", "/mnt/sd1p0", "elm", 0, RT_NULL },
    { "sd1p1", "/mnt/sd1p1", "elm", 0, RT_NULL },
    {0},
};
#endif

#if defined(BOARD_USING_STORAGE_SPIFLASH)
    #define PARTITION_NAME_FILESYSTEM "filesystem"
    #define MOUNT_POINT_SPIFLASH0 "/"

/* Recursive mkdir */
static int mkdir_p(const char *dir, const mode_t mode)
{
    int ret = -1;
    char *tmp = NULL;
    char *p = NULL;
    struct stat sb;
    rt_size_t len;

    if (!dir)
        goto exit_mkdir_p;

    /* Copy path */
    /* Get the string length */
    len = strlen(dir);
    tmp = rt_strdup(dir);

    /* Remove trailing slash */
    if (tmp[len - 1] == '/')
    {
        tmp[len - 1] = '\0';
        len--;
    }

    /* check if path exists and is a directory */
    if (stat(tmp, &sb) == 0)
    {
        if (S_ISDIR(sb.st_mode))
        {
            ret = 0;
            goto exit_mkdir_p;
        }
    }

    /* Recursive mkdir */
    for (p = tmp + 1; p - tmp <= len; p++)
    {
        if ((*p == '/') || (p - tmp == len))
        {
            *p = 0;

            /* Test path */
            if (stat(tmp, &sb) != 0)
            {
                /* Path does not exist - create directory */
                if (mkdir(tmp, mode) < 0)
                {
                    goto exit_mkdir_p;
                }
            }
            else if (!S_ISDIR(sb.st_mode))
            {
                /* Not a directory */
                goto exit_mkdir_p;
            }
            if (p - tmp != len)
                *p = '/';
        }
    }

    ret = 0;

exit_mkdir_p:

    if (tmp)
        rt_free(tmp);

    return ret;
}

int mnt_init_spiflash0(void)
{
#if defined(RT_USING_FAL)
    extern int fal_init_check(void);
    if (!fal_init_check())
        fal_init();
#endif
    struct rt_device *psNorFlash = fal_blk_device_create(PARTITION_NAME_FILESYSTEM);
    if (!psNorFlash)
    {
        rt_kprintf("Failed to create block device for %s.\n", PARTITION_NAME_FILESYSTEM);
        goto exit_mnt_init_spiflash0;
    }
    else if (dfs_mount(psNorFlash->parent.name, MOUNT_POINT_SPIFLASH0, "elm", 0, 0) != 0)
    {
        rt_kprintf("Failed to mount elm on %s.\n", MOUNT_POINT_SPIFLASH0);
        rt_kprintf("Try to execute 'mkfs -t elm %s' first, then reboot.\n", PARTITION_NAME_FILESYSTEM);
        goto exit_mnt_init_spiflash0;
    }
    rt_kprintf("mount %s with elmfat type: ok\n", PARTITION_NAME_FILESYSTEM);
    mkdir_p("/mnt/sd0", 0x777);
    mkdir_p("/mnt/sd0p0", 0x777);
    mkdir_p("/mnt/sd0p1", 0x777);
    mkdir_p("/mnt/sd1", 0x777);
    mkdir_p("/mnt/sd1p0", 0x777);
    mkdir_p("/mnt/sd1p1", 0x777);
    mkdir_p(UDISK_MOUNTPOINT, 0x777);

exit_mnt_init_spiflash0:

    return 0;
}
INIT_APP_EXPORT(mnt_init_spiflash0);
#endif

