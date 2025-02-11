/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：SDRAM 设备使用例程，例程导出了sdram_sample命令到控制终端
 * 命令调用格式：sdram_sample
 * 程序功能：以8/16/32bit方式分别对整个SDRAM存储空间进行写和读操作，比较数据是否一致
 *
 * 注意: 修改函数SystemClock_Config，调用函数CLK_SetClockDiv参数，
 *     CLK_EXCLK_DIV2改为CLK_EXCLK_DIV8(EXCLK: 30MHz);
 *
 * menuconfig:
 *     Hardware Drivers Config  --->  On-chip Peripheral Drivers  ---->  Enable EXMC  ---->  Using SDRAM or NAND  ---->  Using SDRAM (IS42S16400J7TLI)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#if defined(BSP_USING_EXMC) && defined(BSP_USING_SDRAM)
#include "sdram_port.h"

static rt_err_t sdram_8bit_test(void)
{
    rt_uint32_t i;
    rt_uint32_t start_time;
    rt_uint32_t time_cast;
    const char data_width = 1;
    rt_uint8_t data = 0;
    rt_err_t err = RT_EOK;

    rt_kprintf("\r\n************************* %s *************************\r\n", __func__);

    /* write data */
    rt_kprintf("writing the 0x%08X bytes data, waiting....\r\n", SDRAM_SIZE);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint8_t)(i % 100);
    }
    time_cast = rt_tick_get() - start_time;
    rt_kprintf("write data success, total time: %d.%03dS.\r\n", time_cast / RT_TICK_PER_SECOND,
               time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    rt_kprintf("start reading and verifying data, waiting....\r\n");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        data = *(__IO uint8_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 100)
        {
            err = -RT_ERROR;
            rt_kprintf("SDRAM test failed!\r\n");
            break;
        }
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        rt_kprintf("SDRAM test success!\r\n");
    }

    return err;
}

static rt_err_t sdram_16bit_test(void)
{
    rt_uint32_t i;
    rt_uint32_t start_time;
    rt_uint32_t time_cast;
    const char data_width = 2;
    rt_uint16_t data = 0;
    rt_err_t err = RT_EOK;

    rt_kprintf("\r\n************************* %s *************************\r\n", __func__);

    /* write data */
    rt_kprintf("writing the 0x%08X haflword data, waiting....\r\n", SDRAM_SIZE / data_width);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint16_t)(i % 1000);
    }
    time_cast = rt_tick_get() - start_time;
    rt_kprintf("write data success, total time: %d.%03dS.\r\n", time_cast / RT_TICK_PER_SECOND,
               time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    rt_kprintf("start reading and verifying data, waiting....\r\n");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        data = *(__IO uint16_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 1000)
        {
            err = -RT_ERROR;
            rt_kprintf("SDRAM test failed!\r\n");
            break;
        }
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        rt_kprintf("SDRAM test success!\r\n");
    }

    return err;
}

static rt_err_t sdram_32bit_test(void)
{
    rt_uint32_t i;
    rt_uint32_t start_time;
    rt_uint32_t time_cast;
    const char data_width = 4;
    rt_uint32_t data = 0;
    rt_err_t err = RT_EOK;

    rt_kprintf("\r\n************************* %s *************************\r\n", __func__);

    /* write data */
    rt_kprintf("writing the 0x%08X bytes data, waiting....\r\n", SDRAM_SIZE / data_width);
    start_time = rt_tick_get();
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width) = (uint32_t)(i % 10000);
    }
    time_cast = rt_tick_get() - start_time;
    rt_kprintf("write data success, total time: %d.%03dS.\r\n", time_cast / RT_TICK_PER_SECOND,
               time_cast % RT_TICK_PER_SECOND / ((RT_TICK_PER_SECOND * 1 + 999) / 1000));

    /* read data */
    rt_kprintf("start reading and verifying data, waiting....\r\n");
    for (i = 0; i < SDRAM_SIZE / data_width; i++)
    {
        data = *(__IO uint32_t *)(SDRAM_BANK_ADDR + i * data_width);
        if (data != i % 10000)
        {
            err = -RT_ERROR;
            rt_kprintf("SDRAM test failed!\r\n");
            break;
        }
    }

    if (i >= SDRAM_SIZE / data_width)
    {
        rt_kprintf("SDRAM test success!\r\n");
    }

    return err;
}

static void sdram_thread_entry(void *parameter)
{
    while (1)
    {
        sdram_8bit_test();
        rt_thread_mdelay(1000);

        sdram_16bit_test();
        rt_thread_mdelay(1000);

        sdram_32bit_test();
        rt_thread_mdelay(1000);
    }
}

static void sdram_sample(int argc, char *argv[])
{
    rt_thread_t thread = rt_thread_create("sdram", sdram_thread_entry, RT_NULL, 2048, 15, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}
MSH_CMD_EXPORT(sdram_sample, sdram sample);

#endif
