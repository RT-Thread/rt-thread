/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-07     NU-LL        first version
 */
#include <rtthread.h>
#include <board.h>
#include <drv_qspi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>

#ifdef BSP_USING_QSPI_FLASH

#include <fal.h>
#include <sfud.h>
#include "dfs_fs.h"
#include "drv_spi.h"
#include "spi_flash.h"
#include "spi_flash_sfud.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.qspiflash"
#include <drv_log.h>


#define FS_PARTITION_NAME               "fs_qspi"
#define FAL_USING_NOR_FLASH_2_DEV_NAME  "W25Q64_q"


static sfud_flash_t sfud_dev = NULL;

static int init(void);
static int read(long offset, uint8_t *buf, size_t size);
static int write(long offset, const uint8_t *buf, size_t size);
static int erase(long offset, size_t size);

struct fal_flash_dev nor_flash1 =
{
    .name       = FAL_USING_NOR_FLASH_2_DEV_NAME,
    .addr       = 0,
    .len        = 8 * 1024 * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 4
};

static int init(void)
{

#ifdef RT_USING_SFUD
    /* RT-Thread RTOS platform */
    sfud_dev = rt_sfud_flash_find_by_dev_name(FAL_USING_NOR_FLASH_2_DEV_NAME);
#else
    /* bare metal platform */
    extern sfud_flash nor_flash1;
    sfud_dev = &nor_flash1;
#endif

    if (NULL == sfud_dev)
    {
        return -1;
    }

    /* update the flash chip information */
    nor_flash1.blk_size = sfud_dev->chip.erase_gran;
    nor_flash1.len = sfud_dev->chip.capacity;

    return 0;
}

static int read(long offset, uint8_t *buf, size_t size)
{
    assert(sfud_dev);
    assert(sfud_dev->init_ok);
    sfud_read(sfud_dev, nor_flash1.addr + offset, size, buf);

    return size;
}

static int write(long offset, const uint8_t *buf, size_t size)
{
    assert(sfud_dev);
    assert(sfud_dev->init_ok);
    if (sfud_write(sfud_dev, nor_flash1.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, size_t size)
{
    assert(sfud_dev);
    assert(sfud_dev->init_ok);
    if (sfud_erase(sfud_dev, nor_flash1.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}









char w25qxx_read_status_register2(struct rt_qspi_device *device)
{
    /* 0x35 read status register2 */
    char instruction = 0x35, status;

    rt_qspi_send_then_recv(device, &instruction, 1, &status, 1);

    return status;
}

void w25qxx_write_enable(struct rt_qspi_device *device)
{
    /* 0x06 write enable */
    char instruction = 0x06;

    rt_qspi_send(device, &instruction, 1);
}

void w25qxx_enter_qspi_mode(struct rt_qspi_device *device)
{
    char status = 0;
    /* 0x38 enter qspi mode */
    char instruction = 0x38;
    char write_status2_buf[2] = {0};

    /* 0x31 write status register2 */
    write_status2_buf[0] = 0x31;

    status = w25qxx_read_status_register2(device);
    if (!(status & 0x02))
    {
        status |= 1 << 1;
        w25qxx_write_enable(device);
        write_status2_buf[1] = status;
        rt_qspi_send(device, &write_status2_buf, 2);
        rt_qspi_send(device, &instruction, 1);
        rt_kprintf("flash already enter qspi mode\n");
        rt_thread_mdelay(10);
    }
}

static int rt_qspi_flash_init(void)
{
    extern rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);

    rt_hw_qspi_device_attach("qspi1", "qspi10", RT_NULL, 4, w25qxx_enter_qspi_mode, RT_NULL);
    if (RT_NULL == rt_sfud_flash_probe(FAL_USING_NOR_FLASH_2_DEV_NAME, "qspi10"))
    {
        LOG_E("Failed to probe flash device "FAL_USING_NOR_FLASH_2_DEV_NAME);
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_qspi_flash_init);


#endif/* BSP_USING_QSPI_FLASH */
