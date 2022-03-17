/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-30     flybreak     first version
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "hal_data.h"
#include "drv_flash.h"

#include <rtthread.h>

#if defined(RT_USING_FAL)
    #include "fal.h"
#endif

//#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */
#include <rtdbg.h>

int _flash_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open Flash_HP */
    err = R_FLASH_HP_Open(&g_flash_ctrl, &g_flash_cfg);
    /* Handle Error */
    if (FSP_SUCCESS != err)
    {
        LOG_E("\r\n Flah_HP_Open API failed");
    }
    /* Setup Default  Block 0 as Startup Setup Block */
    err = R_FLASH_HP_StartUpAreaSelect(&g_flash_ctrl, FLASH_STARTUP_AREA_BLOCK0, true);
    if (err != FSP_SUCCESS)
    {
        LOG_E("\r\n Flah_HP_StartUpAreaSelect API failed");
    }
    return 0;
}

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int _flash_read(rt_uint32_t addr, rt_uint8_t *buf, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

/**
 * Write data to flash.
 * @note This operation's units is word.
 * @note This operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int _flash_write(rt_uint32_t addr, const rt_uint8_t *buf, size_t size)
{
    rt_err_t result      = RT_EOK;
    rt_base_t level;
    fsp_err_t err = FSP_SUCCESS;
    size_t written_size = 0;

    if (size % BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE)
    {
        LOG_E("Flash Write size must be an integer multiple of %d", BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE);
        return -RT_EINVAL;
    }

    while (written_size < size)
    {
        level = rt_hw_interrupt_disable();
        R_FLASH_HP_Reset(&g_flash_ctrl);
        /* Write code flash data*/
        err = R_FLASH_HP_Write(&g_flash_ctrl, (uint32_t)(buf + written_size), addr + written_size, BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE);
        rt_hw_interrupt_enable(level);

        /* Error Handle */
        if (FSP_SUCCESS != err)
        {
            LOG_E("Write API failed");
            return -RT_EIO;
        }

        written_size += BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE;
    }

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int _flash_erase_8k(rt_uint32_t addr, size_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    rt_base_t level;

    if ((addr + size) > BSP_FEATURE_FLASH_HP_CF_REGION0_SIZE)
    {
        LOG_E("ERROR: erase outrange flash size! addr is (0x%p)\n", (void *)(addr + size));
        return -RT_EINVAL;
    }

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    R_FLASH_HP_Reset(&g_flash_ctrl);
    /* Erase Block */
    err = R_FLASH_HP_Erase(&g_flash_ctrl, RT_ALIGN_DOWN(addr, FLASH_HP_CF_BLOCK_SIZE_8KB), (size - 1) / BSP_FEATURE_FLASH_HP_CF_REGION0_BLOCK_SIZE + 1);
    rt_hw_interrupt_enable(level);

    if (err != FSP_SUCCESS)
    {
        LOG_E("Erase API failed");
        return -RT_EIO;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

int _flash_erase_32k(rt_uint32_t addr, size_t size)
{
    fsp_err_t err = FSP_SUCCESS;
    rt_base_t level;

    if (size < 1)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    R_FLASH_HP_Reset(&g_flash_ctrl);
    /* Erase Block */
    err = R_FLASH_HP_Erase(&g_flash_ctrl, RT_ALIGN_DOWN(addr, FLASH_HP_CF_BLOCK_SIZE_32KB), (size - 1) / BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE + 1);
    rt_hw_interrupt_enable(level);

    if (err != FSP_SUCCESS)
    {
        LOG_E("Erase API failed");
        return -RT_EIO;
    }

    LOG_D("erase done: addr (0x%p), size %d", (void *)addr, size);
    return size;
}

#if defined(RT_USING_FAL)

static int fal_flash_read_8k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_32k(long offset, rt_uint8_t *buf, size_t size);

static int fal_flash_write_8k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_32k(long offset, const rt_uint8_t *buf, size_t size);

static int fal_flash_erase_8k(long offset, size_t size);
static int fal_flash_erase_32k(long offset, size_t size);

const struct fal_flash_dev _onchip_flash_8k = { "onchip_flash_8k", FLASH_HP_CF_BLCOK_0, FLASH_HP_CF_BLOCK_8, (8 * 1024), {_flash_init, fal_flash_read_8k, fal_flash_write_8k, fal_flash_erase_8k} };
const struct fal_flash_dev _onchip_flash_32k = { "onchip_flash_32k", FLASH_HP_CF_BLOCK_8, 32 * 30 * 1024, (32 * 1024), {_flash_init, fal_flash_read_32k, fal_flash_write_32k, fal_flash_erase_32k} };

static int fal_flash_read_8k(long offset, rt_uint8_t *buf, size_t size)
{
    return _flash_read(_onchip_flash_8k.addr + offset, buf, size);
}

static int fal_flash_read_32k(long offset, rt_uint8_t *buf, size_t size)
{
    return _flash_read(_onchip_flash_32k.addr + offset, buf, size);
}

static int fal_flash_write_8k(long offset, const rt_uint8_t *buf, size_t size)
{
    return _flash_write(_onchip_flash_8k.addr + offset, buf, size);
}

static int fal_flash_write_32k(long offset, const rt_uint8_t *buf, size_t size)
{
    return _flash_write(_onchip_flash_32k.addr + offset, buf, size);
}

static int fal_flash_erase_8k(long offset, size_t size)
{
    return _flash_erase_8k(_onchip_flash_8k.addr + offset, size);
}

static int fal_flash_erase_32k(long offset, size_t size)
{
    return _flash_erase_32k(_onchip_flash_32k.addr + offset, size);
}

int flash_test(void)
{
#define TEST_OFF (_onchip_flash_32k.len - BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE)
    const struct fal_partition *param;
    uint8_t write_buffer[BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE] = {0};
    uint8_t read_buffer[BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE] = {0};

    /* Set write buffer, clear read buffer */
    for (uint8_t index = 0; index < BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE; index++)
    {
        write_buffer[index] = index;
        read_buffer[index] = 0;
    }

    fal_init();

    param = fal_partition_find("param");
    if (param == RT_NULL)
    {
        LOG_E("not find partition param!");
        return -1;
    }
    LOG_I("Erase Start...");
    fal_partition_erase(param, TEST_OFF, BSP_FEATURE_FLASH_HP_CF_REGION1_BLOCK_SIZE);
    LOG_I("Erase succeeded!");
    LOG_I("Write Start...");
    fal_partition_write(param, TEST_OFF, write_buffer, sizeof(write_buffer));
    LOG_I("Write succeeded!");
    LOG_I("Read Start...");
    fal_partition_read(param, TEST_OFF, read_buffer, BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE);
    LOG_I("Read succeeded!");

    for (int i = 0; i < BSP_FEATURE_FLASH_HP_CF_WRITE_SIZE; i++)
    {
        if (read_buffer[i] != write_buffer[i])
        {
            LOG_E("Data verification failed!");
            return -1;
        }
    }

    LOG_I("Data verification succeeded!");
    return 0;
}
MSH_CMD_EXPORT(flash_test, "drv flash test.");

#endif
