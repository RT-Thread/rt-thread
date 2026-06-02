/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-03     CoreBoxer    support IMXRT1180-EVK
 */

#include <rtthread.h>
#include <rthw.h>
#include <fal.h>

#include "drv_flexspi_nor_flash.h"

/*
 * Logging configuration
 */
#define LOG_TAG     "fal.flash"
#define LOG_LVL     LOG_LVL_INFO
#include <rtdbg.h>

/* FAL ops bridge */
#ifdef RT_USING_FAL

static int _fal_init(void)
{
    return rt_qspi_flash_init();
}

static int _fal_read(long offset, rt_uint8_t *buf, size_t size)
{
    return rt_qspi_flash_read((rt_uint32_t)offset, buf, size);
}

QSPI_RAM_CODE static int _fal_write(long offset, const rt_uint8_t *buf, size_t size)
{
    return rt_qspi_flash_write((rt_uint32_t)offset, buf, size);
}

QSPI_RAM_CODE static int _fal_erase(long offset, size_t size)
{
    return rt_qspi_flash_erase((rt_uint32_t)offset, size);
}

const struct fal_flash_dev imxrt1180_nor_flash =
{
    .name       = "norflash0",
    .addr       = QSPI_FLASH_BASE,
    .len        = QSPI_FLASH_SIZE,
    .blk_size   = QSPI_SECTOR_SIZE,
    .ops        = { _fal_init, _fal_read, _fal_write, _fal_erase },
    .write_gran = QSPI_PAGE_SIZE,
};

#endif /* RT_USING_FAL */
