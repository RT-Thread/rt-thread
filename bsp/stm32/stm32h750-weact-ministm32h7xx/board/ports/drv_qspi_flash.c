/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
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


#define QSPI_CS_PIN		GET_PIN(B, 6)

#define FS_PARTITION_NAME  "fs_qspi"
#define FAL_USING_NOR_FLASH_2_DEV_NAME "W25Q64_q"


static int init(void);
static int read(long offset, uint8_t *buf, size_t size);
static int write(long offset, const uint8_t *buf, size_t size);
static int erase(long offset, size_t size);





static char w25qxx_read_status_register2(struct rt_qspi_device *device)
{
    /* 0x35 read status register2 */
    char instruction = 0x35, status;

    rt_qspi_send_then_recv(device, &instruction, 1, &status, 1);

    return status;
}

static void w25qxx_write_enable(struct rt_qspi_device *device)
{
    /* 0x06 write enable */
    char instruction = 0x06;

    rt_qspi_send(device, &instruction, 1);
}

static void w25qxx_enter_qspi_mode(struct rt_qspi_device *device)
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
        // rt_qspi_send(device, &write_status2_buf, 2);
        rt_qspi_send(device, write_status2_buf, 2);
        rt_qspi_send(device, &instruction, 1);
        rt_kprintf("flash already enter qspi mode\n");
        rt_thread_mdelay(10);
    }
}

/* read the JEDEC SFDP command must run at 50 MHz or less */
#define RT_SFUD_DEFAULT_SPI_CFG                  \
{                                                \
    .mode = RT_SPI_MODE_2 | RT_SPI_MSB,          \
    .data_width = 8,                             \
    .max_hz = 20000000,                \
}

#ifdef SFUD_USING_QSPI
#define RT_SFUD_DEFAULT_QSPI_CFG                 \
{                                                \
    RT_SFUD_DEFAULT_SPI_CFG,                     \
    .medium_size = 0x800000,                     \
    .ddr_mode = 0,                               \
    .qspi_dl_width = 4,                          \
}
#endif /* SFUD_USING_QSPI */

static int rt_hw_qspi_flash_with_sfud_init(void)
{
    stm32_qspi_bus_attach_device("qspi1", "qspi10", RT_NULL, 4, RT_NULL, RT_NULL);
    // stm32_qspi_bus_attach_device("qspi1", "qspi10", RT_NULL, 4, w25qxx_enter_qspi_mode, RT_NULL);
    // stm32_qspi_bus_attach_device("qspi1", "qspi10", QSPI_CS_PIN, 4, w25qxx_enter_qspi_mode, RT_NULL);

    /* init W25Q16    , And register as a block device */

    struct rt_spi_configuration cfg = RT_SFUD_DEFAULT_SPI_CFG;
    struct rt_qspi_configuration qspi_cfg = RT_SFUD_DEFAULT_QSPI_CFG;
    // // return rt_sfud_flash_probe_ex(FAL_USING_NOR_FLASH_2_DEV_NAME, "qspi10", &cfg, &qspi_cfg);
    if(RT_NULL == rt_sfud_flash_probe_ex(FAL_USING_NOR_FLASH_2_DEV_NAME, "qspi10", &cfg, &qspi_cfg))


    // if (RT_NULL == rt_sfud_flash_probe(FAL_USING_NOR_FLASH_2_DEV_NAME, "qspi10"))
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_qspi_flash_with_sfud_init);








static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev nor_flash1 =
{
    .name       = FAL_USING_NOR_FLASH_2_DEV_NAME,
    .addr       = 0,
    .len        = 8 * 1024 * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 1
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






static int mnt_qspi(void)
{
    struct rt_device *mtd_dev = RT_NULL;

    mtd_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);
    if (!mtd_dev)
    {
        LOG_E("Can't create a mtd device on '%s' partition.", FS_PARTITION_NAME);
    }
    else
    {
        /* mount littlefs */
        if (dfs_mount(FS_PARTITION_NAME, "/qspi", "lfs", 0, 0) == 0)
        {
            LOG_I("Filesystem initialized!");
        }
        else
        {
            dfs_mkfs("lfs", FS_PARTITION_NAME);
            /* mount littlefs */
            if (dfs_mount(FS_PARTITION_NAME, "/qspi", "lfs", 0, 0) == 0)
            {
                LOG_I("Filesystem initialized!");
            }
            else
            {
                LOG_E("Failed to initialize filesystem!");
            }
        }
    }
    return RT_EOK;
}
INIT_APP_EXPORT(mnt_qspi);



#endif/* BSP_USING_QSPI_FLASH */
