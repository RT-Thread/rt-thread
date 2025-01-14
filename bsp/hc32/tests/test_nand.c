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
 * 程序清单：NAND 设备使用例程，例程导出了nand_sample命令到控制终端
 * 命令调用格式：nand_sample
 * 程序功能：对整个Nand存储空间进行擦除、写和读操作，比较数据是否一致
 *
 * 注意: 修改函数SystemClock_Config，调用函数CLK_SetClockDiv参数，
 *     CLK_EXCLK_DIV2改为CLK_EXCLK_DIV4;
 *
 * menuconfig:
 *     Hardware Drivers Config  --->  On-chip Peripheral Drivers  ---->  Enable EXMC  ---->  Using SDRAM or NAND  ---->  Using NAND (MT29F2G08AB)
 */

#include <stdlib.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#if defined(BSP_USING_EXMC) && defined(BSP_USING_NAND)
#include "nand_port.h"

#define NAND_DEVICE_NAME             "nand"

static rt_err_t nand_read_id(struct rt_mtd_nand_device *mtd_nand)
{
    if (mtd_nand == RT_NULL)
    {
        rt_kprintf("mtd_nand pointer = NULL!\n");
        return -RT_ERROR;
    }

    return rt_mtd_nand_read_id(mtd_nand);
}

static rt_err_t nand_read(struct rt_mtd_nand_device *mtd_nand, int block, rt_off_t page, rt_uint8_t *data)
{
    rt_err_t result;

    if ((mtd_nand == RT_NULL) || (block >= mtd_nand->block_total) || (data == RT_NULL))
    {
        rt_kprintf("%s: parameters invallid!\n", __func__);
        return -RT_ERROR;
    }

    /* calculate the page number */
    page = block * mtd_nand->pages_per_block + page;
    result = rt_mtd_nand_read(mtd_nand, page, data, mtd_nand->page_size, RT_NULL, mtd_nand->oob_size);

    return result;
}

static rt_err_t nand_read_oob_free(struct rt_mtd_nand_device *mtd_nand, int block, rt_off_t page, rt_uint8_t *oob_free_data)
{
    rt_err_t result;

    if ((mtd_nand == RT_NULL) || (block >= mtd_nand->block_total) || (oob_free_data == RT_NULL))
    {
        rt_kprintf("%s: parameters invallid!\n", __func__);
        return -RT_ERROR;
    }

    /* calculate the page number */
    page = block * mtd_nand->pages_per_block + page;
    result = rt_mtd_nand_read(mtd_nand, page, RT_NULL, 0UL, oob_free_data, mtd_nand->oob_free);

    return result;
}

static rt_err_t nand_write(struct rt_mtd_nand_device *mtd_nand, int block, rt_off_t page,
                           rt_uint8_t *data, rt_uint8_t *oob_free_data)
{
    rt_err_t result;

    if ((mtd_nand == RT_NULL) || (block >= mtd_nand->block_total) || ((data == RT_NULL) && (oob_free_data == RT_NULL)))
    {
        rt_kprintf("%s: parameters invallid!\n", __func__);
        return -RT_ERROR;
    }


    /* calculate the page number */
    page = block * mtd_nand->pages_per_block + page;
    result = rt_mtd_nand_write(mtd_nand, page, data, mtd_nand->page_size, oob_free_data, mtd_nand->oob_free);
    if (result != RT_MTD_EOK)
    {
        rt_kprintf("write page failed!, rc=%d\n", result);
    }

    return result;
}

static rt_err_t nand_erase(struct rt_mtd_nand_device *mtd_nand, int block)
{
    if ((mtd_nand == RT_NULL) || (block >= mtd_nand->block_total))
    {
        rt_kprintf("%s: parameters invallid!\n", __func__);
        return -RT_ERROR;
    }

    return rt_mtd_nand_erase_block(mtd_nand, block);
}

static void nand_thread_entry(void *parameter)
{
    rt_err_t result;
    rt_uint32_t i;
    rt_uint32_t block = 0UL;
    rt_uint32_t page = 0UL;
    rt_uint32_t err_count = 0UL;

    rt_uint8_t *page_rbuf;
    rt_uint8_t *page_wbuf;
    rt_uint8_t *page_oob_free_wbuf;
    rt_uint8_t *page_oob_free_rbuf;
    struct rt_mtd_nand_device *mtd_nand;

    mtd_nand = RT_MTD_NAND_DEVICE(rt_device_find(NAND_DEVICE_NAME));
    if (mtd_nand == RT_NULL)
    {
        rt_kprintf("no nand device found!\n");
        return;
    }

    /* read UID */
    if (nand_read_id(mtd_nand) != RT_EOK)
    {
        rt_kprintf("fail nand_read_id!\n");
        return;
    }

    /*  memory buffer */
    page_rbuf = rt_malloc(mtd_nand->page_size);
    if (page_rbuf == RT_NULL)
    {
        rt_kprintf("out of memory!");
        return;
    }

    page_wbuf = rt_malloc(mtd_nand->page_size);
    if (page_wbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        rt_kprintf("out of memory!");
        return;
    }

    page_oob_free_rbuf = rt_malloc(mtd_nand->oob_free);
    if (page_oob_free_rbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        rt_free(page_wbuf);
        rt_kprintf("out of memory!");
        return;
    }

    page_oob_free_wbuf = rt_malloc(mtd_nand->oob_free);
    if (page_oob_free_wbuf == RT_NULL)
    {
        rt_free(page_rbuf);
        rt_free(page_wbuf);
        rt_free(page_oob_free_rbuf);
        rt_kprintf("out of memory!");
        return;
    }

    while (1)
    {
        for (block = 0UL; block < mtd_nand->block_total; block++)
        {
            for (i = 0UL; i < mtd_nand->page_size; i++)
            {
                page_rbuf[i] = 0U;
                page_wbuf[i] = (rt_uint8_t)rand();
            }

            for (i = 0UL; i < mtd_nand->oob_free; i++)
            {
                page_oob_free_rbuf[i] = 0;
                page_oob_free_wbuf[i] = (rt_uint8_t)rand();
            }

            result = nand_erase(mtd_nand, block);
            if (result == RT_EOK)
            {
                rt_kprintf("mtd_nand_erase block=0x%08X: ok !\r\n", block);
            }
            else
            {
                err_count++;
                rt_kprintf("mtd_nand_erase block=0x%08X: error !\r\n", block);
            }

            for (page = 0UL; page < mtd_nand->pages_per_block; page++)
            {
                rt_thread_mdelay(500);

                result = nand_write(mtd_nand, block, page, page_wbuf, page_oob_free_wbuf);
                if (result == RT_EOK)
                {
                    rt_kprintf("nand_write block=0x%08X page=%d(include oob free area): ok !\r\n", block, page);
                }
                else
                {
                    err_count++;
                    rt_kprintf("nand_write block=0x%08X page=%d(include oob free area): error !\r\n", block, page);
                    break;
                }

                result = nand_read(mtd_nand, block, page, page_rbuf);
                if (result == RT_EOK)
                {
                    rt_kprintf("nand_read block=0x%08X page=%d: ok !\r\n", block, page);
                }
                else
                {
                    err_count++;
                    rt_kprintf("nand_read block=0x%08X page=%d: error !\r\n", block, page);
                    break;
                }

                if (rt_memcmp(page_rbuf, page_wbuf, mtd_nand->page_size) == 0)
                {
                    rt_kprintf("nand_write and nand_read block=0x%08X page=0x%d data consistency: ok !\r\n", block, page);
                }
                else
                {
                    err_count++;
                    rt_kprintf("nand_write and nand_read block=0x%08X page=0x%d data consistency: error !\r\n", block, page);
                    break;
                }

                result = nand_read_oob_free(mtd_nand, block, page, page_oob_free_rbuf);
                if (result == RT_EOK)
                {
                    rt_kprintf("nand_read_oob_free block=0x%08X page=%d: ok !\r\n", block, page);
                }
                else
                {
                    err_count++;
                    rt_kprintf("nand_read_oob_free block=0x%08X page=%d: error !\r\n", block, page);
                    break;
                }

                if (rt_memcmp(page_oob_free_rbuf, page_oob_free_wbuf, mtd_nand->oob_free) == 0)
                {
                    rt_kprintf("nand_write and nand_read_oob_free block=0x%08X page=0x%d data consistency: ok !\r\n", block, page);
                }
                else
                {
                    err_count++;
                    rt_kprintf("nand_write and nand_read_oob_free block=0x%08X page=0x%d data consistency: error !\r\n", block, page);
                    break;
                }

                rt_kprintf("mtd_nand block=0x%08X, page=%d test result: ok...... !\r\n", block, page);
            }
        }

        rt_kprintf("mtd_nand test result: %s  !\r\n", err_count ? "err" : "ok");
        rt_thread_mdelay(500);
    }
}

static void nand_sample(int argc, char *argv[])
{
    rt_thread_t thread = rt_thread_create("nand", nand_thread_entry, RT_NULL, 2048, 15, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
}
MSH_CMD_EXPORT(nand_sample, nand sample);

#endif
