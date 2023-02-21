/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-6-26       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(RT_USING_DFS)

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

#if defined(PKG_USING_RAMDISK)
    #define RAMDISK_NAME         "ramdisk0"
    #define RAMDISK_UDC          "ramdisk1"
    #define MOUNT_POINT_RAMDISK0 "/"
#endif

#if defined(BOARD_USING_STORAGE_SPIFLASH)
    #define PARTITION_NAME_FILESYSTEM "filesystem"
    #define MOUNT_POINT_SPIFLASH0 "/mnt/"PARTITION_NAME_FILESYSTEM
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
#if defined(PKG_USING_RAMDISK)
    { RAMDISK_UDC, "/mnt/ram_usbd", "elm", 0, RT_NULL },
#endif
#if defined(PKG_USING_DFS_YAFFS)
    { "nand1", "/mnt/nand1", "yaffs", 0, RT_NULL },
    { "rawnd1", "/mnt/nfi", "yaffs", 0, RT_NULL },
#elif defined(RT_USING_DFS_UFFS)
    { "nand1", "/mnt/nand1", "uffs", 0, RT_NULL },
#endif
    { "sd0", "/mnt/sd0", "elm", 0, RT_NULL },
    { "sd0p0", "/mnt/sd0p0", "elm", 0, RT_NULL },
    { "sd0p1", "/mnt/sd0p1", "elm", 0, RT_NULL },
    { "sd1", "/mnt/sd1", "elm", 0, RT_NULL },
    { "sd1p0", "/mnt/sd1p0", "elm", 0, RT_NULL },
    { "sd1p1", "/mnt/sd1p1", "elm", 0, RT_NULL },
    {0},
};
#endif


#if defined(PKG_USING_RAMDISK)

extern rt_err_t ramdisk_init(const char *dev_name, rt_uint8_t *disk_addr, rt_size_t block_size, rt_size_t num_block);
int ramdisk_device_init(void)
{
    rt_err_t result = RT_EOK;

    /* Create a 16MB RAMDISK */
    result = ramdisk_init(RAMDISK_NAME, NULL, 512, 16 * 4096);
    RT_ASSERT(result == RT_EOK);

    /* Create a 16MB RAMDISK */
    result = ramdisk_init(RAMDISK_UDC, NULL, 512, 16 * 4096);
    RT_ASSERT(result == RT_EOK);

    return 0;
}
INIT_DEVICE_EXPORT(ramdisk_device_init);

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

#if defined(PKG_USING_DFS_YAFFS) && defined(RT_USING_DFS_MNTTABLE)
#include "yaffs_guts.h"
int yaffs_dev_init(void)
{
    int i;

    for (i = 0; i < sizeof(mount_table) / sizeof(struct dfs_mount_tbl); i++)
    {
        if (mount_table[i].filesystemtype && !rt_strcmp(mount_table[i].filesystemtype, "yaffs"))
        {
            struct rt_mtd_nand_device *psMtdNandDev = RT_MTD_NAND_DEVICE(rt_device_find(mount_table[i].device_name));
            if (psMtdNandDev)
            {
                LOG_I("yaffs start [%s].", mount_table[i].device_name);

                yaffs_start_up(psMtdNandDev, (const char *)mount_table[i].path);

                LOG_I("dfs mount [%s].", mount_table[i].device_name);
                if (dfs_mount(mount_table[i].device_name,
                              mount_table[i].path,
                              mount_table[i].filesystemtype,
                              mount_table[i].rwflag,
                              mount_table[i].data) != 0)
                {
                    LOG_E("mount fs[%s] on %s failed.", mount_table[i].filesystemtype, mount_table[i].path);
                }
            }
        }
    }

    return 0;
}
INIT_APP_EXPORT(yaffs_dev_init);
#endif

/* Initialize the filesystem */
int filesystem_init(void)
{
    rt_err_t result = RT_EOK;

#if defined(RT_USING_FAL)
    extern int fal_init_check(void);
    if (!fal_init_check())
        fal_init();
#endif

    // ramdisk as root
    if (!rt_device_find(RAMDISK_NAME))
    {
        LOG_E("cannot find %s device", RAMDISK_NAME);
        result = -RT_ERROR;
        goto exit_filesystem_init;
    }
    else
    {
        /* Format these ramdisk */
        result = (rt_err_t)dfs_mkfs("elm", RAMDISK_NAME);
        RT_ASSERT(result == RT_EOK);

        /* mount ramdisk0 as root directory */
        if (dfs_mount(RAMDISK_NAME, "/", "elm", 0, RT_NULL) == 0)
        {
            LOG_I("ramdisk mounted on \"/\".");

            /* now you can create dir dynamically. */
            mkdir_p("/mnt", 0x777);
            mkdir_p("/cache", 0x777);
            mkdir_p("/download", 0x777);
            mkdir_p("/mnt/ram_usbd", 0x777);
            mkdir_p("/mnt/nand1", 0x777);
            mkdir_p("/mnt/nfi", 0x777);
            mkdir_p("/mnt/sd0", 0x777);
            mkdir_p("/mnt/sd0p0", 0x777);
            mkdir_p("/mnt/sd0p1", 0x777);
            mkdir_p("/mnt/sd1", 0x777);
            mkdir_p("/mnt/sd1p0", 0x777);
            mkdir_p("/mnt/sd1p1", 0x777);
#if defined(RT_USBH_MSTORAGE) && defined(UDISK_MOUNTPOINT)
            mkdir_p(UDISK_MOUNTPOINT, 0x777);
#endif
        }
        else
        {
            LOG_E("root folder creation failed!\n");
            goto exit_filesystem_init;
        }
    }

    if (!rt_device_find(RAMDISK_UDC))
    {
        LOG_E("cannot find %s device", RAMDISK_UDC);
        goto exit_filesystem_init;
    }
    else
    {
        /* Format these ramdisk */
        result = (rt_err_t)dfs_mkfs("elm", RAMDISK_UDC);
        RT_ASSERT(result == RT_EOK);
    }

#if defined(BOARD_USING_STORAGE_SPIFLASH)
    {
        struct rt_device *psNorFlash = fal_blk_device_create(PARTITION_NAME_FILESYSTEM);
        if (!psNorFlash)
        {
            rt_kprintf("Failed to create block device for %s.\n", PARTITION_NAME_FILESYSTEM);
        }
    }
#endif

exit_filesystem_init:

    return -result;
}
INIT_ENV_EXPORT(filesystem_init);
#endif
#endif
