/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-03-09   hpmicro     First implementation
 * 2022-08-01   hpmicro     Fixed random crashing during kvdb_init
 * 2022-08-03   hpmicro     Improved erase speed
 * 2023-05-15   hpmicro     Disable global interrupt during FLASH operation for FLASH build
 *
 */
#include <rtthread.h>
#include <rthw.h>
#ifdef RT_USING_FAL
#include "fal.h"
#include "hpm_romapi.h"
#include "board.h"
#include "hpm_l1c_drv.h"

#if defined(FLASH_XIP) && (FLASH_XIP == 1)

static rt_base_t s_interrupt_level;
#define FAL_ENTER_CRITICAL() do {\
        rt_exit_critical();\
        fencei();\
        s_interrupt_level = rt_hw_interrupt_disable();\
    } while(0)

#define FAL_EXIT_CRITICAL() do {\
        ROM_API_TABLE_ROOT->xpi_driver_if->software_reset(BOARD_APP_XPI_NOR_XPI_BASE);\
        fencei();\
        rt_exit_critical();\
        rt_hw_interrupt_enable(s_interrupt_level);\
    } while(0)

#define FAL_RAMFUNC __attribute__((section(".isr_vector")))

#else
#define FAL_ENTER_CRITICAL() rt_enter_critical()

#define FAL_EXIT_CRITICAL() rt_exit_critical()

#define FAL_RAMFUNC

#endif

/***************************************************************************************************
 *      FAL Porting Guide
 *
 *      1. Most FLASH devices do not support RWW (Read-while-Write), the codes to access the FLASH
 *         must be placed at RAM or ROM code
 *      2. During FLASH erase/program, it is recommended to disable the interrupt, or place the
 *         interrupt related codes to RAM
 *
 ***************************************************************************************************/

static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

static xpi_nor_config_t s_flashcfg;

/**
 * @brief FAL Flash device context
 */
struct fal_flash_dev nor_flash0 =
    {
            .name = NOR_FLASH_DEV_NAME,
            /* If porting this code to the device with FLASH connected to XPI1, the address must be changed to 0x90000000 */
            .addr = NOR_FLASH_MEM_BASE,
            .len = 8 * 1024 * 1024,
            .blk_size = 4096,
            .ops = { .init = init, .read = read, .write = write, .erase = erase },
            .write_gran = 1
    };

/**
 * @brief FAL initialization
 *        This function probes the FLASH using the ROM API
 */
FAL_RAMFUNC static int init(void)
{
    int ret = RT_EOK;
    xpi_nor_config_option_t cfg_option;
    cfg_option.header.U = BOARD_APP_XPI_NOR_CFG_OPT_HDR;
    cfg_option.option0.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT0;
    cfg_option.option1.U = BOARD_APP_XPI_NOR_CFG_OPT_OPT1;

    FAL_ENTER_CRITICAL();
    hpm_stat_t status = rom_xpi_nor_auto_config(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, &cfg_option);
    FAL_EXIT_CRITICAL();
    if (status != status_success)
    {
        ret = -RT_ERROR;
    }
    else
    {
        /* update the flash chip information */
        rt_uint32_t sector_size;
        rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, xpi_nor_property_sector_size, &sector_size);
        rt_uint32_t flash_size;
        rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, xpi_nor_property_total_size, &flash_size);
        nor_flash0.blk_size = sector_size;
        nor_flash0.len = flash_size;
    }

    return ret;
}

/**
 * @brief FAL read function
 *        Read data from FLASH
 * @param offset FLASH offset
 * @param buf Buffer to hold data read by this API
 * @param size Size of data to be read
 * @return actual read bytes
 */
FAL_RAMFUNC static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t flash_addr = nor_flash0.addr + offset;
    rt_uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN(flash_addr);
    rt_uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP(flash_addr + size);
    rt_uint32_t aligned_size = aligned_end - aligned_start;
    rt_base_t level = rt_hw_interrupt_disable();
    l1c_dc_invalidate(aligned_start, aligned_size);
    rt_hw_interrupt_enable(level);

    (void) rt_memcpy(buf, (void*) flash_addr, size);

    return size;
}

/**
 * @brief Write unaligned data to the page
 * @param offset FLASH offset
 * @param buf Data buffer
 * @param size Size of data to be written
 * @return actual size of written data or error code
 */
FAL_RAMFUNC static int write_unaligned_page_data(long offset, const rt_uint32_t *buf, rt_size_t size)
{
    hpm_stat_t status;

    FAL_ENTER_CRITICAL();
    status = rom_xpi_nor_program(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_flashcfg, buf, offset, size);
    FAL_EXIT_CRITICAL();

    if (status != status_success)
    {
        return -RT_ERROR;
        rt_kprintf("write failed, status=%d\n", status);
    }

    return size;
}

/**
 * @brief FAL write function
 *        Write data to specified FLASH address
 * @param offset FLASH offset
 * @param buf Data buffer
 * @param size Size of data to be written
 * @return actual size of written data or error code
 */
FAL_RAMFUNC static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_uint32_t *src = NULL;
    rt_uint32_t buf_32[64];
    rt_uint32_t write_size;
    rt_size_t remaining_size = size;
    int ret = (int)size;

    rt_uint32_t page_size;
    rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, xpi_nor_property_page_size, &page_size);
    rt_uint32_t offset_in_page = offset % page_size;
    if (offset_in_page != 0)
    {
        rt_uint32_t write_size_in_page = page_size - offset_in_page;
        rt_uint32_t write_page_size = MIN(write_size_in_page, size);
        (void) rt_memcpy(buf_32, buf, write_page_size);
        write_size = write_unaligned_page_data(offset, buf_32, write_page_size);
        if (write_size < 0)
        {
            ret = -RT_ERROR;
            goto write_quit;
        }

        remaining_size -= write_page_size;
        offset += write_page_size;
        buf += write_page_size;
    }

    while (remaining_size > 0)
    {
        write_size = MIN(remaining_size, sizeof(buf_32));
        rt_memcpy(buf_32, buf, write_size);
        src = &buf_32[0];

        FAL_ENTER_CRITICAL();
        hpm_stat_t status = rom_xpi_nor_program(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_flashcfg, src,
                offset, write_size);
        FAL_EXIT_CRITICAL();

        if (status != status_success)
        {
            ret = -RT_ERROR;
            rt_kprintf("write failed, status=%d\n", status);
            break;
        }

        remaining_size -= write_size;
        buf += write_size;
        offset += write_size;
    }

write_quit:
    return ret;
}

/**
 * @brief FAL erase function
 *        Erase specified FLASH region
 * @param offset the start FLASH address to be erased
 * @param size size of the region to be erased
 * @ret RT_EOK Erase operation is successful
 * @retval -RT_ERROR Erase operation failed
 */
FAL_RAMFUNC static int erase(long offset, rt_size_t size)
{
    rt_uint32_t aligned_size = (size + nor_flash0.blk_size - 1U) & ~(nor_flash0.blk_size - 1U);
    hpm_stat_t status;
    int ret = (int)size;

    rt_uint32_t block_size;
    rt_uint32_t sector_size;
    (void) rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, xpi_nor_property_sector_size, &sector_size);
    (void) rom_xpi_nor_get_property(BOARD_APP_XPI_NOR_XPI_BASE, &s_flashcfg, xpi_nor_property_block_size, &block_size);
    rt_uint32_t erase_unit;
    while (aligned_size > 0)
    {
        FAL_ENTER_CRITICAL();
        if ((offset % block_size == 0) && (aligned_size >= block_size))
        {
            erase_unit = block_size;
            status = rom_xpi_nor_erase_block(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_flashcfg, offset);
        }
        else
        {
            erase_unit = sector_size;
            status = rom_xpi_nor_erase_sector(BOARD_APP_XPI_NOR_XPI_BASE, xpi_xfer_channel_auto, &s_flashcfg, offset);
        }
        FAL_EXIT_CRITICAL();

        if (status != status_success)
        {
            ret = -RT_ERROR;
            break;
        }
        offset += erase_unit;
        aligned_size -= erase_unit;
    }

    return ret;
}
#endif /* RT_USING_FAL */
