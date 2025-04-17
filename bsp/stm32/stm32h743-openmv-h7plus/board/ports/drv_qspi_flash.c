/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     zylx         first version
 * 2022-03-16     Miaowulue    add dfs mount
 */

#include <board.h>
#include <drv_qspi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>
#include <dfs_elm.h>
#include <dfs_fs.h>

#ifdef BSP_USING_QSPI_FLASH

#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"

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

static int rt_hw_qspi_flash_with_sfud_init(void)
{
    rt_hw_qspi_device_attach("qspi1", "qspi10", RT_NULL, 4, w25qxx_enter_qspi_mode, RT_NULL);

    /* init W25Q256 */
    if (RT_NULL == rt_sfud_flash_probe("W25Q256", "qspi10"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_qspi_flash_with_sfud_init);

static int mnt_qspi_flash_init(void)
{
    if (dfs_mount("W25Q256", "/", "elm", 0, 0) == RT_EOK)
    {
        rt_kprintf("Mount spi flash successfully!\n");
        return RT_EOK;
    }
    else
    {
        rt_kprintf("Mount spi flash fail!\n");
        return -RT_ERROR;
    }
}
INIT_APP_EXPORT(mnt_qspi_flash_init);

#endif/* BSP_USING_QSPI_FLASH */
