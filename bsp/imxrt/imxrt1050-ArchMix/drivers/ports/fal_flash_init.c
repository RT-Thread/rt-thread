/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-29     flybreak     first implementation
 */

#include <rtthread.h>
#include <fal.h>
#include <easyflash.h>

#define FAL_FS_PART_NAME               "fs"
#define FAL_DOWNLOAD_PART_NAME         "download"

int rt_fal_flash_init(void)
{
    fal_init();
    easyflash_init();

    fal_blk_device_create(FAL_FS_PART_NAME);
    fal_char_device_create(FAL_DOWNLOAD_PART_NAME);

    return 0;
}
INIT_DEVICE_EXPORT(rt_fal_flash_init);
