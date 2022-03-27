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

#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>

#if defined(RT_USING_FAL)
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

int mnt_init_spiflash0(void)
{
    if (dfs_mount("flash0", MOUNT_POINT_SPIFLASH0, "elm", 0, 0) != 0)
    {
        rt_kprintf("Failed to mount elm on %s.\n", MOUNT_POINT_SPIFLASH0);
        rt_kprintf("Try to execute 'mkfs -t elm flash0' first, then reboot.\n");
        goto exit_mnt_init_spiflash0;
    }
    rt_kprintf("mount flash0 with elmfat type: ok\n");

exit_mnt_init_spiflash0:

    return 0;
}
#endif
INIT_ENV_EXPORT(mnt_init_spiflash0);
#endif
