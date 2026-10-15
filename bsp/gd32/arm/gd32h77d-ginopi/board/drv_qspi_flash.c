/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-31     RT-Thread    add GD25X512ME OSPI flash support
 * 2026-08-31     CYFS         adapt GD25Q64E QSPI flash
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <fal.h>

#include "drv_ospi.h"

#ifdef BSP_USING_FLASH_FATFS

#define DBG_TAG                         "drv.qspi_flash"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#define GD25Q64E_DEVICE_NAME            "qspi_flash0"
#define GD25Q64E_BUS_NAME               "ospi0"
#define GD25Q64E_SECTOR_SIZE            (4U * 1024U)
#define GD25Q64E_PAGE_SIZE              256U

#define GD25Q64E_EXPECTED_ID            0xC84017U

#define GD25Q64E_CMD_WRITE_ENABLE       0x06U
#define GD25Q64E_CMD_READ_STATUS1       0x05U
#define GD25Q64E_CMD_READ_STATUS2       0x35U
#define GD25Q64E_CMD_WRITE_STATUS2      0x31U
#define GD25Q64E_CMD_READ_ID            0x9FU
#define GD25Q64E_CMD_RESET_ENABLE       0x66U
#define GD25Q64E_CMD_RESET_MEMORY       0x99U
#define GD25Q64E_CMD_QUAD_READ          0x6BU
#define GD25Q64E_CMD_QUAD_PAGE_PROGRAM  0x32U
#define GD25Q64E_CMD_ERASE_4K           0x20U

#define GD25Q64E_STATUS_WIP             0x01U
#define GD25Q64E_STATUS_WEL             0x02U
#define GD25Q64E_STATUS2_QE             0x02U

#define GD25Q64E_READ_DUMMY_CYCLES      8U
#define GD25Q64E_PROGRAM_TIMEOUT_MS     1000U
#define GD25Q64E_ERASE_TIMEOUT_MS       2000U

static struct rt_qspi_device *gd25q64e_device;
static struct rt_mutex gd25q64e_lock;
static rt_bool_t gd25q64e_lock_initialized;
static rt_bool_t gd25q64e_ready;

static rt_err_t gd25q64e_transfer(rt_uint8_t instruction,
                                  rt_uint8_t instruction_lines,
                                  rt_uint32_t address,
                                  rt_uint8_t address_size,
                                  rt_uint8_t address_lines,
                                  rt_uint32_t dummy_cycles,
                                  const rt_uint8_t *send_buf,
                                  rt_uint8_t *recv_buf,
                                  rt_size_t size,
                                  rt_uint8_t data_lines)
{
    struct rt_qspi_message message = {0};
    rt_ssize_t result;

    message.instruction.content = instruction;
    message.instruction.qspi_lines = instruction_lines;
    message.address.content = address;
    message.address.size = address_size;
    message.address.qspi_lines = address_lines;
    message.dummy_cycles = dummy_cycles;
    message.qspi_data_lines = data_lines;
    message.parent.send_buf = send_buf;
    message.parent.recv_buf = recv_buf;
    message.parent.length = size;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;
    message.parent.next = RT_NULL;

    result = rt_qspi_transfer_message(gd25q64e_device, &message);
    if (size == 0U)
    {
        return result > 0 ? RT_EOK : -RT_EIO;
    }

    return result == (rt_ssize_t)size ? RT_EOK : -RT_EIO;
}

static rt_err_t gd25q64e_command(rt_uint8_t instruction)
{
    return gd25q64e_transfer(instruction, 1, 0, 0, 0, 0,
                             RT_NULL, RT_NULL, 0, 0);
}

static rt_err_t gd25q64e_read_status1(rt_uint8_t *status)
{
    return gd25q64e_transfer(GD25Q64E_CMD_READ_STATUS1, 1,
                             0, 0, 0, 0,
                             RT_NULL, status, 1, 1);
}

static rt_err_t gd25q64e_read_status2(rt_uint8_t *status)
{
    return gd25q64e_transfer(GD25Q64E_CMD_READ_STATUS2, 1,
                             0, 0, 0, 0,
                             RT_NULL, status, 1, 1);
}

static rt_err_t gd25q64e_wait_status(rt_uint8_t mask,
                                     rt_uint8_t expected,
                                     rt_uint32_t timeout_ms,
                                     rt_bool_t delay_while_busy)
{
    rt_uint32_t start_ms;
    rt_uint8_t status;
    rt_err_t result;

    start_ms = (rt_uint32_t)rt_tick_get_millisecond();
    do
    {
        result = gd25q64e_read_status1(&status);
        if (result != RT_EOK)
        {
            return result;
        }
        if ((status & mask) == expected)
        {
            return RT_EOK;
        }

        if (delay_while_busy)
        {
            rt_thread_mdelay(1);
        }
    }
    while ((rt_uint32_t)((rt_uint32_t)rt_tick_get_millisecond() - start_ms) < timeout_ms);

    return -RT_ETIMEOUT;
}

static rt_err_t gd25q64e_write_enable(void)
{
    rt_err_t result;

    result = gd25q64e_command(GD25Q64E_CMD_WRITE_ENABLE);
    if (result != RT_EOK)
    {
        return result;
    }

    return gd25q64e_wait_status(GD25Q64E_STATUS_WEL,
                                 GD25Q64E_STATUS_WEL,
                                 GD25Q64E_PROGRAM_TIMEOUT_MS,
                                 RT_FALSE);
}

static rt_err_t gd25q64e_set_qe(void)
{
    rt_uint8_t status2 = 0;
    rt_err_t result;

    result = gd25q64e_read_status2(&status2);
    if (result != RT_EOK || (status2 & GD25Q64E_STATUS2_QE) != 0U)
    {
        return result;
    }

    status2 |= GD25Q64E_STATUS2_QE;
    result = gd25q64e_write_enable();
    if (result == RT_EOK)
    {
        result = gd25q64e_transfer(GD25Q64E_CMD_WRITE_STATUS2, 1,
                                    0, 0, 0, 0,
                                    &status2, RT_NULL, 1, 1);
    }
    if (result == RT_EOK)
    {
        result = gd25q64e_wait_status(GD25Q64E_STATUS_WIP, 0,
                                      GD25Q64E_PROGRAM_TIMEOUT_MS,
                                      RT_TRUE);
    }
    if (result == RT_EOK)
    {
        result = gd25q64e_read_status2(&status2);
    }

    return result == RT_EOK && (status2 & GD25Q64E_STATUS2_QE) != 0U ?
           RT_EOK : -RT_EIO;
}

static rt_err_t gd25q64e_read_id(rt_uint32_t *flash_id)
{
    rt_uint8_t id[3] = {0};
    rt_err_t result;

    result = gd25q64e_transfer(GD25Q64E_CMD_READ_ID, 1,
                               0, 0, 0, 0,
                               RT_NULL, id, sizeof(id), 1);
    if (result == RT_EOK)
    {
        *flash_id = ((rt_uint32_t)id[0] << 16) |
                    ((rt_uint32_t)id[1] << 8) |
                    (rt_uint32_t)id[2];
    }

    return result;
}

static rt_err_t gd25q64e_reset(void)
{
    rt_err_t result;

    result = gd25q64e_command(GD25Q64E_CMD_RESET_ENABLE);
    if (result == RT_EOK)
    {
        result = gd25q64e_command(GD25Q64E_CMD_RESET_MEMORY);
    }

    rt_thread_mdelay(1);
    return result;
}

static int gd25q64e_init(void)
{
    struct rt_qspi_configuration configuration = {0};
    rt_device_t device;
    rt_uint32_t flash_id = 0;
    rt_err_t result;

    if (gd25q64e_ready)
    {
        return RT_EOK;
    }

    if (!gd25q64e_lock_initialized)
    {
        result = rt_mutex_init(&gd25q64e_lock, "qspi_fl", RT_IPC_FLAG_PRIO);
        if (result != RT_EOK)
        {
            return result;
        }
        gd25q64e_lock_initialized = RT_TRUE;
    }

    device = rt_device_find(GD25Q64E_DEVICE_NAME);
    if (device == RT_NULL)
    {
        result = rt_hw_ospi_device_attach(GD25Q64E_BUS_NAME,
                                          GD25Q64E_DEVICE_NAME,
                                          4, RT_NULL, RT_NULL);
        if (result != RT_EOK)
        {
            LOG_E("attach %s to %s failed: %d",
                  GD25Q64E_DEVICE_NAME, GD25Q64E_BUS_NAME, result);
            return result;
        }
        device = rt_device_find(GD25Q64E_DEVICE_NAME);
    }
    if (device == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    gd25q64e_device = (struct rt_qspi_device *)device;
    configuration.parent.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    configuration.parent.data_width = 8;
    configuration.parent.max_hz = BSP_OSPI_FLASH_MAX_HZ;
    configuration.medium_size = GD25Q64E_FLASH_SIZE;
    configuration.ddr_mode = 0;
    configuration.qspi_dl_width = 4;
    result = rt_qspi_configure(gd25q64e_device, &configuration);
    if (result != RT_EOK)
    {
        LOG_E("configure %s failed: %d", GD25Q64E_DEVICE_NAME, result);
        return result;
    }

    result = rt_mutex_take(&gd25q64e_lock, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return result;
    }

    result = gd25q64e_reset();
    if (result == RT_EOK)
    {
        result = gd25q64e_read_id(&flash_id);
    }
    if (result == RT_EOK && flash_id != GD25Q64E_EXPECTED_ID)
    {
        LOG_E("unexpected flash ID: 0x%06x", flash_id);
        result = -RT_EIO;
    }
    if (result == RT_EOK)
    {
        result = gd25q64e_set_qe();
    }
    if (result == RT_EOK)
    {
        gd25q64e_ready = RT_TRUE;
        LOG_I("GD25Q64E ready, ID 0x%06x, clock %u Hz",
              flash_id, (unsigned int)BSP_OSPI_FLASH_MAX_HZ);
    }

    rt_mutex_release(&gd25q64e_lock);
    return result;
}
INIT_DEVICE_EXPORT(gd25q64e_init);

static int gd25q64e_read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_err_t result;

    if (!gd25q64e_ready)
    {
        return -RT_EIO;
    }
    if (offset < 0 || buf == RT_NULL || (rt_size_t)offset > GD25Q64E_FLASH_SIZE ||
        size > GD25Q64E_FLASH_SIZE - (rt_size_t)offset)
    {
        return -RT_EINVAL;
    }
    if (size == 0U)
    {
        return 0;
    }

    result = rt_mutex_take(&gd25q64e_lock, RT_WAITING_FOREVER);
    if (result == RT_EOK)
    {
        result = gd25q64e_transfer(GD25Q64E_CMD_QUAD_READ, 1,
                                   (rt_uint32_t)offset, 24, 1,
                                   GD25Q64E_READ_DUMMY_CYCLES,
                                   RT_NULL, buf, size, 4);
        rt_mutex_release(&gd25q64e_lock);
    }

    return result == RT_EOK ? (int)size : result;
}

static int gd25q64e_write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t remaining;
    rt_size_t page_remaining;
    rt_size_t write_size;
    rt_uint32_t address;
    rt_err_t result;

    if (!gd25q64e_ready)
    {
        return -RT_EIO;
    }
    if (offset < 0 || buf == RT_NULL || (rt_size_t)offset > GD25Q64E_FLASH_SIZE ||
        size > GD25Q64E_FLASH_SIZE - (rt_size_t)offset)
    {
        return -RT_EINVAL;
    }
    if (size == 0U)
    {
        return 0;
    }

    result = rt_mutex_take(&gd25q64e_lock, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return result;
    }

    address = (rt_uint32_t)offset;
    remaining = size;
    while (remaining > 0U)
    {
        page_remaining = GD25Q64E_PAGE_SIZE - (address % GD25Q64E_PAGE_SIZE);
        write_size = remaining < page_remaining ? remaining : page_remaining;

        result = gd25q64e_write_enable();
        if (result == RT_EOK)
        {
            result = gd25q64e_transfer(GD25Q64E_CMD_QUAD_PAGE_PROGRAM, 1,
                                       address, 24, 1, 0,
                                       buf, RT_NULL, write_size, 4);
        }
        if (result == RT_EOK)
        {
            result = gd25q64e_wait_status(GD25Q64E_STATUS_WIP, 0,
                                          GD25Q64E_PROGRAM_TIMEOUT_MS,
                                          RT_TRUE);
        }
        if (result != RT_EOK)
        {
            break;
        }

        address += (rt_uint32_t)write_size;
        buf += write_size;
        remaining -= write_size;
    }

    rt_mutex_release(&gd25q64e_lock);
    return result == RT_EOK ? (int)size : result;
}

static int gd25q64e_erase(long offset, rt_size_t size)
{
    rt_size_t remaining;
    rt_uint32_t address;
    rt_err_t result;

    if (!gd25q64e_ready)
    {
        return -RT_EIO;
    }
    if (offset < 0 || ((rt_size_t)offset % GD25Q64E_SECTOR_SIZE) != 0U ||
        (size % GD25Q64E_SECTOR_SIZE) != 0U ||
        (rt_size_t)offset > GD25Q64E_FLASH_SIZE ||
        size > GD25Q64E_FLASH_SIZE - (rt_size_t)offset)
    {
        return -RT_EINVAL;
    }
    if (size == 0U)
    {
        return 0;
    }

    result = rt_mutex_take(&gd25q64e_lock, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        return result;
    }

    address = (rt_uint32_t)offset;
    remaining = size;
    while (remaining > 0U)
    {
        result = gd25q64e_write_enable();
        if (result == RT_EOK)
        {
            result = gd25q64e_transfer(GD25Q64E_CMD_ERASE_4K, 1,
                                       address, 24, 1, 0,
                                       RT_NULL, RT_NULL, 0, 0);
        }
        if (result == RT_EOK)
        {
            result = gd25q64e_wait_status(GD25Q64E_STATUS_WIP, 0,
                                          GD25Q64E_ERASE_TIMEOUT_MS,
                                          RT_TRUE);
        }
        if (result != RT_EOK)
        {
            break;
        }

        address += GD25Q64E_SECTOR_SIZE;
        remaining -= GD25Q64E_SECTOR_SIZE;
    }

    rt_mutex_release(&gd25q64e_lock);
    return result == RT_EOK ? (int)size : result;
}

const struct fal_flash_dev gd25q64e_flash =
{
    .name = "gd25q64e",
    .addr = 0,
    .len = GD25Q64E_FLASH_SIZE,
    .blk_size = GD25Q64E_SECTOR_SIZE,
    .ops =
    {
        .init = gd25q64e_init,
        .read = gd25q64e_read,
        .write = gd25q64e_write,
        .erase = gd25q64e_erase,
    },
    .write_gran = 1,
};

#endif /* BSP_USING_FLASH_FATFS */
