/*
 * Copyright (c) 2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-09     [Your Name]  First version for Renesas RA series OSPI flash
 */

#include <rtthread.h>
#include "hal_data.h"
#include "ospi_b_ep.h"

#ifdef BSP_USING_OSPI_FLASH
#include "fal.h"

#define LOG_TAG                "drv.ospi_flash"
#include <drv_log.h>

/* Flash device configuration */
#define RENESAS_FLASH_START_ADDRESS    OSPI_B_CS1_START_ADDRESS
#define RENESAS_FLASH_SIZE             (64 * 1024 * 1024) /* 64MB for W35T51NW flash */
#define RENESAS_FLASH_SECTOR_SIZE      OSPI_B_SECTOR_SIZE_4K /* 4KB sectors */
#define RENESAS_FLASH_END_ADDRESS      (RENESAS_FLASH_START_ADDRESS + RENESAS_FLASH_SIZE)

/**
 * @brief Read data from OSPI flash in XIP mode.
 * @note This operation reads data directly from the memory-mapped address.
 *
 * @param offset Offset from the flash start address
 * @param buf Buffer to store read data
 * @param size Number of bytes to read
 *
 * @return Number of bytes read, or negative error code
 */
static int renesas_flash_read(long offset, rt_uint8_t *buf, rt_uint32_t size)
{
    rt_uint32_t addr = RENESAS_FLASH_START_ADDRESS + offset;

    if ((addr + size) > RENESAS_FLASH_END_ADDRESS)
    {
        LOG_E("read outrange flash size! addr is (0x%p)", (void *)(addr + size));
        return -RT_EINVAL;
    }

#if defined(__DCACHE_PRESENT)
    // Invalidate cache for the read region to ensure data consistency
    SCB_InvalidateDCache_by_Addr((uint32_t *)addr, size);
#endif
    /* Directly read from memory-mapped address in XIP mode */
    rt_memcpy(buf, (void *)addr, size);

    return (int)size;
}

/**
 * @brief Write data to OSPI flash using low-level API.
 *
 * @param offset Offset from the flash start address
 * @param buf The write data buffer
 * @param size Number of bytes to write
 *
 * @return Number of bytes written, or negative error code
 */
static int renesas_flash_write(long offset, const rt_uint8_t *buf, rt_uint32_t size)
{
    fsp_err_t err;
    rt_uint32_t addr = RENESAS_FLASH_START_ADDRESS + offset;
    rt_uint32_t remaining = size;
    rt_uint8_t *p_buf = (rt_uint8_t *)buf;
    const rt_uint32_t chunk_size = 4; // Fixed 4-byte write size

    // Input validation
    if (!buf || size == 0)
    {
        LOG_E("Invalid input: buf=%p, size=%u", buf, size);
        return -RT_EINVAL;
    }

    if ((addr + size) > RENESAS_FLASH_END_ADDRESS)
    {
        LOG_E("Write out of range: addr=0x%08x, size=%u", addr, size);
        return -RT_EINVAL;
    }

    // Write data in 4-byte chunks
    while (remaining > 0)
    {
        // Calculate current chunk size (up to 4 bytes or remaining bytes)
        rt_uint32_t current_size = (remaining >= chunk_size) ? chunk_size : remaining;

        // Perform write operation
        err = R_OSPI_B_Write(&g_ospi_b_ctrl, p_buf, (uint8_t *)addr, current_size);
        if (err != FSP_SUCCESS)
        {
            LOG_E("OSPI write failed: addr=0x%08x, size=%u, error=%d", addr, current_size, err);
            return -RT_ERROR;
        }

#if defined(__DCACHE_PRESENT)
        // Clean and invalidate cache for the written region
        SCB_CleanInvalidateDCache_by_Addr((uint32_t *)addr, current_size);
#endif

        // Wait for write operation to complete
        err = ospi_b_wait_operation(OSPI_B_TIME_WRITE);
        if (err != FSP_SUCCESS)
        {
            LOG_E("OSPI wait failed: addr=0x%08x, error=%d", addr, err);
            return -RT_ERROR;
        }

        // Update address, buffer pointer, and remaining bytes
        addr += current_size;
        p_buf += current_size;
        remaining -= current_size;
    }

    return (int)size;
}

/**
 * @brief Erase data on OSPI flash using low-level API.
 * @note Erases in 4KB sectors, using OSPI_B_APP_ADDRESS for sector alignment.
 *
 * @param offset Offset from the flash start address
 * @param size Number of bytes to erase
 *
 * @return Number of bytes erased, or negative error code
 */
static int renesas_flash_erase(long offset, rt_uint32_t size)
{
    fsp_err_t err;
    rt_uint32_t addr = RENESAS_FLASH_START_ADDRESS + offset;
    rt_uint32_t end_addr = addr + size;
    rt_uint32_t sector_count;
    rt_uint32_t sector_no;

    if (end_addr > RENESAS_FLASH_END_ADDRESS)
    {
        LOG_E("erase outrange flash size! addr is (0x%p)", (void *)end_addr);
        return -RT_EINVAL;
    }

    /* Calculate starting sector and number of sectors to erase */
    sector_no = offset / RENESAS_FLASH_SECTOR_SIZE;
    sector_count = (size + RENESAS_FLASH_SECTOR_SIZE - 1) / RENESAS_FLASH_SECTOR_SIZE; /* Ceiling division */

    for (rt_uint32_t i = 0; i < sector_count; i++)
    {
        rt_uint32_t sector_addr = (rt_uint32_t)OSPI_B_APP_ADDRESS(sector_no + i);

        /* Perform sector erase */
        err = R_OSPI_B_Erase(&g_ospi_b_ctrl, (uint8_t *)sector_addr, RENESAS_FLASH_SECTOR_SIZE);
        if (err != FSP_SUCCESS)
        {
            LOG_E("OSPI erase failed at addr 0x%08x, error code: %d", sector_addr, err);
            return -RT_ERROR;
        }

        /* Wait for erase completion */
        err = ospi_b_wait_operation(OSPI_B_TIME_ERASE_4K);
        if (err != FSP_SUCCESS)
        {
            LOG_E("OSPI wait operation failed for sector %d, error code: %d", sector_no + i, err);
            return -RT_ERROR;
        }
    }

    return (int)size;
}

/**
 * @brief Initialize the OSPI flash driver for FAL.
 * @note This function should be called during system initialization.
 *
 * @return RT_EOK on success, or negative error code
 */
int _flash_init(void)
{
    fsp_err_t err;
    uint32_t flash_id = 0;

    /* Initialize OSPI module and flash device */
    err = ospi_b_init();
    if (err != FSP_SUCCESS)
    {
        LOG_E("OSPI initialization failed, error code: %d", err);
        return -RT_ERROR;
    }

    err = ospi_b_set_protocol_to_opi();
    if (err != FSP_SUCCESS)
    {
        LOG_E("ospi_b_set_protocol_to_opi API FAILED: %d", err);
        return -RT_ERROR;
    }

    err = ospi_b_read_device_id(&flash_id);
    if (err != FSP_SUCCESS)
    {
        LOG_E("ospi_b_read_device_id FAILED: %d", err);
        return -RT_ERROR;
    }

    LOG_I("Get flash id: 0x%08x", flash_id);

    LOG_I("OSPI flash initialized successfully");

    return RT_EOK;
}

/* FAL flash device table */
const struct fal_flash_dev _ospi_flash =
{
    .name = "ospi_flash",
    .addr = RENESAS_FLASH_START_ADDRESS,
    .len = RENESAS_FLASH_SIZE,
    .blk_size = RENESAS_FLASH_SECTOR_SIZE,
    .ops = {
        .init = _flash_init, /* Initialization handled by ospi_b_init in main application */
        .read = renesas_flash_read,
        .write = renesas_flash_write,
        .erase = renesas_flash_erase
    }
};

#endif /* BSP_USING_OSPI_FLASH */
