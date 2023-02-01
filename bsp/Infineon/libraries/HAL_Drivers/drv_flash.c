/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-26     Rbb666       first version
 */

#include <rtthread.h>
#include "drv_common.h"

#ifdef BSP_USING_ON_CHIP_FLASH
#include "drv_flash.h"

#if defined(RT_USING_FAL)
    #include "fal.h"
#endif

#define DRV_DEBUG
#define LOG_TAG                "drv.flash"
#include <drv_log.h>

static cyhal_flash_t flash_obj;
static cyhal_flash_block_info_t block_info;
static cyhal_flash_info_t flash_info;

int _flash_init(void)
{
    cy_rslt_t err = CY_RSLT_SUCCESS;
    /* Init Flash */
    err = cyhal_flash_init(&flash_obj);

    /* Handle Error */
    if (CY_RSLT_SUCCESS != err)
    {
        LOG_E("\r\n Flash Init failed");
    }

    cyhal_flash_get_info(&flash_obj, &flash_info);

    block_info = flash_info.blocks[flash_info.block_count - 1u];

    return 0;
}

static rt_uint32_t get_page_32k(uint32_t addr)
{
    rt_uint32_t page = 0;

    page = RT_ALIGN_DOWN(addr, IFX_EFLASH_PAGE_SIZE);

    return page;
}

/**
  * @brief  gets the page of a given address
  * @param  addr: address of the flash memory
  * @retval the page of a given address
  */
static rt_uint32_t get_page_256k(uint32_t addr)
{
    rt_uint32_t page = 0;

    page = RT_ALIGN_DOWN(addr, IFX_FLASH_PAGE_SIZE);

    return page;
}

int ifx_flash_read_32k(rt_uint32_t addr, rt_uint8_t *buf, rt_uint32_t size)
{
    rt_uint32_t i;

    if ((addr + size) > IFX_EFLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

/**
 * @brief read data from flash.
 * @note this operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int ifx_flash_read_256k(rt_uint32_t addr, rt_uint8_t *buf, rt_uint32_t size)
{
    rt_uint32_t i;

    if ((addr + size) > IFX_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    for (i = 0; i < size; i++, buf++, addr++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

/**
 * @brief write data to flash.
 * @note this operation's units is word.
 * @note this operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int ifx_flash_write(rt_uint32_t addr, const rt_uint8_t *buf, rt_uint32_t size)
{
    rt_err_t result = RT_EOK;
    rt_base_t level;
    cy_rslt_t err = CY_RSLT_SUCCESS;
    size_t written_size = 0;

#define BSP_FEATURE_FLASH_WRITE_SIZE 512U

    if (size % BSP_FEATURE_FLASH_WRITE_SIZE)
    {
        LOG_E("Flash Write size must be an integer multiple of %d", BSP_FEATURE_FLASH_WRITE_SIZE);
        return -RT_EINVAL;
    }

    while (written_size < size)
    {
        level = rt_hw_interrupt_disable();
        /* Write code flash data*/
        err = cyhal_flash_write(&flash_obj, addr + written_size, (rt_uint32_t *)(buf + written_size));
        rt_hw_interrupt_enable(level);

        /* Error Handle */
        if (CY_RSLT_SUCCESS != err)
        {
            LOG_E("Write API failed");
            return -RT_EIO;
        }

        written_size += BSP_FEATURE_FLASH_WRITE_SIZE;
    }

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

int ifx_flash_erase_32k(rt_uint32_t addr, rt_uint32_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t page_addr = 0;
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if ((end_addr) > IFX_EFLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    while (addr < end_addr)
    {
        page_addr = get_page_32k(addr);

        if (cyhal_flash_erase(&flash_obj, page_addr) != CY_RSLT_SUCCESS)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        addr += IFX_FLASH_PAGE_SIZE;
    }

    rt_hw_interrupt_enable(level);

__exit:

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

/**
 * @brief erase data on flash .
 * @note this operation is irreversible.
 * @note this operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int ifx_flash_erase_256k(rt_uint32_t addr, rt_uint32_t size)
{
    rt_err_t result = RT_EOK;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t page_addr = 0;
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if ((end_addr) > IFX_FLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

    while (addr < end_addr)
    {
        page_addr = get_page_256k(addr);

        if (cyhal_flash_erase(&flash_obj, page_addr) != CY_RSLT_SUCCESS)
        {
            result = -RT_ERROR;
            goto __exit;
        }

        addr += IFX_FLASH_PAGE_SIZE;
    }

    rt_hw_interrupt_enable(level);

__exit:

    if (result != RT_EOK)
    {
        return result;
    }

    return size;
}

#if defined(RT_USING_FAL)
static int fal_flash_read_32k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_256k(long offset, rt_uint8_t *buf, size_t size);

static int fal_flash_write_32k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_256k(long offset, const rt_uint8_t *buf, size_t size);

static int fal_flash_erase_32k(long offset, size_t size);
static int fal_flash_erase_256k(long offset, size_t size);

const struct fal_flash_dev ifx_onchip_flash_32k =
{
    "onchip_flash_32k",
    IFX_EFLASH_START_ADRESS,
    IFX_EFLASH_SIZE,
    IFX_EFLASH_PAGE_SIZE,
    {
        NULL,
        fal_flash_read_32k,
        fal_flash_write_32k,
        fal_flash_erase_32k
    }
};

const struct fal_flash_dev ifx_onchip_flash_256k =
{
    "onchip_flash_256k",
    IFX_FLASH_START_ADRESS,
    IFX_FLASH_SIZE,
    IFX_FLASH_PAGE_SIZE,
    {
        _flash_init,
        fal_flash_read_256k,
        fal_flash_write_256k,
        fal_flash_erase_256k
    }
};

static int fal_flash_read_32k(long offset, rt_uint8_t *buf, size_t size)
{
    return ifx_flash_read_32k(ifx_onchip_flash_32k.addr + offset, buf, size);
}

static int fal_flash_read_256k(long offset, rt_uint8_t *buf, size_t size)
{
    return ifx_flash_read_256k(ifx_onchip_flash_256k.addr + offset, buf, size);
}

static int fal_flash_write_32k(long offset, const rt_uint8_t *buf, size_t size)
{
    return ifx_flash_write(ifx_onchip_flash_32k.addr + offset, buf, size);
}

static int fal_flash_write_256k(long offset, const rt_uint8_t *buf, size_t size)
{
    return ifx_flash_write(ifx_onchip_flash_256k.addr + offset, buf, size);
}

static int fal_flash_erase_32k(long offset, size_t size)
{
    return ifx_flash_erase_32k(ifx_onchip_flash_32k.addr + offset, size);
}

static int fal_flash_erase_256k(long offset, size_t size)
{
    return ifx_flash_erase_256k(ifx_onchip_flash_256k.addr + offset, size);
}

#if defined(BSP_USING_ON_CHIP_FLASH)
static int rt_hw_on_chip_flash_init(void)
{
    fal_init();
    return RT_EOK;
}
INIT_ENV_EXPORT(rt_hw_on_chip_flash_init);

int flash64k_test(void)
{
#define TEST_OFF (ifx_onchip_flash_256k.len - 0x40000)
    const struct fal_partition *param;
    uint8_t write_buffer[512U] = {0};
    uint8_t read_buffer[512U] = {0};

    /* Set write buffer, clear read buffer */
    for (uint16_t index = 0; index < 512U; index++)
    {
        write_buffer[index] = index;
        read_buffer[index] = 0;
    }

    param = fal_partition_find("app");

    if (param == RT_NULL)
    {
        LOG_E("not find partition app!");
        return -1;
    }

    LOG_I("Erase Start...");
    fal_partition_erase(param, TEST_OFF, 0x40000);
    LOG_I("Erase succeeded!");
    LOG_I("Write Start...");
    fal_partition_write(param, TEST_OFF, write_buffer, sizeof(write_buffer));
    LOG_I("Write succeeded!");
    LOG_I("Read Start...");
    fal_partition_read(param, TEST_OFF, read_buffer, 128U);
    LOG_I("Read succeeded!");

    for (int i = 0; i < 128U; i++)
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
MSH_CMD_EXPORT(flash64k_test, "drv flash64k test.");

int flash32k_test(void)
{
#define TEST32_OFF (ifx_onchip_flash_32k.len - 0x8000)
    const struct fal_partition *param;
    uint8_t write_buffer[512U] = {0};
    uint8_t read_buffer[512U] = {0};

    /* Set write buffer, clear read buffer */
    for (uint16_t index = 0; index < 512U; index++)
    {
        write_buffer[index] = index;
        read_buffer[index] = 0;
    }

    param = fal_partition_find("param");

    if (param == RT_NULL)
    {
        LOG_E("not find partition param!");
        return -1;
    }

    LOG_I("Erase Start...");
    fal_partition_erase(param, TEST32_OFF, 0x8000);
    LOG_I("Erase succeeded!");
    LOG_I("Write Start...");
    fal_partition_write(param, TEST32_OFF, write_buffer, sizeof(write_buffer));
    LOG_I("Write succeeded!");
    LOG_I("Read Start...");
    fal_partition_read(param, TEST32_OFF, read_buffer, 128U);
    LOG_I("Read succeeded!");

    for (int i = 0; i < 128U; i++)
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
MSH_CMD_EXPORT(flash32k_test, "drv flash32k test.");
#endif
#endif
#endif /* BSP_USING_ON_CHIP_FLASH */
