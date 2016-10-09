/*
 * File      : spi_flash_sfud.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2016, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-28     armink       first version.
 */

#include <stdint.h>
#include <rtdevice.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#ifdef RT_USING_SFUD

#if RT_DEBUG_SFUD
#define SFUD_TRACE         rt_kprintf
#else
#define SFUD_TRACE(...)
#endif /* RT_DEBUG_SFUD */

#ifndef RT_SFUD_DEFAULT_SPI_CFG
/* read the JEDEC SFDP command must run at 50 MHz or less */
#define RT_SFUD_DEFAULT_SPI_CFG                 \
{                                               \
    .mode = RT_SPI_MODE_0 | RT_SPI_MSB,         \
    .data_width = 8,                            \
    .max_hz = 50 * 1000 * 1000,                 \
}
#endif

static char log_buf[RT_CONSOLEBUF_SIZE];

void sfud_log_debug(const char *file, const long line, const char *format, ...);

static rt_err_t rt_sfud_control(rt_device_t dev, rt_uint8_t cmd, void *args) {
    RT_ASSERT(dev != RT_NULL);

    switch (cmd) {
    case RT_DEVICE_CTRL_BLK_GETGEOME: {
        struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *) args;
        struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (dev->user_data);

        if (rtt_dev == RT_NULL || geometry == RT_NULL) {
            return -RT_ERROR;
        }

        geometry->bytes_per_sector = rtt_dev->geometry.bytes_per_sector;
        geometry->sector_count = rtt_dev->geometry.sector_count;
        geometry->block_size = rtt_dev->geometry.block_size;
        break;
    }
    case RT_DEVICE_CTRL_BLK_ERASE: {
        rt_uint32_t *addrs = (rt_uint32_t *) args, start_addr = addrs[0], end_addr = addrs[1], phy_start_addr;
        struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (dev->user_data);
        sfud_flash *sfud_dev = (sfud_flash *) (rtt_dev->user_data);
        rt_size_t phy_size;

        if (addrs == RT_NULL || start_addr > end_addr || rtt_dev == RT_NULL || sfud_dev == RT_NULL) {
            return -RT_ERROR;
        }

        phy_start_addr = start_addr * rtt_dev->geometry.bytes_per_sector;
        phy_size = (end_addr - start_addr) * rtt_dev->geometry.bytes_per_sector;

        if (sfud_erase(sfud_dev, phy_start_addr, phy_size) != SFUD_SUCCESS) {
            return -RT_ERROR;
        }
        break;
    }
    }

    return RT_EOK;
}


static rt_size_t rt_sfud_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size) {
    struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (dev->user_data);
    sfud_flash *sfud_dev = (sfud_flash *) (rtt_dev->user_data);
    /* change the block device¡¯s logic address to physical address */
    rt_off_t phy_pos = pos * rtt_dev->geometry.bytes_per_sector;
    rt_size_t phy_size = size * rtt_dev->geometry.bytes_per_sector;

    if (sfud_read(sfud_dev, phy_pos, phy_size, buffer) != SFUD_SUCCESS) {
        return 0;
    } else {
        return size;
    }
}

static rt_size_t rt_sfud_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size) {
    struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (dev->user_data);
    sfud_flash *sfud_dev = (sfud_flash *) (rtt_dev->user_data);
    /* change the block device¡¯s logic address to physical address */
    rt_off_t phy_pos = pos * rtt_dev->geometry.bytes_per_sector;
    rt_size_t phy_size = size * rtt_dev->geometry.bytes_per_sector;

    if (sfud_erase_write(sfud_dev, phy_pos, phy_size, buffer) != SFUD_SUCCESS) {
        return 0;
    } else {
        return size;
    }
}

/**
 * SPI write data then read data
 */
static sfud_err spi_write_read(const sfud_spi *spi, const uint8_t *write_buf, size_t write_size, uint8_t *read_buf,
        size_t read_size) {
    sfud_err result = SFUD_SUCCESS;
    sfud_flash *sfud_dev = (sfud_flash *) (spi->user_data);
    struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (sfud_dev->user_data);

    if (write_size) {
        RT_ASSERT(write_buf);
    }
    if (read_size) {
        RT_ASSERT(read_buf);
    }

    if (write_size && read_size) {
        if (rt_spi_send_then_recv(rtt_dev->rt_spi_device, write_buf, write_size, read_buf, read_size) != RT_EOK) {
            result = SFUD_ERR_TIMEOUT;
        }
    } else if (write_size) {
        if (rt_spi_send(rtt_dev->rt_spi_device, write_buf, write_size) == 0) {
            result = SFUD_ERR_TIMEOUT;
        }
    } else {
        if (rt_spi_recv(rtt_dev->rt_spi_device, read_buf, read_size) == 0) {
            result = SFUD_ERR_TIMEOUT;
        }
    }

    return result;
}

static void spi_lock(const sfud_spi *spi) {
    sfud_flash *sfud_dev = (sfud_flash *) (spi->user_data);
    struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (sfud_dev->user_data);

    rt_mutex_take(&(rtt_dev->lock), RT_WAITING_FOREVER);
}

static void spi_unlock(const sfud_spi *spi) {
    sfud_flash *sfud_dev = (sfud_flash *) (spi->user_data);
    struct spi_flash_device *rtt_dev = (struct spi_flash_device *) (sfud_dev->user_data);

    rt_mutex_release(&(rtt_dev->lock));
}

static void retry_delay_ms(void) {
    /* millisecond delay */
    rt_tick_from_millisecond(1);
}

static void retry_delay_100us(void) {
    /* 100 microsecond delay */
    rt_thread_delay((RT_TICK_PER_SECOND * 1 + 9999) / 10000);
}

/**
 * This function is print debug info.
 *
 * @param file the file which has call this function
 * @param line the line number which has call this function
 * @param format output format
 * @param ... args
 */
void sfud_log_debug(const char *file, const long line, const char *format, ...) {
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    rt_kprintf("[SFUD](%s:%ld) ", file, line);
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    rt_kprintf("%s\n", log_buf);
    va_end(args);
}

/**
 * This function is print routine info.
 *
 * @param format output format
 * @param ... args
 */
void sfud_log_info(const char *format, ...) {
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);
    rt_kprintf("[SFUD]");
    /* must use vprintf to print */
    vsnprintf(log_buf, sizeof(log_buf), format, args);
    rt_kprintf("%s\n", log_buf);
    va_end(args);
}

sfud_err sfud_spi_port_init(sfud_flash *flash) {
    sfud_err result = SFUD_SUCCESS;

    /* port SPI device interface */
    flash->spi.wr = spi_write_read;
    flash->spi.lock = spi_lock;
    flash->spi.unlock = spi_unlock;
    flash->spi.user_data = flash;
    /* 100 microsecond delay */
    flash->retry.delay = retry_delay_100us;
    /* 60 seconds timeout */
    flash->retry.times = 60 * 10000;


    return result;
}

/**
 * SPI Flash device initialize by SFUD(Serial Flash Universal Driver) library
 *
 * @param rtt_dev the static RT-Thread's flash device object
 * @param sfud_dev the static SFUD's flash device object
 *
 * @return result
 */
rt_err_t rt_sfud_init(struct spi_flash_device *rtt_dev, sfud_flash *sfud_dev) {
    extern sfud_err sfud_device_init(sfud_flash *flash);

    RT_ASSERT(rtt_dev);
    RT_ASSERT(sfud_dev);

    rt_memset(rtt_dev, 0, sizeof(struct spi_flash_device));

    /* SPI configure */
    {
        /* RT-Thread SPI device initialize */
        rtt_dev->rt_spi_device = (struct rt_spi_device *) rt_device_find(sfud_dev->spi.name);
        if (rtt_dev->rt_spi_device == RT_NULL) {
            SFUD_TRACE("spi device %s not found!\r\n", sfud_dev->spi.name);
            return -RT_ENOSYS;
        }
        /* using default flash SPI configuration for initialize SPI Flash
         * @note you also can change the SPI to other configuration after initialized finish */
        struct rt_spi_configuration cfg = RT_SFUD_DEFAULT_SPI_CFG;
        rt_spi_configure(rtt_dev->rt_spi_device, &cfg);
        /* initialize lock */
        rt_mutex_init(&(rtt_dev->lock), sfud_dev->name, RT_IPC_FLAG_FIFO);
    }


    /* SFUD flash device initialize */
    {
        /* accessed each other */
        rtt_dev->user_data = sfud_dev;
        rtt_dev->flash_device.user_data = rtt_dev;
        sfud_dev->user_data = rtt_dev;
        /* initialize SFUD device */
        if (sfud_device_init(sfud_dev) != SFUD_SUCCESS) {
            return -RT_EIO;
        }
        /* when initialize success, then copy SFUD flash device's geometry to RT-Thread SPI flash device */
        rtt_dev->geometry.sector_count = sfud_dev->chip.capacity / sfud_dev->chip.erase_gran;
        rtt_dev->geometry.bytes_per_sector = sfud_dev->chip.erase_gran;
        rtt_dev->geometry.block_size = sfud_dev->chip.erase_gran;
    }

    /* register device */
    rtt_dev->flash_device.type      = RT_Device_Class_Block;
    rtt_dev->flash_device.init      = RT_NULL;
    rtt_dev->flash_device.open      = RT_NULL;
    rtt_dev->flash_device.close     = RT_NULL;
    rtt_dev->flash_device.read      = rt_sfud_read;
    rtt_dev->flash_device.write     = rt_sfud_write;
    rtt_dev->flash_device.control   = rt_sfud_control;

    rt_device_register(&(rtt_dev->flash_device), sfud_dev->name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return RT_EOK;
}

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)

#include <finsh.h>

static void sf(uint8_t argc, char **argv) {

#define CMD_SETECT_INDEX              0
#define CMD_READ_INDEX                1
#define CMD_WRITE_INDEX               2
#define CMD_ERASE_INDEX               3
#define CMD_RW_STATUS_INDEX           4
#define CMD_BENCH_INDEX               5

    sfud_err result = SFUD_SUCCESS;
    const static sfud_flash *flash = NULL;
    size_t i = 0;

    const char* sf_help_info[] = {
            [CMD_SETECT_INDEX]    = "sf select [index]               - select a flash chip with device's index",
            [CMD_READ_INDEX]      = "sf read addr size               - read 'size' bytes starting at 'addr'",
            [CMD_WRITE_INDEX]     = "sf write addr data1 ... dataN   - write some bytes 'data' to flash starting at 'addr'",
            [CMD_ERASE_INDEX]     = "sf erase addr size              - erase 'size' bytes starting at 'addr'",
            [CMD_RW_STATUS_INDEX] = "sf status [<volatile> <status>] - read or write '1:volatile|0:non-volatile' 'status'",
            [CMD_BENCH_INDEX]     = "sf bench                        - full chip benchmark. DANGER: it will erase full chip!",
    };

    if (argc < 2) {
        rt_kprintf("Usage:\n");
        for (i = 0; i < sizeof(sf_help_info) / sizeof(char*); i++) {
            rt_kprintf("%s\n", sf_help_info[i]);
        }
        rt_kprintf("\n");
    } else {
        const char *operator = argv[1];
        uint32_t addr, size;

        if (!strcmp(operator, "select")) {
            if (argc < 3) {
                rt_kprintf("Usage: %s.\n", sf_help_info[CMD_SETECT_INDEX]);
                if (sfud_get_device_num() > 0) {
                    for (i = 0; i < sfud_get_device_num(); i++) {
                        if (sfud_get_device(i)->init_ok) {
                            rt_kprintf("The index %d flash device name is %s, ", i, sfud_get_device(i)->name);
                            if (sfud_get_device(i)->chip.capacity < 1024 * 1024) {
                                rt_kprintf("total is %d KB", sfud_get_device(i)->chip.capacity / 1024);
                            } else {
                                rt_kprintf("total is %d MB", sfud_get_device(i)->chip.capacity / 1024 / 1024);
                            }
                            if (sfud_get_device(i)->chip.name != NULL) {
                                rt_kprintf(", type is %s", sfud_get_device(i)->chip.name);
                            }
                            rt_kprintf(".\n");
                        }
                    }
                } else {
                    rt_kprintf("There is no flash device in device table.\n");
                }
            } else {
                size_t device_index = atol(argv[2]);
                if (device_index >= sfud_get_device_num()) {
                    rt_kprintf("Flash device index out bound[0:%d].\n", sfud_get_device_num() - 1);
                    return;
                }
                if (!sfud_get_device(device_index)->init_ok) {
                    rt_kprintf("Flash %s isn't initialize OK.\n", sfud_get_device(device_index)->name);
                    return;
                }
                flash = sfud_get_device(device_index);
                if (flash->chip.capacity < 1024 * 1024) {
                    rt_kprintf("%d KB %s is current selected device.\n", flash->chip.capacity / 1024, flash->name);
                } else {
                    rt_kprintf("%d MB %s is current selected device.\n", flash->chip.capacity / 1024 / 1024,
                            flash->name);
                }
            }
        } else {
            if (!flash) {
                rt_kprintf("No flash device selected. Please run 'sf select'.\n");
                return;
            }
            if (!rt_strcmp(operator, "read")) {
                if (argc < 4) {
                    rt_kprintf("Usage: %s.\n", sf_help_info[CMD_READ_INDEX]);
                    return;
                } else {
                    addr = atol(argv[2]);
                    size = atol(argv[3]);
                    uint8_t *data = rt_malloc(size);
                    if (data) {
                        result = sfud_read(flash, addr, size, data);
                        if (result == SFUD_SUCCESS) {
                            rt_kprintf("Read the %s flash data success. Start from 0x%08X, size is %ld. The data is:\n",
                                    flash->name, addr, size);
                            rt_kprintf("Offset (h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
                            for (i = 0; i < size; i++) {
                                if (i % 16 == 0) {
                                    rt_kprintf("[%08X] ", addr + i);
                                }
                                rt_kprintf("%02X ", data[i]);
                                if (((i + 1) % 16 == 0) || i == size - 1) {
                                    rt_kprintf("\n");
                                }
                            }
                            rt_kprintf("\n");
                        }
                        rt_free(data);
                    } else {
                        rt_kprintf("Low memory!\n");
                    }
                }
            } else if (!rt_strcmp(operator, "write")) {
                if (argc < 4) {
                    rt_kprintf("Usage: %s.\n", sf_help_info[CMD_WRITE_INDEX]);
                    return;
                } else {
                    addr = atol(argv[2]);
                    size = argc - 3;
                    uint8_t *data = rt_malloc(size);
                    if (data) {
                        for (i = 0; i < size; i++) {
                            data[i] = atoi(argv[3 + i]);
                        }
                        result = sfud_write(flash, addr, size, data);
                        if (result == SFUD_SUCCESS) {
                            rt_kprintf("Write the %s flash data success. Start from 0x%08X, size is %ld.\n",
                                    flash->name, addr, size);
                            rt_kprintf("Write data: ");
                            for (i = 0; i < size; i++) {
                                rt_kprintf("%d ", data[i]);
                            }
                            rt_kprintf(".\n");
                        }
                        rt_free(data);
                    } else {
                        rt_kprintf("Low memory!\n");
                    }
                }
            } else if (!rt_strcmp(operator, "erase")) {
                if (argc < 4) {
                    rt_kprintf("Usage: %s.\n", sf_help_info[CMD_ERASE_INDEX]);
                    return;
                } else {
                    addr = atol(argv[2]);
                    size = atol(argv[3]);
                    result = sfud_erase(flash, addr, size);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("Erase the %s flash data success. Start from 0x%08X, size is %ld.\n", flash->name,
                                addr, size);
                    }
                }
            } else if (!rt_strcmp(operator, "status")) {
                if (argc < 3) {
                    uint8_t status;
                    result = sfud_read_status(flash, &status);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("The %s flash status register current value is 0x%02X.\n", flash->name, status);
                    }
                } else if (argc == 4) {
                    bool is_volatile = atoi(argv[2]);
                    uint8_t status = atoi(argv[3]);
                    result = sfud_write_status(flash, is_volatile, status);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("Write the %s flash status register to 0x%02X success.\n", flash->name, status);
                    }
                } else {
                    rt_kprintf("Usage: %s.\n", sf_help_info[CMD_RW_STATUS_INDEX]);
                    return;
                }
            } else if (!rt_strcmp(operator, "bench")) {
                /* full chip benchmark test */
                addr = 0;
                size = flash->chip.capacity;
                uint32_t start_time, time_cast;
                rt_uint32_t total_mem, used_mem, max_uesd_mem;
                rt_memory_info(&total_mem, &used_mem, &max_uesd_mem);
                size_t write_size = SFUD_WRITE_MAX_PAGE_SIZE, read_size;
                if ((total_mem - used_mem) / 2 < size) {
                    read_size = (total_mem - used_mem) / 2;
                } else {
                    read_size = size;
                }
                uint8_t *write_data = rt_malloc(write_size), *read_data = rt_malloc(read_size);

                if (write_data && read_data) {
                    rt_memset(write_data, 0x55, write_size);
                    /* benchmark testing */
                    rt_kprintf("Erasing the %s %ld bytes data, waiting...\n", flash->name, size);
                    start_time = rt_tick_get();
                    result = sfud_erase(flash, addr, size);
                    if (result == SFUD_SUCCESS) {
                        time_cast = rt_tick_get() - start_time;
                        rt_kprintf("Erase benchmark success, total time: %d.%03dS.\n", time_cast / RT_TICK_PER_SECOND,
                                time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));
                    } else {
                        rt_kprintf("Erase benchmark has an error. Error code: %d.\n", result);
                    }
                    /* write test */
                    rt_kprintf("Writing the %s %ld bytes data, waiting...\n", flash->name, size);
                    start_time = rt_tick_get();
                    for (i = 0; i < size; i += write_size) {
                        result = sfud_write(flash, addr + i, write_size, write_data);
                        if (result != SFUD_SUCCESS) {
                            break;
                        }
                    }
                    if (result == SFUD_SUCCESS) {
                        time_cast = rt_tick_get() - start_time;
                        rt_kprintf("Write benchmark success, total time: %d.%03dS.\n", time_cast / RT_TICK_PER_SECOND,
                                time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));
                    } else {
                        rt_kprintf("Write benchmark has an error. Error code: %d.\n", result);
                    }
                    /* read test */
                    rt_kprintf("Reading the %s %ld bytes data, waiting...\n", flash->name, size);
                    start_time = rt_tick_get();
                    for (i = 0; i < size; i += read_size) {
                        if (i + read_size <= size) {
                            result = sfud_read(flash, addr + i, read_size, read_data);
                        } else {
                            result = sfud_read(flash, addr + i, size - i, read_data);
                        }
                        if (result != SFUD_SUCCESS) {
                            break;
                        }
                    }
                    if (result == SFUD_SUCCESS) {
                        time_cast = rt_tick_get() - start_time;
                        rt_kprintf("Read benchmark success, total time: %d.%03dS.\n", time_cast / RT_TICK_PER_SECOND,
                                time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));
                    } else {
                        rt_kprintf("Read benchmark has an error. Error code: %d.\n", result);
                    }
                } else {
                    rt_kprintf("Low memory!\n");
                }
                rt_free(write_data);
                rt_free(read_data);
            } else {
                rt_kprintf("Usage:\n");
                for (i = 0; i < sizeof(sf_help_info) / sizeof(char*); i++) {
                    rt_kprintf("%s\n", sf_help_info[i]);
                }
                rt_kprintf("\n");
                return;
            }
            if (result != SFUD_SUCCESS) {
                rt_kprintf("This flash operate has an error. Error code: %d.\n", result);
            }
        }
    }
}
MSH_CMD_EXPORT(sf, SPI Flash operate.);

#endif /* defined(RT_USING_FINSH) && defined(FINSH_USING_MSH) */

#endif /* RT_USING_SFUD */
