/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-19     Rbbb666      first version
 * 2024-03-30     xhackerustc  2nd version for FRDM-MCXN947
 */

#include "board.h"

#include <drv_spi.h>

#define SPI_NAME     "spi60"
#define CS_PIN       (3*32+23)
static struct rt_spi_device *spi_dev;

/* attach spi device */
static int rt_spi_device_init(void)
{
    struct rt_spi_configuration cfg;

    rt_hw_spi_device_attach("spi6", SPI_NAME, CS_PIN);

    cfg.data_width = 8;
    cfg.mode   = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_NO_CS;
    cfg.max_hz = 1 *1000 *1000;

    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_NAME);

    if (RT_NULL == spi_dev)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_NAME);
        return -RT_ERROR;
    }

    rt_spi_configure(spi_dev, &cfg);

    return RT_EOK;
}
INIT_APP_EXPORT(rt_spi_device_init);

/* spi loopback mode test case */
static int spi_sample(int argc, char **argv)
{
    rt_uint8_t t_buf[32], r_buf[32];
    int i = 0;
    static struct rt_spi_message msg1;

    for (i = 0; i < sizeof(t_buf); i++)
    {
        t_buf[i] = i;
    }

    msg1.send_buf   = &t_buf;
    msg1.recv_buf   = &r_buf;
    msg1.length     = sizeof(t_buf);
    msg1.cs_take    = 1;
    msg1.cs_release = 1;
    msg1.next       = RT_NULL;

    rt_spi_transfer_message(spi_dev, &msg1);

    rt_kprintf("spi rbuf : ");
    for (i = 0; i < sizeof(r_buf); i++)
    {
        rt_kprintf("%x ", r_buf[i]);
    }

    rt_kprintf("\nspi loopback mode test over!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(spi_sample, spi loopback test);
