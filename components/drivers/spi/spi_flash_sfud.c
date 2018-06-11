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

#ifdef RT_DEBUG_SFUD
#define DEBUG_TRACE         rt_kprintf("[SFUD] "); rt_kprintf
#else
#define DEBUG_TRACE(...)
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

static rt_err_t rt_sfud_control(rt_device_t dev, int cmd, void *args) {
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
    rt_kprintf("[SFUD] (%s:%ld) ", file, line);
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
    rt_kprintf("[SFUD] ");
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
    if (RT_TICK_PER_SECOND < 1000) {
        rt_kprintf("[SFUD] Warning: The OS tick(%d) is less than 1000. So the flash write will take more time.\n", RT_TICK_PER_SECOND);
    }
    /* 100 microsecond delay */
    flash->retry.delay = retry_delay_100us;
    /* 60 seconds timeout */
    flash->retry.times = 60 * 10000;


    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops flash_device_ops = 
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_sfud_read,
    rt_sfud_write,
    rt_sfud_control
};
#endif

/**
 * Probe SPI flash by SFUD(Serial Flash Universal Driver) driver library and though SPI device.
 *
 * @param spi_flash_dev_name the name which will create SPI flash device
 * @param spi_dev_name using SPI device name
 *
 * @return probed SPI flash device, probe failed will return RT_NULL
 */
rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name) {
    rt_spi_flash_device_t rtt_dev = RT_NULL;
    sfud_flash *sfud_dev = RT_NULL;
    char *spi_flash_dev_name_bak = RT_NULL, *spi_dev_name_bak = RT_NULL;
    /* using default flash SPI configuration for initialize SPI Flash
     * @note you also can change the SPI to other configuration after initialized finish */
    struct rt_spi_configuration cfg = RT_SFUD_DEFAULT_SPI_CFG;
    extern sfud_err sfud_device_init(sfud_flash *flash);

    RT_ASSERT(spi_flash_dev_name);
    RT_ASSERT(spi_dev_name);

    rtt_dev = (rt_spi_flash_device_t) rt_malloc(sizeof(struct spi_flash_device));
    sfud_dev = (sfud_flash_t) rt_malloc(sizeof(sfud_flash));
    spi_flash_dev_name_bak = (char *) rt_malloc(rt_strlen(spi_flash_dev_name) + 1);
    spi_dev_name_bak = (char *) rt_malloc(rt_strlen(spi_dev_name) + 1);

    if (rtt_dev) {
        rt_memset(rtt_dev, 0, sizeof(struct spi_flash_device));
        /* initialize lock */
        rt_mutex_init(&(rtt_dev->lock), spi_flash_dev_name, RT_IPC_FLAG_FIFO);
    }

    if (rtt_dev && sfud_dev && spi_flash_dev_name_bak && spi_dev_name_bak) {
        rt_memset(sfud_dev, 0, sizeof(sfud_flash));
        rt_strncpy(spi_flash_dev_name_bak, spi_flash_dev_name, rt_strlen(spi_flash_dev_name));
        rt_strncpy(spi_dev_name_bak, spi_dev_name, rt_strlen(spi_dev_name));
        /* make string end sign */
        spi_flash_dev_name_bak[rt_strlen(spi_flash_dev_name)] = '\0';
        spi_dev_name_bak[rt_strlen(spi_dev_name)] = '\0';
        /* SPI configure */
        {
            /* RT-Thread SPI device initialize */
            rtt_dev->rt_spi_device = (struct rt_spi_device *) rt_device_find(spi_dev_name);
            if (rtt_dev->rt_spi_device == RT_NULL || rtt_dev->rt_spi_device->parent.type != RT_Device_Class_SPIDevice) {
                rt_kprintf("ERROR: SPI device %s not found!\n", spi_dev_name);
                goto error;
            }
            sfud_dev->spi.name = spi_dev_name_bak;
            rt_spi_configure(rtt_dev->rt_spi_device, &cfg);
        }
        /* SFUD flash device initialize */
        {
            sfud_dev->name = spi_flash_dev_name_bak;
            /* accessed each other */
            rtt_dev->user_data = sfud_dev;
            rtt_dev->flash_device.user_data = rtt_dev;
            sfud_dev->user_data = rtt_dev;
            /* initialize SFUD device */
            if (sfud_device_init(sfud_dev) != SFUD_SUCCESS) {
                rt_kprintf("ERROR: SPI flash probe failed by SPI device %s.\n", spi_dev_name);
                goto error;
            }
            /* when initialize success, then copy SFUD flash device's geometry to RT-Thread SPI flash device */
            rtt_dev->geometry.sector_count = sfud_dev->chip.capacity / sfud_dev->chip.erase_gran;
            rtt_dev->geometry.bytes_per_sector = sfud_dev->chip.erase_gran;
            rtt_dev->geometry.block_size = sfud_dev->chip.erase_gran;
        }

        /* register device */
        rtt_dev->flash_device.type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
        rtt_dev->flash_device.ops  = &flash_device_ops;
#else
        rtt_dev->flash_device.init = RT_NULL;
        rtt_dev->flash_device.open = RT_NULL;
        rtt_dev->flash_device.close = RT_NULL;
        rtt_dev->flash_device.read = rt_sfud_read;
        rtt_dev->flash_device.write = rt_sfud_write;
        rtt_dev->flash_device.control = rt_sfud_control;
#endif

        rt_device_register(&(rtt_dev->flash_device), spi_flash_dev_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

        DEBUG_TRACE("Probe SPI flash %s by SPI device %s success.\n",spi_flash_dev_name, spi_dev_name);
        return rtt_dev;
    } else {
        rt_kprintf("ERROR: Low memory.\n");
        goto error;
    }

error:

    if (rtt_dev) {
        rt_mutex_detach(&(rtt_dev->lock));
    }
    /* may be one of objects memory was malloc success, so need free all */
    rt_free(rtt_dev);
    rt_free(sfud_dev);
    rt_free(spi_flash_dev_name_bak);
    rt_free(spi_dev_name_bak);

    return RT_NULL;
}

/**
 * Delete SPI flash device
 *
 * @param spi_flash_dev SPI flash device
 *
 * @return the operation status, RT_EOK on successful
 */
rt_err_t rt_sfud_flash_delete(rt_spi_flash_device_t spi_flash_dev) {
    sfud_flash *sfud_flash_dev = (sfud_flash *) (spi_flash_dev->user_data);

    RT_ASSERT(spi_flash_dev);
    RT_ASSERT(sfud_flash_dev);

    rt_device_unregister(&(spi_flash_dev->flash_device));

    rt_mutex_detach(&(spi_flash_dev->lock));

    rt_free(sfud_flash_dev->spi.name);
    rt_free(sfud_flash_dev->name);
    rt_free(sfud_flash_dev);
    rt_free(spi_flash_dev);

    return RT_EOK;
}

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)

#include <finsh.h>

static void sf(uint8_t argc, char **argv) {

#define CMD_PROBE_INDEX               0
#define CMD_READ_INDEX                1
#define CMD_WRITE_INDEX               2
#define CMD_ERASE_INDEX               3
#define CMD_RW_STATUS_INDEX           4
#define CMD_BENCH_INDEX               5

    sfud_err result = SFUD_SUCCESS;
    static const sfud_flash *sfud_dev = NULL;
    static rt_spi_flash_device_t rtt_dev = NULL, rtt_dev_bak = NULL;
    size_t i = 0;

    const char* sf_help_info[] = {
            [CMD_PROBE_INDEX]     = "sf probe [spi_device]           - probe and init SPI flash by given 'spi_device'",
            [CMD_READ_INDEX]      = "sf read addr size               - read 'size' bytes starting at 'addr'",
            [CMD_WRITE_INDEX]     = "sf write addr data1 ... dataN   - write some bytes 'data' to flash starting at 'addr'",
            [CMD_ERASE_INDEX]     = "sf erase addr size              - erase 'size' bytes starting at 'addr'",
            [CMD_RW_STATUS_INDEX] = "sf status [<volatile> <status>] - read or write '1:volatile|0:non-volatile' 'status'",
            [CMD_BENCH_INDEX]     = "sf bench                        - full chip benchmark. DANGER: It will erase full chip!",
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

        if (!strcmp(operator, "probe")) {
            if (argc < 3) {
                rt_kprintf("Usage: %s.\n", sf_help_info[CMD_PROBE_INDEX]);
            } else {
                char *spi_dev_name = argv[2];
                rtt_dev_bak = rtt_dev;
                rtt_dev = rt_sfud_flash_probe("sf_cmd", spi_dev_name);
                if (!rtt_dev) {
                    return;
                }
                /* already probe then delete the old SPI flash device */
                if(rtt_dev_bak) {
                    rt_sfud_flash_delete(rtt_dev_bak);
                }
                sfud_dev = (sfud_flash_t)rtt_dev->user_data;
                if (sfud_dev->chip.capacity < 1024 * 1024) {
                    rt_kprintf("%d KB %s is current selected device.\n", sfud_dev->chip.capacity / 1024, sfud_dev->name);
                } else {
                    rt_kprintf("%d MB %s is current selected device.\n", sfud_dev->chip.capacity / 1024 / 1024,
                            sfud_dev->name);
                }
            }
        } else {
            if (!sfud_dev) {
                rt_kprintf("No flash device selected. Please run 'sf probe'.\n");
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
                        result = sfud_read(sfud_dev, addr, size, data);
                        if (result == SFUD_SUCCESS) {
                            rt_kprintf("Read the %s flash data success. Start from 0x%08X, size is %ld. The data is:\n",
                                    sfud_dev->name, addr, size);
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
                        result = sfud_write(sfud_dev, addr, size, data);
                        if (result == SFUD_SUCCESS) {
                            rt_kprintf("Write the %s flash data success. Start from 0x%08X, size is %ld.\n",
                                    sfud_dev->name, addr, size);
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
                    result = sfud_erase(sfud_dev, addr, size);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("Erase the %s flash data success. Start from 0x%08X, size is %ld.\n", sfud_dev->name,
                                addr, size);
                    }
                }
            } else if (!rt_strcmp(operator, "status")) {
                if (argc < 3) {
                    uint8_t status;
                    result = sfud_read_status(sfud_dev, &status);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("The %s flash status register current value is 0x%02X.\n", sfud_dev->name, status);
                    }
                } else if (argc == 4) {
                    bool is_volatile = atoi(argv[2]);
                    uint8_t status = atoi(argv[3]);
                    result = sfud_write_status(sfud_dev, is_volatile, status);
                    if (result == SFUD_SUCCESS) {
                        rt_kprintf("Write the %s flash status register to 0x%02X success.\n", sfud_dev->name, status);
                    }
                } else {
                    rt_kprintf("Usage: %s.\n", sf_help_info[CMD_RW_STATUS_INDEX]);
                    return;
                }
            } else if (!rt_strcmp(operator, "bench")) {
                if ((argc > 2 && rt_strcmp(argv[2], "yes")) || argc < 3) {
                    rt_kprintf("DANGER: It will erase full chip! Please run 'sf bench yes'.\n");
                    return;
                }
                /* full chip benchmark test */
                addr = 0;
                size = sfud_dev->chip.capacity;
                uint32_t start_time, time_cast;
                size_t write_size = SFUD_WRITE_MAX_PAGE_SIZE, read_size = 4096;
                uint8_t *write_data = rt_malloc(write_size), *read_data = rt_malloc(read_size);

                if (write_data && read_data) {
                    rt_memset(write_data, 0x55, write_size);
                    /* benchmark testing */
                    rt_kprintf("Erasing the %s %ld bytes data, waiting...\n", sfud_dev->name, size);
                    start_time = rt_tick_get();
                    result = sfud_erase(sfud_dev, addr, size);
                    if (result == SFUD_SUCCESS) {
                        time_cast = rt_tick_get() - start_time;
                        rt_kprintf("Erase benchmark success, total time: %d.%03dS.\n", time_cast / RT_TICK_PER_SECOND,
                                time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));
                    } else {
                        rt_kprintf("Erase benchmark has an error. Error code: %d.\n", result);
                    }
                    /* write test */
                    rt_kprintf("Writing the %s %ld bytes data, waiting...\n", sfud_dev->name, size);
                    start_time = rt_tick_get();
                    for (i = 0; i < size; i += write_size) {
                        result = sfud_write(sfud_dev, addr + i, write_size, write_data);
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
                    rt_kprintf("Reading the %s %ld bytes data, waiting...\n", sfud_dev->name, size);
                    start_time = rt_tick_get();
                    for (i = 0; i < size; i += read_size) {
                        if (i + read_size <= size) {
                            result = sfud_read(sfud_dev, addr + i, read_size, read_data);
                        } else {
                            result = sfud_read(sfud_dev, addr + i, size - i, read_data);
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
