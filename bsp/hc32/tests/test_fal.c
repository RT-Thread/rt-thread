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
 * 程序清单： FAL使用例程
 * 例程导出了 fal_sample 命令到控制终端
 * 命令调用格式：fal_sample
 * 1）配置RTT工程
 *     menuconfig:
 *     RT-Thread Components  --->  FAL: flash abstraction layer
 *                           --->  Device Drivers  --->  Using SPI Bus/Device device drivers  --->  Using Serial Flash Universal Driver
 *     Hardware Drivers Config  --->  Onboard Peripheral Drivers  ---->  Enable on-chip FLASH
*/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_FAL) && defined(BSP_USING_ON_CHIP_FLASH)

#include "board.h"
#include <fal.h>

#define FAL_PART_NAME                   "app"
#define TEST_BUF_SIZE                   1024UL
#define TEST_RW_CNT                     32UL
#define TEST_RW_START_ADDR              HC32_FLASH_END_ADDRESS - (TEST_BUF_SIZE * TEST_RW_CNT)


static uint8_t write_buffer[TEST_BUF_SIZE] = {0};
static uint8_t read_buffer[TEST_BUF_SIZE] = {0};


static int fal_sample(int argc, char **argv)
{
    const struct fal_partition *param;
    int ret;
    uint32_t Address;
    uint8_t errFlag = 0;

    fal_init();     //抽象层初始化
    /* Set write buffer, clear read buffer */
    for (uint32_t index = 0; index < TEST_BUF_SIZE; index++)
    {
        write_buffer[index] = index;
    }
    param = fal_partition_find(FAL_PART_NAME);
    if (param == RT_NULL)
    {
        rt_kprintf("not find partition app!\r\n");
        return -1;
    }
    for (int j = 0; j < TEST_RW_CNT; j++)
    {
        errFlag = 0;
        Address = TEST_RW_START_ADDR + j * TEST_BUF_SIZE;
        rt_kprintf("........test %d address 0x%08x........\r\n", j + 1, Address);
        /* erase process */

        if (j == 31)
        {
            rt_kprintf(".......");
        }

        ret = fal_partition_erase(param, Address, TEST_BUF_SIZE);
        if (ret >= 0)
        {
            rt_kprintf("Erase succeeded!\r\n");
        }
        else
        {
            rt_kprintf("Erase failed!\r\n");
            return ret;
        }
        /* write process */
        ret = fal_partition_write(param, Address, write_buffer, TEST_BUF_SIZE);
        if (ret >= 0)
        {
            rt_kprintf("Write succeeded!\r\n");
        }
        else
        {
            rt_kprintf("Write failed!\r\n");
            return ret;
        }
        /* read process */
        for (uint32_t index = 0; index < TEST_BUF_SIZE; index++)
        {
            read_buffer[index] = 0;
        }
        ret = fal_partition_read(param, Address, read_buffer, TEST_BUF_SIZE);
        if (ret >= 0)
        {
            rt_kprintf("Read succeeded!\r\n");
        }
        else
        {
            rt_kprintf("Read failed!\r\n");
            return ret;
        }
        /* compare process */
        for (int i = 0; i < TEST_BUF_SIZE; i++)
        {
#if defined(HC32F460)
            if ((j == (TEST_RW_CNT - 1)) && (i >= (TEST_BUF_SIZE - 32)) ?
                    (read_buffer[i] != 0xFF) : (read_buffer[i] != write_buffer[i]))
#else
            if (read_buffer[i] != write_buffer[i])
#endif
            {
                rt_kprintf("Data verification failed:\r\n");
                rt_kprintf("NUM: %d  Write: %x Read: %x \r\n", i, write_buffer[i], read_buffer[i]);
                errFlag = 1;
                ret = -1;
            }
        }
        if (0 == errFlag)
        {
            rt_kprintf("Data verification OK!\r\n");
        }
    }

    return ret;
}

/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(fal_sample, fal sample);

#endif
