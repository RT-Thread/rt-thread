/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-19     Rbbb666      first version
 */

#include "board.h"

#if defined(BSP_USING_SPI3_SAMPLE)
#include <drv_spi.h>

#define SPI_NAME     "spi30"
static struct rt_spi_device *spi_dev = RT_NULL;

/* attach spi5 device */
static int rt_spi_device_init(void)
{
    struct rt_spi_configuration cfg;

    rt_hw_spi_device_attach("spi3", "spi30", NULL);

    cfg.data_width = 8;
    cfg.mode   = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB | RT_SPI_NO_CS;
    cfg.max_hz = 1 *1000 *1000;

    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_NAME);

    if (RT_NULL == spi_dev)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_NAME);
        return RT_ERROR;
    }

    rt_spi_configure(spi_dev, &cfg);

    return RT_EOK;
}
INIT_APP_EXPORT(rt_spi_device_init);

/* spi5 loopback mode test case */
static int spi_sample(int argc, char **argv)
{
    rt_uint8_t t_buf[8], r_buf[8];
    int i = 0;
    static struct rt_spi_message msg1;

    if (argc != 9)
    {
        rt_kprintf("Please Usage:\n");
        rt_kprintf("spi_sample 1 2 3 4 5 6 7 8\n");
        return -RT_ERROR;
    }

    for (i = 0; i < 8; i++)
    {
        t_buf[i] = atoi(argv[i+1]);
    }

    msg1.send_buf   = &t_buf;
    msg1.recv_buf   = &r_buf;
    msg1.length     = sizeof(t_buf);
    msg1.cs_take    = 1;
    msg1.cs_release = 0;
    msg1.next       = RT_NULL;

    rt_spi_transfer_message(spi_dev, &msg1);

    rt_kprintf("spi rbuf : ");
    for (i = 0; i < sizeof(t_buf); i++)
    {
        rt_kprintf("%x ", r_buf[i]);
    }

    rt_kprintf("\nspi loopback mode test over!\n");

    return RT_EOK;
}
MSH_CMD_EXPORT(spi_sample, spi loopback test);

#endif /* BSP_USING_SPI3 */
