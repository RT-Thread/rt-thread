/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(RT_USING_DFS)
    #include <dfs_fs.h>
    #include <dfs_posix.h>
#endif

#if defined(PKG_USING_FAL)
    #include <fal.h>
#endif

#if defined(BOARD_USING_STORAGE_SPIFLASH)
    #define MOUNT_POINT_SPIFLASH0 "/"
#endif

#if defined(BOARD_USING_STORAGE_SPIFLASH)

#if defined(RT_USB_DEVICE_MSTORAGE)
int mnt_init_spiflash0(void)
{
    rt_kprintf("Sorry, you enabled RT_USB_DEVICE_MSTORAGE option in menu, so we won't mount flash0 on /.\n");
    return 0;
}
#else

/* Recursive mkdir */
#if defined(RT_USBH_MSTORAGE) && defined(UDISK_MOUNTPOINT)
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
#endif

int mnt_init_spiflash0(void)
{
    if (dfs_mount("flash0", MOUNT_POINT_SPIFLASH0, "elm", 0, 0) != 0)
    {
        rt_kprintf("Failed to mount elm on %s.\n", MOUNT_POINT_SPIFLASH0);
        rt_kprintf("Try to execute 'mkfs -t elm flash0' first, then reboot.\n");
        goto exit_mnt_init_spiflash0;
    }
    rt_kprintf("mount flash0 with elmfat type: ok\n");

#if defined(RT_USBH_MSTORAGE) && defined(UDISK_MOUNTPOINT)
    if (mkdir_p(UDISK_MOUNTPOINT, 0) < 0)
    {
        rt_kprintf("Failed to create directory on %s for RT_USBH_MSTORAGE.\n", UDISK_MOUNTPOINT);
    }
#endif

exit_mnt_init_spiflash0:

    return 0;
}
#endif
INIT_ENV_EXPORT(mnt_init_spiflash0);
#endif

