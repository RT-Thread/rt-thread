/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author     Notes
 * 2026-08-13     nxp-ran    SPI3 send test for IMXRT1180 CM33 (moved from drv_spi.c)
 *
 * Usage:
 *   spi3_test
 *
 * The command sends 256 bytes (0x00..0xFF) once per call at 1 MHz, Mode 0.
 * Probe the following pins with a logic analyzer:
 *   SCK  -> GPIO_SD_B1_01
 *   MOSI -> GPIO_SD_B1_02
 *   CS   -> SPI3_TEST_CS_PIN (software-toggled GPIO, default GPIO4_IO28)
 *
 * Change SPI3_TEST_CS_PIN to any free GPIO on your board if needed.
 */

#include <rtthread.h>
#include <rtdevice.h>

#if defined(BSP_USING_SPI3) && defined(RT_USING_FINSH) && defined(SOC_IMXRT1180_SERIES)

#include <finsh.h>
#include "drv_gpio.h"
#include "drv_spi.h"

/* Use GPIO4_IO28 as software CS (adjacent to the LED on GPIO4_IO27). */
#define SPI3_TEST_CS_PIN   GET_PIN(4, 28)
#define SPI3_TEST_BUS      "spi3"
#define SPI3_TEST_DEVICE   "spi30"
#define SPI3_TEST_SPEED_HZ (1 * 1000 * 1000)

static struct rt_spi_device *_spi3_dev = RT_NULL;

static rt_err_t _spi3_ensure_open(void)
{
    if (_spi3_dev != RT_NULL)
        return RT_EOK;

    rt_err_t ret = rt_hw_spi_device_attach(SPI3_TEST_BUS, SPI3_TEST_DEVICE, SPI3_TEST_CS_PIN);
    if (ret != RT_EOK)
    {
        rt_kprintf("[spi3_test] attach failed: %d\n", ret);
        return ret;
    }

    _spi3_dev = (struct rt_spi_device *)rt_device_find(SPI3_TEST_DEVICE);
    if (_spi3_dev == RT_NULL)
    {
        rt_kprintf("[spi3_test] device not found\n");
        return -RT_ERROR;
    }

    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    cfg.max_hz = SPI3_TEST_SPEED_HZ;

    ret = rt_spi_configure(_spi3_dev, &cfg);
    if (ret != RT_EOK)
    {
        rt_kprintf("[spi3_test] configure failed: %d\n", ret);
        _spi3_dev = RT_NULL;
        return ret;
    }

    rt_kprintf("[spi3_test] SPI3 ready, CS=GPIO4_IO28, %d Hz, Mode0\n", SPI3_TEST_SPEED_HZ);
    return RT_EOK;
}

/* Buffers must be in DMA4-accessible SRAM (not CM33 DTCM/ITCM).
 * Declaring them static places them in .bss which the linker puts in OCRAM. */
static AT_NONCACHEABLE_SECTION(rt_uint8_t s_spi3_tx_buf[256]);
static AT_NONCACHEABLE_SECTION(rt_uint8_t s_spi3_rx_buf[256]);

static int spi3_test(int argc, char *argv[])
{
    rt_uint8_t *tx_buf = s_spi3_tx_buf;
    rt_uint8_t *rx_buf = s_spi3_rx_buf;
    int i;

    if (_spi3_ensure_open() != RT_EOK)
        return -1;

    for (i = 0; i < 256; i++)
        tx_buf[i] = (rt_uint8_t)i;
    rt_memset(rx_buf, 0, 256U);

    rt_kprintf("[spi3_test] sending 256 bytes (0x00..0xFF) at %d Hz...\n", SPI3_TEST_SPEED_HZ);

    rt_ssize_t len = rt_spi_transfer(_spi3_dev, tx_buf, rx_buf, 256U);

    if (len == (rt_ssize_t)256U)
    {
        rt_kprintf("[spi3_test] OK, %d bytes sent\n", (int)len);
    }
    else
    {
        rt_kprintf("[spi3_test] error, returned %d\n", (int)len);
        return -1;
    }

    rt_kprintf("[spi3_test] RX[0..15]:");
    for (i = 0; i < 16; i++)
        rt_kprintf(" %02X", rx_buf[i]);
    rt_kprintf("\n");

    return 0;
}
MSH_CMD_EXPORT(spi3_test, send 256 bytes via SPI3 for logic analyzer capture);

#endif /* BSP_USING_SPI3 && RT_USING_FINSH && SOC_IMXRT1180_SERIES */
