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
 * 程序清单：SD/MMC卡 设备使用例程
 * 例程导出了 sample_sdmmc 命令到控制终端
 * 命令调用格式：sdmmc_sample
 * 程序功能：对整个SD/MMC卡进行写和读操作，比较数据是否一致
 *
 * 注意: 修改函数SystemClock_Config下面参数，
 *     stcPLLHInit.PLLCFGR_f.PLLN = 120UL - 1UL;
 *                    改为
 *     stcPLLHInit.PLLCFGR_f.PLLN = 100UL - 1UL;
 */

#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#if defined(BSP_USING_SDIO)

#define SDMMC_DEVICE_NAME               "sd"
#define SDMMC_SECTOR_SIZE               512UL

#define SDMMC_TEST_SECTORS_PER_TIME     100UL
#define SDMMC_TEST_TIME                 10UL

#define SDMMC_TEST_SECTORS              (SDMMC_TEST_TIME * SDMMC_TEST_SECTORS_PER_TIME)
#define SDMMC_TEST_BUF_SIZE             (SDMMC_SECTOR_SIZE * SDMMC_TEST_SECTORS_PER_TIME)

static void sdmmc_thread_entry(void *parameter)
{
    rt_ssize_t size;
    rt_uint32_t err_count = 0;
    rt_device_t sd_device;
    rt_uint32_t sector_start;
    rt_uint32_t sector_end;;
    rt_uint32_t sector_cur_start;
    rt_uint32_t sector_cur_end;
    rt_uint8_t *sector_rbuf;
    rt_uint8_t *sector_wbuf;

    sd_device = rt_device_find(SDMMC_DEVICE_NAME);
    if (sd_device == RT_NULL)
    {
        rt_kprintf("no nand device found!\n");
        return;
    }

    if (rt_device_open(sd_device, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("fail to open!\n");
        return;
    }

    sector_rbuf = rt_malloc(SDMMC_TEST_BUF_SIZE);
    if (sector_rbuf == RT_NULL)
    {
        rt_kprintf("out of memory!");
        return;
    }

    sector_wbuf = rt_malloc(SDMMC_TEST_BUF_SIZE);
    if (sector_wbuf == RT_NULL)
    {
        rt_free(sector_rbuf);
        rt_kprintf("out of memory!");
        return;
    }

    sector_start = ((rt_uint32_t)rand() & 0x00000FFFUL);
    sector_end = (sector_start + SDMMC_TEST_SECTORS - 1);

    rt_kprintf("sector=[%d, %d]: ......test start...... !\r\n", sector_start, sector_end);

    for (sector_cur_start = sector_start; sector_cur_start <= sector_end; sector_cur_start += SDMMC_TEST_SECTORS_PER_TIME)
    {
        sector_cur_end = sector_cur_start + SDMMC_TEST_SECTORS_PER_TIME - 1UL;

        /* initialize buffer data */
        rt_memset(sector_rbuf, 0, SDMMC_TEST_BUF_SIZE);
        rt_memset(sector_wbuf, (rt_uint8_t)rand(), SDMMC_TEST_BUF_SIZE);

        /* write sdmmc */
        size = rt_device_write(sd_device, sector_cur_start, sector_wbuf, SDMMC_TEST_SECTORS_PER_TIME);
        if (size == SDMMC_TEST_SECTORS_PER_TIME)
        {
            rt_kprintf("sector=[%d, %d]: ok wr !\r\n", sector_cur_start, sector_cur_end);
        }
        else
        {
            err_count++;
            rt_kprintf("sector=[%d, %d]: error wr !\r\n", sector_cur_start, sector_cur_end);
            continue;
        }

        /* read sdmmc */
        size = rt_device_read(sd_device, sector_cur_start, sector_rbuf, SDMMC_TEST_SECTORS_PER_TIME);
        if (size == SDMMC_TEST_SECTORS_PER_TIME)
        {
            rt_kprintf("sector=[%d, %d]: ok rd !\r\n", sector_cur_start, sector_cur_end);
        }
        else
        {
            err_count++;
            rt_kprintf("sector=[%d, %d]: error rd !\r\n", sector_cur_start, sector_cur_end);
            continue;
        }

        /* compare data */
        if (rt_memcmp(sector_wbuf, sector_rbuf, SDMMC_TEST_BUF_SIZE) == 0)
        {
            rt_kprintf("sector=[%d, %d]: ok cmp  !\r\n", sector_cur_start, sector_cur_end);
        }
        else
        {
            err_count++;
            rt_kprintf("sector=[%d, %d]: error cmp  !\r\n", sector_cur_start, sector_cur_end);
        }
    }

    if (rt_device_close(sd_device) != RT_EOK)
    {
        rt_kprintf("fail to close!\n");
    }

    rt_free(sector_rbuf);
    rt_free(sector_wbuf);

    if (err_count == 0)
    {
        rt_kprintf("sector=[%d, %d]: ...... test ok...... !\r\n\r\n", sector_start, sector_end);

    }
    else
    {
        rt_kprintf("sector=[%d, %d]: ...... test error...... !\r\n\r\n", sector_start, sector_end);
    }
}

static void sdmmc_sample(int argc, char *argv[])
{
    rt_thread_t thread = rt_thread_create("sdmmc", sdmmc_thread_entry, RT_NULL, 2048, 15, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}
MSH_CMD_EXPORT(sdmmc_sample, sdmmc sample);

#endif