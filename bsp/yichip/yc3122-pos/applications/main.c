/*
 * Copyright (c) 2006-2021, YICHIP Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WSY          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

/* defined the LED pin: PA12 */
#define LED_PIN (51)
#define FS_PARTITION_NAME "filesystem"

#ifdef BSP_USING_INTER_FLASH
#include <dfs_elm.h>
#include <dfs_file.h>
#include <unistd.h>
#include <dfs_fs.h>
#include <fal.h>
static void elmfs_sample(void)
{
    fal_init();

    struct rt_device *flash_dev = fal_blk_device_create(FS_PARTITION_NAME);
    if (flash_dev == NULL)
    {
        LOG_E("Can't create a block device on '%s' partition.", FS_PARTITION_NAME);
    }
    else
    {
        LOG_I("Create a block device on the %s partition of flash successful...", FS_PARTITION_NAME);
    }
    if (dfs_mkfs("elm", flash_dev->parent.name) == 0)
    {
        LOG_I("dfs_mkfs ok!\n");
    }
    else
    {
        LOG_E("dfs_mkfs err!\n");
    }

    if (dfs_mount(flash_dev->parent.name, "/", "elm", 0, 0) == 0)
    {
        LOG_I("Filesystem initialized!");
    }
    else
    {
        LOG_E("Failed to initialize filesystem!");
        LOG_D("You should create a filesystem on the block device first!");
    }
    struct statfs elm_stat;
    if (statfs("/", &elm_stat) == 0)
    {
        LOG_I("elmfat filesystem block size:0x%x,total blocks:0x%x,free blocks:0x%x\n", elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);
    }

    if (mkdir("/user", 0x777) == 0)
    {
        LOG_I("make a directory: '/user'.\n");
    }

    LOG_I("open file\n");
    int fd = open("/user/test.txt", O_WRONLY | O_CREAT);
    LOG_I("open file ok\n");
    char str[] = "elmfat mount";
    if (fd >= 0)
    {
        LOG_I("write file\n");
        if (write(fd, str, sizeof(str)) == sizeof(str))
            LOG_I("write data done.\n");
        close(fd);
    }
    int size;
    char buf[20];
    fd = open("/user/test.txt", O_RDONLY);
    if (fd >= 0)
    {
        LOG_I("read file\n");
        size = read(fd, buf, sizeof(buf));
        close(fd);
        if (size == sizeof(str))
        {
            LOG_I("Read data from file test.txt(size:%d):%s\n", size, buf);
        }
    }
    else
    {
        LOG_E("open err\n");
    }

    if (statfs("/", &elm_stat) == 0)
    {
        LOG_I("elmfat filesystem block size:0x%x,total blocks:0x%x,free blocks:0x%x\n", elm_stat.f_bsize, elm_stat.f_blocks, elm_stat.f_bfree);
    }
}
#endif
int main(void)
{
#ifdef BSP_USING_INTER_FLASH
    elmfs_sample();
#endif
    int count = 1;
    /* set LED4 pin mode to output */
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
