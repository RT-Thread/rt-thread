/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-26     CYFS         add SDIO block read and write utest
 */

/**
 * Test Case Name: SDIO Block Read and Write Test
 *
 * Test Objectives:
 * - Verify SDIO block-device geometry and read/write operations.
 * - Verify single-block and multi-block transfers at the beginning and end
 *   of the configured block device.
 * - Verify data remains readable after closing and reopening the device.
 *
 * Test Environment:
 * - Insert a writable SD card.
 * - Do not mount or otherwise access the same card while this test runs.
 * - Existing data in the configured sectors will be overwritten.
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/classes/block.h>
#include "utest.h"

#ifdef RT_UTEST_SDIO

#define SDIO_UTEST_DEVICE_NAME       RT_SDIO_UTEST_DEVICE_NAME
#define SDIO_UTEST_START_SECTOR      ((rt_off_t)RT_SDIO_UTEST_START_SECTOR)
#define SDIO_UTEST_SECTOR_COUNT      ((rt_size_t)RT_SDIO_UTEST_SECTOR_COUNT)
#define SDIO_UTEST_LOOP_COUNT        ((rt_size_t)RT_SDIO_UTEST_LOOP_COUNT)
#define SDIO_UTEST_DEVICE_WAIT_MS    RT_SDIO_UTEST_DEVICE_WAIT_MS

#define SDIO_UTEST_SECTOR_SIZE       512u

static rt_device_t sdio_test_dev;
static struct rt_device_blk_geometry sdio_test_geome;
static rt_uint8_t *sdio_test_write_buf;
static rt_uint8_t *sdio_test_read_buf;
static rt_size_t sdio_test_buf_size;
static rt_bool_t sdio_test_opened;

static void sdio_test_free_buffers(void)
{
    if (sdio_test_write_buf != RT_NULL)
    {
        rt_free(sdio_test_write_buf);
        sdio_test_write_buf = RT_NULL;
    }
    if (sdio_test_read_buf != RT_NULL)
    {
        rt_free(sdio_test_read_buf);
        sdio_test_read_buf = RT_NULL;
    }

    sdio_test_buf_size = 0;
}

static rt_device_t sdio_test_find_device(void)
{
    rt_device_t dev;
    rt_tick_t wait_ticks;
    rt_tick_t start;

    wait_ticks = rt_tick_from_millisecond(SDIO_UTEST_DEVICE_WAIT_MS);
    start = rt_tick_get();

    do
    {
        dev = rt_device_find(SDIO_UTEST_DEVICE_NAME);
        if (dev != RT_NULL)
        {
            return dev;
        }

        if (wait_ticks == 0)
        {
            break;
        }

        rt_thread_mdelay(100);
    } while ((rt_tick_t)(rt_tick_get() - start) < wait_ticks);

    return RT_NULL;
}

static void sdio_test_fill_pattern(rt_uint8_t *buffer, rt_uint8_t seed)
{
    rt_size_t i;

    for (i = 0; i < sdio_test_buf_size; i++)
    {
        buffer[i] = (rt_uint8_t)(seed ^ (rt_uint8_t)(i * 17u + (i >> 3)));
    }
}

static rt_err_t sdio_test_transfer(rt_off_t sector,
                                    rt_size_t sector_count,
                                    rt_uint8_t seed)
{
    rt_ssize_t result;
    rt_size_t transfer_size;

    transfer_size = sdio_test_geome.bytes_per_sector * sector_count;

    sdio_test_fill_pattern(sdio_test_write_buf, seed);
    rt_memset(sdio_test_read_buf, 0, sdio_test_buf_size);

    result = rt_device_write(sdio_test_dev,
                             sector,
                             sdio_test_write_buf,
                             sector_count);
    if (result != (rt_ssize_t)sector_count)
    {
        LOG_E("SDIO write failed at sector %ld, result: %ld",
              (long)sector, (long)result);
        return -RT_EIO;
    }

    result = rt_device_read(sdio_test_dev,
                            sector,
                            sdio_test_read_buf,
                            sector_count);
    if (result != (rt_ssize_t)sector_count)
    {
        LOG_E("SDIO read failed at sector %ld, result: %ld",
              (long)sector, (long)result);
        return -RT_EIO;
    }

    if (rt_memcmp(sdio_test_write_buf,
                  sdio_test_read_buf,
                  transfer_size) != 0)
    {
        LOG_E("SDIO data verification failed at sector %ld", (long)sector);
        return -RT_EIO;
    }

    return RT_EOK;
}

static void sdio_test_check_geometry(void)
{
    uassert_not_null(sdio_test_dev);
    uassert_int_equal(sdio_test_dev->type, RT_Device_Class_Block);
    uassert_int_equal(sdio_test_geome.bytes_per_sector,
                      SDIO_UTEST_SECTOR_SIZE);
    uassert_value_greater(sdio_test_geome.sector_count, 0);
}

static void sdio_test_start_sector(void)
{
    rt_size_t i;
    rt_err_t result;

    for (i = 0; i < SDIO_UTEST_LOOP_COUNT; i++)
    {
        result = sdio_test_transfer(SDIO_UTEST_START_SECTOR,
                                     SDIO_UTEST_SECTOR_COUNT,
                                     (rt_uint8_t)(0x21u + i));
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            return;
        }
    }
}

static void sdio_test_end_sector(void)
{
    rt_off_t end_sector;
    rt_size_t i;
    rt_err_t result;

    end_sector = (rt_off_t)(sdio_test_geome.sector_count -
                            SDIO_UTEST_SECTOR_COUNT);
    if (end_sector == SDIO_UTEST_START_SECTOR)
    {
        LOG_I("SDIO test range covers the whole device; skip duplicate end test");
        return;
    }

    for (i = 0; i < SDIO_UTEST_LOOP_COUNT; i++)
    {
        result = sdio_test_transfer(end_sector,
                                     SDIO_UTEST_SECTOR_COUNT,
                                     (rt_uint8_t)(0x61u + i));
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            return;
        }
    }
}

static void sdio_test_single_sector(void)
{
    rt_err_t result;

    result = sdio_test_transfer(SDIO_UTEST_START_SECTOR, 1, 0x11);
    uassert_int_equal(result, RT_EOK);
}

static void sdio_test_reopen(void)
{
    rt_ssize_t result;
    rt_err_t err;
    rt_uint8_t seed = 0xA5;

    sdio_test_fill_pattern(sdio_test_write_buf, seed);
    result = rt_device_write(sdio_test_dev,
                             SDIO_UTEST_START_SECTOR,
                             sdio_test_write_buf,
                             SDIO_UTEST_SECTOR_COUNT);
    uassert_int_equal(result, (rt_ssize_t)SDIO_UTEST_SECTOR_COUNT);
    if (result != (rt_ssize_t)SDIO_UTEST_SECTOR_COUNT)
    {
        return;
    }

    err = rt_device_close(sdio_test_dev);
    uassert_int_equal(err, RT_EOK);
    if (err != RT_EOK)
    {
        return;
    }
    sdio_test_opened = RT_FALSE;

    err = rt_device_open(sdio_test_dev, RT_DEVICE_OFLAG_RDWR);
    uassert_int_equal(err, RT_EOK);
    if (err != RT_EOK)
    {
        return;
    }
    sdio_test_opened = RT_TRUE;

    rt_memset(sdio_test_read_buf, 0, sdio_test_buf_size);
    result = rt_device_read(sdio_test_dev,
                            SDIO_UTEST_START_SECTOR,
                            sdio_test_read_buf,
                            SDIO_UTEST_SECTOR_COUNT);
    uassert_int_equal(result, (rt_ssize_t)SDIO_UTEST_SECTOR_COUNT);
    if (result != (rt_ssize_t)SDIO_UTEST_SECTOR_COUNT)
    {
        return;
    }

    uassert_buf_equal(sdio_test_write_buf,
                      sdio_test_read_buf,
                      sdio_test_buf_size);
}

static rt_err_t utest_tc_init(void)
{
    rt_err_t result;

    sdio_test_dev = sdio_test_find_device();
    if (sdio_test_dev == RT_NULL)
    {
        LOG_E("SDIO block device %s not found", SDIO_UTEST_DEVICE_NAME);
        return -RT_ERROR;
    }

    if (sdio_test_dev->type != RT_Device_Class_Block)
    {
        LOG_E("Device %s is not a block device", SDIO_UTEST_DEVICE_NAME);
        return -RT_EINVAL;
    }

    rt_memset(&sdio_test_geome, 0, sizeof(sdio_test_geome));
    result = rt_device_control(sdio_test_dev,
                               RT_DEVICE_CTRL_BLK_GETGEOME,
                               &sdio_test_geome);
    if (result != RT_EOK)
    {
        LOG_E("Get SDIO geometry failed, result: %d", result);
        return result;
    }

    if (sdio_test_geome.bytes_per_sector != SDIO_UTEST_SECTOR_SIZE)
    {
        LOG_E("Unsupported SDIO sector size: %u",
              sdio_test_geome.bytes_per_sector);
        return -RT_EINVAL;
    }

    if (sdio_test_geome.sector_count < SDIO_UTEST_SECTOR_COUNT)
    {
        LOG_E("SDIO device is too small: %lu sectors",
              (unsigned long)sdio_test_geome.sector_count);
        return -RT_EINVAL;
    }

    if (SDIO_UTEST_START_SECTOR < 0 ||
        (rt_uint64_t)SDIO_UTEST_START_SECTOR + SDIO_UTEST_SECTOR_COUNT >
        sdio_test_geome.sector_count)
    {
        LOG_E("SDIO test range is out of bounds: start=%ld, count=%u",
              (long)SDIO_UTEST_START_SECTOR,
              (unsigned int)SDIO_UTEST_SECTOR_COUNT);
        return -RT_EINVAL;
    }

    sdio_test_buf_size = sdio_test_geome.bytes_per_sector *
                         SDIO_UTEST_SECTOR_COUNT;
    sdio_test_write_buf = (rt_uint8_t *)rt_malloc(sdio_test_buf_size);
    sdio_test_read_buf = (rt_uint8_t *)rt_malloc(sdio_test_buf_size);
    if (sdio_test_write_buf == RT_NULL || sdio_test_read_buf == RT_NULL)
    {
        LOG_E("Allocate SDIO test buffer failed, size: %u",
              (unsigned int)sdio_test_buf_size);
        sdio_test_free_buffers();
        return -RT_ENOMEM;
    }

    result = rt_device_open(sdio_test_dev, RT_DEVICE_OFLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("Open SDIO device %s failed, result: %d",
              SDIO_UTEST_DEVICE_NAME, result);
        sdio_test_free_buffers();
        return result;
    }
    sdio_test_opened = RT_TRUE;

    LOG_I("SDIO test device=%s, sector_count=%lu, start=%ld, count=%u",
          SDIO_UTEST_DEVICE_NAME,
          (unsigned long)sdio_test_geome.sector_count,
          (long)SDIO_UTEST_START_SECTOR,
          (unsigned int)SDIO_UTEST_SECTOR_COUNT);

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_err_t result = RT_EOK;

    if (sdio_test_opened)
    {
        result = rt_device_close(sdio_test_dev);
        sdio_test_opened = RT_FALSE;
    }

    sdio_test_free_buffers();
    sdio_test_dev = RT_NULL;
    rt_memset(&sdio_test_geome, 0, sizeof(sdio_test_geome));

    return result;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(sdio_test_check_geometry);
    UTEST_UNIT_RUN(sdio_test_single_sector);
    UTEST_UNIT_RUN(sdio_test_start_sector);
    UTEST_UNIT_RUN(sdio_test_end_sector);
    UTEST_UNIT_RUN(sdio_test_reopen);
}

UTEST_TC_EXPORT(testcase,
                "components.drivers.sdio.read_write",
                utest_tc_init,
                utest_tc_cleanup,
                30);

#endif /* RT_UTEST_SDIO */
