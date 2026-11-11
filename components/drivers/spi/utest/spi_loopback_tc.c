/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-02     CYFS         add SPI MOSI/MISO loopback utest
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "utest.h"

#ifdef RT_UTEST_SPI_LOOPBACK

#ifndef RT_UTEST_SPI_LOOPBACK_MAX_HZ
#define RT_UTEST_SPI_LOOPBACK_MAX_HZ 10000000
#endif

#define SPI_LOOPBACK_BUS_NAME   RT_UTEST_SPI_LOOPBACK_BUS_NAME
#define SPI_LOOPBACK_DEV_NAME   RT_UTEST_SPI_LOOPBACK_DEV_NAME
#define SPI_LOOPBACK_DATA_SIZE  RT_UTEST_SPI_LOOPBACK_DATA_SIZE
#define SPI_LOOPBACK_MAX_HZ     RT_UTEST_SPI_LOOPBACK_MAX_HZ
#define SPI_LOOPBACK_TIMEOUT    RT_UTEST_SPI_LOOPBACK_TIMEOUT
#define SPI_LOOPBACK_CLK_ENTRY(max_hz)      ((SPI_LOOPBACK_MAX_HZ > (max_hz)) ? (max_hz) : 0)
#define SPI_LOOPBACK_LEN_ENTRY(length)      ((SPI_LOOPBACK_DATA_SIZE > (length)) ? (length) : 0)
#define SPI_LOOPBACK_CLK_TABLE                                      \
{                                                                   \
    SPI_LOOPBACK_CLK_ENTRY(100000),                                 \
    SPI_LOOPBACK_CLK_ENTRY(400000),                                 \
    SPI_LOOPBACK_CLK_ENTRY(1000000),                                \
    SPI_LOOPBACK_CLK_ENTRY(2000000),                                \
    SPI_LOOPBACK_CLK_ENTRY(5000000),                                \
    SPI_LOOPBACK_CLK_ENTRY(10000000),                               \
    SPI_LOOPBACK_CLK_ENTRY(50000000),                               \
    SPI_LOOPBACK_MAX_HZ,                                            \
}
#define SPI_LOOPBACK_LEN_TABLE                                      \
{                                                                   \
    SPI_LOOPBACK_LEN_ENTRY(1),                                      \
    SPI_LOOPBACK_LEN_ENTRY(8),                                      \
    SPI_LOOPBACK_LEN_ENTRY(31),                                     \
    SPI_LOOPBACK_LEN_ENTRY(32),                                     \
    SPI_LOOPBACK_LEN_ENTRY(64),                                     \
    SPI_LOOPBACK_LEN_ENTRY(256),                                    \
    SPI_LOOPBACK_LEN_ENTRY(512),                                    \
    SPI_LOOPBACK_DATA_SIZE,                                         \
}

static struct rt_spi_device spi_loopback_dev;
static rt_bool_t spi_loopback_attached;
static rt_uint8_t tx_buf[SPI_LOOPBACK_DATA_SIZE];
static rt_uint8_t rx_buf[SPI_LOOPBACK_DATA_SIZE];
static const rt_uint32_t spi_loopback_clk_table[] = SPI_LOOPBACK_CLK_TABLE;
static const rt_size_t spi_loopback_len_table[] = SPI_LOOPBACK_LEN_TABLE;

static void spi_loopback_fill_pattern(rt_uint8_t *buf, rt_size_t size, rt_uint8_t seed)
{
    rt_size_t i;

    for (i = 0; i < size; i++)
    {
        buf[i] = (rt_uint8_t)(seed + i * 17 + (i >> 1));
    }
}

static rt_err_t spi_loopback_configure(rt_uint32_t max_hz)
{
    rt_err_t result;
    struct rt_spi_configuration cfg;

    rt_memset(&cfg, 0, sizeof(cfg));
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_NO_CS;
    cfg.max_hz = max_hz;

    spi_loopback_dev.config.usage_freq = 0;
    result = rt_spi_configure(&spi_loopback_dev, &cfg);
    if (result == -RT_EBUSY)
    {
        result = RT_EOK;
    }

    return result;
}

static rt_bool_t spi_loopback_check_length(rt_size_t length)
{
    if (length == 0)
    {
        return RT_FALSE;
    }

    if (length > sizeof(tx_buf))
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

static void spi_loopback_validate_length_table(void)
{
    rt_size_t i;
    rt_bool_t valid = RT_TRUE;

    for (i = 0; i < sizeof(spi_loopback_len_table) / sizeof(spi_loopback_len_table[0]); i++)
    {
        rt_size_t length = spi_loopback_len_table[i];

        if (length == 0)
        {
            continue;
        }

        if (length > sizeof(tx_buf))
        {
            LOG_E("SPI loopback length matrix[%u] = %u exceeds data size %u.",
                  (unsigned int)i, (unsigned int)length, (unsigned int)sizeof(tx_buf));
            valid = RT_FALSE;
            continue;
        }
    }

    uassert_true(valid);
}

static rt_bool_t spi_loopback_check_buffer(const rt_uint8_t *tx, const rt_uint8_t *rx,
                                           rt_size_t length, const char *stage,
                                           rt_size_t clk_index, rt_size_t len_index)
{
    rt_size_t i;

    if (rt_memcmp(tx, rx, length) == 0)
    {
        uassert_buf_equal(tx, rx, length);
        return RT_TRUE;
    }

    for (i = 0; i < length; i++)
    {
        if (tx[i] != rx[i])
        {
            LOG_E("SPI loopback %s mismatch: clk[%u], len[%u], offset %u, tx=0x%02x, rx=0x%02x.",
                  stage,
                  (unsigned int)clk_index,
                  (unsigned int)len_index,
                  (unsigned int)i,
                  tx[i],
                  rx[i]);
            break;
        }
    }

    uassert_buf_equal(tx, rx, length);
    return RT_FALSE;
}

static rt_bool_t spi_loopback_transfer_full_duplex(rt_size_t length, rt_uint8_t seed,
                                                  rt_size_t clk_index, rt_size_t len_index)
{
    rt_ssize_t result;

    if (!spi_loopback_check_length(length))
    {
        return RT_FALSE;
    }

    spi_loopback_fill_pattern(tx_buf, length, seed);
    rt_memset(rx_buf, 0, length);

    result = rt_spi_transfer(&spi_loopback_dev, tx_buf, rx_buf, length);
    uassert_int_equal(result, (rt_ssize_t)length);
    if (result != (rt_ssize_t)length)
    {
        return RT_FALSE;
    }

    return spi_loopback_check_buffer(tx_buf, rx_buf, length, "transfer", clk_index, len_index);
}

static rt_bool_t spi_loopback_sendrecv8(rt_uint8_t tx_data, rt_size_t clk_index)
{
    rt_uint8_t rx_data = 0;
    rt_err_t result;

    result = rt_spi_sendrecv8(&spi_loopback_dev, tx_data, &rx_data);
    uassert_int_equal(result, RT_EOK);
    if (result != RT_EOK)
    {
        return RT_FALSE;
    }

    if (rx_data != tx_data)
    {
        LOG_E("SPI loopback byte mismatch: clk[%u], tx=0x%02x, rx=0x%02x. Check the selected bus MOSI/MISO pins.",
              (unsigned int)clk_index,
              tx_data,
              rx_data);
    }
    uassert_int_equal(rx_data, tx_data);

    return (rx_data == tx_data) ? RT_TRUE : RT_FALSE;
}

static rt_bool_t spi_loopback_transfer_message(rt_size_t length, rt_uint8_t seed,
                                              rt_size_t clk_index, rt_size_t len_index)
{
    struct rt_spi_message msg1;
    struct rt_spi_message msg2;
    struct rt_spi_message *result;
    rt_size_t first_len;

    if (!spi_loopback_check_length(length))
    {
        return RT_FALSE;
    }

    if (length < 2)
    {
        return RT_TRUE;
    }

    first_len = length / 2;
    spi_loopback_fill_pattern(tx_buf, length, seed);
    rt_memset(rx_buf, 0, length);
    rt_memset(&msg1, 0, sizeof(msg1));
    rt_memset(&msg2, 0, sizeof(msg2));

    msg1.send_buf = tx_buf;
    msg1.recv_buf = rx_buf;
    msg1.length = first_len;
    msg1.cs_take = 1;
    msg1.cs_release = 0;
    msg1.next = &msg2;

    msg2.send_buf = tx_buf + first_len;
    msg2.recv_buf = rx_buf + first_len;
    msg2.length = length - first_len;
    msg2.cs_take = 0;
    msg2.cs_release = 1;
    msg2.next = RT_NULL;

    result = rt_spi_transfer_message(&spi_loopback_dev, &msg1);
    uassert_null(result);
    if (result != RT_NULL)
    {
        return RT_FALSE;
    }

    return spi_loopback_check_buffer(tx_buf, rx_buf, length, "message", clk_index, len_index);
}

static rt_bool_t spi_loopback_data_length_matrix(rt_size_t clk_index)
{
    rt_size_t i;
    rt_size_t tested = 0;
    rt_bool_t passed = RT_TRUE;

    for (i = 0; i < sizeof(spi_loopback_len_table) / sizeof(spi_loopback_len_table[0]); i++)
    {
        rt_size_t length = spi_loopback_len_table[i];

        if (length == 0)
        {
            continue;
        }

        if (!spi_loopback_check_length(length))
        {
            continue;
        }

        tested++;
        LOG_I("SPI loopback data matrix: clk[%u], len[%u] = %u bytes.",
              (unsigned int)clk_index, (unsigned int)i, (unsigned int)length);

        if (!spi_loopback_transfer_full_duplex(length, (rt_uint8_t)(0x35 + clk_index + i), clk_index, i))
        {
            passed = RT_FALSE;
            break;
        }

        if (!spi_loopback_transfer_message(length, (rt_uint8_t)(0x5A + clk_index + i), clk_index, i))
        {
            passed = RT_FALSE;
            break;
        }
    }

    uassert_true(tested > 0);
    return passed;
}

#ifdef RT_UTEST_SPI_LOOPBACK_API_SMOKE
static void spi_loopback_transfer_tx_only_smoke(rt_size_t length, rt_uint8_t seed)
{
    rt_ssize_t result;

    if (!spi_loopback_check_length(length))
    {
        return;
    }

    spi_loopback_fill_pattern(tx_buf, length, seed);

    result = rt_spi_transfer(&spi_loopback_dev, tx_buf, RT_NULL, length);
    uassert_int_equal(result, (rt_ssize_t)length);
}

static void spi_loopback_transfer_rx_only_smoke(rt_size_t length)
{
    rt_ssize_t result;

    if (!spi_loopback_check_length(length))
    {
        return;
    }

    rt_memset(rx_buf, 0, length);

    result = rt_spi_transfer(&spi_loopback_dev, RT_NULL, rx_buf, length);
    uassert_int_equal(result, (rt_ssize_t)length);
}

static void spi_loopback_api_smoke_length_matrix(rt_size_t clk_index)
{
    rt_size_t i;
    rt_size_t tested = 0;

    for (i = 0; i < sizeof(spi_loopback_len_table) / sizeof(spi_loopback_len_table[0]); i++)
    {
        rt_size_t length = spi_loopback_len_table[i];

        if (!spi_loopback_check_length(length))
        {
            continue;
        }

        tested++;
        LOG_I("SPI transfer API smoke: clk[%u], len[%u] = %u bytes, tx-only/rx-only.",
              (unsigned int)clk_index, (unsigned int)i, (unsigned int)length);

        spi_loopback_transfer_tx_only_smoke(length, (rt_uint8_t)(0xC3 + clk_index + i));
        spi_loopback_transfer_rx_only_smoke(length);
    }

    uassert_true(tested > 0);
}
#endif /* RT_UTEST_SPI_LOOPBACK_API_SMOKE */

static void spi_loopback_clock_matrix(void)
{
    rt_size_t i;
    rt_size_t tested = 0;

    spi_loopback_validate_length_table();

    for (i = 0; i < sizeof(spi_loopback_clk_table) / sizeof(spi_loopback_clk_table[0]); i++)
    {
        rt_err_t result;
        rt_uint32_t request_hz = spi_loopback_clk_table[i];
        rt_uint32_t actual_hz;

        if (request_hz == 0)
        {
            continue;
        }

        tested++;
        LOG_I("SPI loopback clock matrix[%u]: request %u Hz.", (unsigned int)i, request_hz);

        result = spi_loopback_configure(request_hz);
        uassert_int_equal(result, RT_EOK);
        if (result != RT_EOK)
        {
            continue;
        }

        actual_hz = spi_loopback_dev.config.usage_freq;
        if (actual_hz != 0)
        {
            LOG_I("SPI loopback clock matrix[%u]: actual %u Hz.", (unsigned int)i, actual_hz);
        }

        if (!spi_loopback_sendrecv8((rt_uint8_t)(0xA5 ^ i), i))
        {
            LOG_E("Skip longer transfers for clock[%u] because the byte loopback check failed.",
                  (unsigned int)i);
            continue;
        }

#ifdef RT_UTEST_SPI_LOOPBACK_API_SMOKE
        if (spi_loopback_data_length_matrix(i))
        {
            spi_loopback_api_smoke_length_matrix(i);
        }
#else
        (void)spi_loopback_data_length_matrix(i);
#endif
    }

    uassert_true(tested > 0);
}

static rt_err_t utest_tc_init(void)
{
    rt_device_t bus;

    LOG_I("SPI loopback test: connect MOSI and MISO on bus %s.", SPI_LOOPBACK_BUS_NAME);
    LOG_I("SPI loopback test: use the selected bus pinmux, not another SPI header.");
    LOG_I("SPI loopback test: max clock %u Hz, max data %u bytes.",
          (unsigned int)SPI_LOOPBACK_MAX_HZ, (unsigned int)SPI_LOOPBACK_DATA_SIZE);

    bus = rt_device_find(SPI_LOOPBACK_BUS_NAME);
    if (bus == RT_NULL || bus->type != RT_Device_Class_SPIBUS)
    {
        LOG_E("SPI bus %s not found.", SPI_LOOPBACK_BUS_NAME);
        return -RT_ERROR;
    }

    rt_memset(&spi_loopback_dev, 0, sizeof(spi_loopback_dev));
    if (rt_spi_bus_attach_device(&spi_loopback_dev, SPI_LOOPBACK_DEV_NAME, SPI_LOOPBACK_BUS_NAME, RT_NULL) != RT_EOK)
    {
        LOG_E("Attach SPI loopback device %s failed.", SPI_LOOPBACK_DEV_NAME);
        return -RT_ERROR;
    }
    spi_loopback_attached = RT_TRUE;

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    if (spi_loopback_attached)
    {
        rt_spi_bus_detach_device(&spi_loopback_dev);
        spi_loopback_attached = RT_FALSE;
    }

    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(spi_loopback_clock_matrix);
}

UTEST_TC_EXPORT(testcase, "components.drivers.spi.loopback", utest_tc_init, utest_tc_cleanup, SPI_LOOPBACK_TIMEOUT);

#endif /* RT_UTEST_SPI_LOOPBACK */
