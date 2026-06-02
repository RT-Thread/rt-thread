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

#include "drv_flexspi_nor_flash.h"
#include "drv_flexspi.h"
#include "flexspi_port.h"
#include "fsl_flexspi.h"
#include "fsl_cache.h"

/*
 * Logging configuration
 */
#define LOG_TAG     "drv.flash"
#define LOG_LVL     LOG_LVL_INFO
#include <rtdbg.h>

/*
 * FLASH_BUSY_STATUS_POL    = 1  : SR[bit] = 1 means busy
 * FLASH_BUSY_STATUS_OFFSET = 0  : WIP bit is SR[0]
 * FLASH_QUAD_ENABLE        = 0x40 : write to SR to enable Quad mode
 */
#define FLASH_QUAD_ENABLE_VAL       0x40U

/* WIP polling upper limit to prevent infinite loop on Flash failure */
#define WIP_TIMEOUT_COUNT           2000000UL

/*
 * Internal write buffer (must reside in SRAM)
 *
 * Reason: src data may come from const sections in XIP Flash.
 * During FLEXSPI IP write commands, AHB access is suspended.
 * If CPU tries to read src via AHB at that moment, bus hang or
 * corrupted data may occur. Pre-copying to SRAM avoids this.
 */
static uint8_t SDK_ALIGN(s_write_buf[QSPI_PAGE_SIZE], 4);

/* Internal state */
static imxrt_flexspi_handle_t  *s_handle  = RT_NULL;
static struct rt_mutex          s_mutex;
static int                      s_inited  = 0;

/*
 * _range_valid - check whether [offset, offset+size) is within Flash
 */
rt_inline int _range_valid(rt_uint32_t offset, rt_size_t size)
{
    if (size == 0U)
    {
        return 1;
    }
    if ((offset + (rt_uint32_t)size) < offset)
    {
        return 0; /* overflow */
    }
    if ((offset + (rt_uint32_t)size) > QSPI_FLASH_SIZE)
    {
        return 0;
    }
    return 1;
}

/*
 * _addr_safe - check whether [offset, offset+size) is within the FS partition
 */
rt_inline int _addr_safe(rt_uint32_t offset, rt_size_t size)
{
    if (size == 0U)
    {
        return 1;
    }
    if ((offset + (rt_uint32_t)size) < offset)
    {
        return 0;
    }
    if (offset < QSPI_FS_OFFSET)
    {
        return 0;
    }
    if ((offset + (rt_uint32_t)size) > (QSPI_FS_OFFSET + QSPI_FS_SIZE))
    {
        return 0;
    }
    return 1;
}

/*
 * Low-level NOR Flash operations (mapped from SDK flexspi_nor_flash_ops.c)
 *
 * All functions are marked QSPI_RAM_CODE (placed in ITCM) because they are
 * called while a FLEXSPI IP command is in progress, during which AHB access
 * is suspended and the CPU must fetch instructions from ITCM.
 */

/*
 * _nor_write_enable - send WREN command (SDK: flexspi_nor_write_enable)
 */
QSPI_RAM_CODE static status_t _nor_write_enable(rt_uint32_t base_addr)
{
    flexspi_transfer_t xfer;

    xfer.deviceAddress = base_addr;
    xfer.port          = FLASH_PORT;
    xfer.cmdType       = kFLEXSPI_Command;
    xfer.SeqNumber     = 1;
    xfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    return FLEXSPI_TransferBlocking(s_handle->base, &xfer);
}

/*
 * _nor_wait_busy - poll WIP bit until Flash is idle (SDK: flexspi_nor_wait_bus_busy)
 *
 * W25Q128JWSIQ SR1[0] = WIP (Write In Progress)
 * FLASH_BUSY_STATUS_POL = 1: bit set means busy
 */
QSPI_RAM_CODE static status_t _nor_wait_busy(void)
{
    rt_uint32_t        read_val = 0;
    rt_uint32_t        timeout  = 0;
    status_t           status;
    rt_bool_t          is_busy;
    flexspi_transfer_t xfer;

    xfer.deviceAddress = 0;
    xfer.port          = FLASH_PORT;
    xfer.cmdType       = kFLEXSPI_Read;
    xfer.SeqNumber     = 1;
    xfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READSTATUSREG;
    xfer.data          = &read_val;
    xfer.dataSize      = 1;

    do
    {
        status = FLEXSPI_TransferBlocking(s_handle->base, &xfer);
        if (status != kStatus_Success)
        {
            return status;
        }

        /* Busy detection logic identical to SDK example */
        if (FLASH_BUSY_STATUS_POL)
        {
            is_busy = (read_val & (1U << FLASH_BUSY_STATUS_OFFSET)) != 0U;
        }
        else
        {
            is_busy = (read_val & (1U << FLASH_BUSY_STATUS_OFFSET)) == 0U;
        }

        if (++timeout > WIP_TIMEOUT_COUNT)
        {
            return kStatus_Timeout;
        }
    }
    while (is_busy);

    return kStatus_Success;
}

/*
 * _nor_erase_sector - erase one 4KB sector (SDK: flexspi_nor_flash_erase_sector)
 *
 * @addr: Flash internal offset (not AHB address)
 */
QSPI_RAM_CODE static status_t _nor_erase_sector(rt_uint32_t addr)
{
    rt_base_t          level;
    status_t           status;
    flexspi_transfer_t xfer;

    level = rt_hw_interrupt_disable();

    xfer.deviceAddress = addr;
    xfer.port          = FLASH_PORT;
    xfer.cmdType       = kFLEXSPI_Command;
    xfer.SeqNumber     = 1;
    xfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(s_handle->base, &xfer);
    if (status != kStatus_Success)
    {
        rt_hw_interrupt_enable(level);
        return status;
    }

    xfer.seqIndex = NOR_CMD_LUT_SEQ_IDX_ERASESECTOR;
    status = FLEXSPI_TransferBlocking(s_handle->base, &xfer);
    if (status != kStatus_Success)
    {
        rt_hw_interrupt_enable(level);
        return status;
    }

    status = _nor_wait_busy();
    if (status == kStatus_Success)
    {
        FLEXSPI_SoftwareReset(s_handle->base);
    }

    rt_hw_interrupt_enable(level);

    return status;
}

/*
 * _nor_page_program - program one page (SDK: flexspi_nor_flash_page_program)
 *
 * Uses PAGEPROGRAM_QUAD (0x32, 1-1-4 mode) for faster write speed,
 * consistent with the SDK example. src must be a 4-byte aligned SRAM buffer.
 */
QSPI_RAM_CODE static status_t _nor_page_program(rt_uint32_t addr, const rt_uint32_t *src)
{
    rt_base_t          level;
    status_t           status;
    flexspi_transfer_t xfer;

    level = rt_hw_interrupt_disable();

    status = _nor_wait_busy();
    if (status != kStatus_Success)
    {
        rt_hw_interrupt_enable(level);
        return status;
    }

    status = _nor_write_enable(addr);
    if (status != kStatus_Success)
    {
        rt_hw_interrupt_enable(level);
        return status;
    }

    xfer.deviceAddress = addr;
    xfer.port          = FLASH_PORT;
    xfer.cmdType       = kFLEXSPI_Write;
    xfer.SeqNumber     = 1;
    xfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_PAGEPROGRAM_QUAD;
    xfer.data          = (rt_uint32_t *)src;
    xfer.dataSize      = QSPI_PAGE_SIZE;

    status = FLEXSPI_TransferBlocking(s_handle->base, &xfer);
    if (status != kStatus_Success)
    {
        rt_hw_interrupt_enable(level);
        return status;
    }

    status = _nor_wait_busy();
    if (status == kStatus_Success)
    {
        FLEXSPI_SoftwareReset(s_handle->base);
    }

    rt_hw_interrupt_enable(level);

    return status;
}

/*
 * rt_qspi_flash_init - initialize the QSPI NOR Flash driver
 *
 * Note: drv_flexspi.c has already performed the following via INIT_DEVICE_EXPORT:
 *   - flexspi_clock_init
 *   - FLEXSPI_Init
 *   - FLEXSPI_SetFlashConfig
 *   - FLEXSPI_UpdateLUT
 *   - FLEXSPI_SoftwareReset
 * This function only acquires the handle and verifies Flash connectivity.
 */
int rt_qspi_flash_init(void)
{
    rt_uint8_t         vendor_id = 0;
    rt_uint32_t        temp      = 0;
    status_t           status;
    flexspi_transfer_t xfer;

    if (s_inited)
    {
        return RT_EOK;
    }

    /* Acquire the controller handle already initialized by drv_flexspi.c */
    s_handle = imxrt_flexspi_get_handle();
    if ((s_handle == RT_NULL) || (s_handle->base == RT_NULL))
    {
        LOG_E("FlexSPI handle not ready, check INIT order");
        return -RT_ERROR;
    }

    /* Read Vendor ID to verify Flash connectivity (SDK: flexspi_nor_get_vendor_id) */
    xfer.deviceAddress = 0;
    xfer.port          = FLASH_PORT;
    xfer.cmdType       = kFLEXSPI_Read;
    xfer.SeqNumber     = 1;
    xfer.seqIndex      = NOR_CMD_LUT_SEQ_IDX_READID;
    xfer.data          = &temp;
    xfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(s_handle->base, &xfer);
    if (status != kStatus_Success)
    {
        LOG_E("read vendor ID failed, status=0x%X", (unsigned)status);
        return -RT_ERROR;
    }

    vendor_id = (rt_uint8_t)(temp & 0xFFU);
    if ((vendor_id == 0x00U) || (vendor_id == 0xFFU))
    {
        LOG_E("Flash not detected (vendor=0x%02X)", vendor_id);
        return -RT_ERROR;
    }

    LOG_I("Vendor ID: 0x%02X", vendor_id);

    /*
     * W25Q128JWSIQ: QE bit is set by default from factory, no Quad Enable
     * sequence is needed. For other Flash models, refer to SDK example
     * flexspi_nor_enable_quad_mode() to add this step.
     */

    if (rt_mutex_init(&s_mutex, "flashmtx", RT_IPC_FLAG_PRIO) != RT_EOK)
    {
        LOG_E("mutex init failed");
        return -RT_ERROR;
    }

    s_inited = 1;

    LOG_I("init OK, base=0x%08X total=%uKB sector=%uB page=%uB",
          (unsigned)QSPI_FLASH_BASE,
          (unsigned)(QSPI_FLASH_SIZE / 1024U),
          (unsigned)QSPI_SECTOR_SIZE,
          (unsigned)QSPI_PAGE_SIZE);
    LOG_I("fs partition: 0x%08X~0x%08X (%uKB)",
          (unsigned)(QSPI_FLASH_BASE + QSPI_FS_OFFSET),
          (unsigned)(QSPI_FLASH_BASE + QSPI_FS_OFFSET + QSPI_FS_SIZE - 1U),
          (unsigned)(QSPI_FS_SIZE / 1024U));

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_qspi_flash_init);

/*
 * rt_qspi_flash_read - read data via AHB direct memcpy (XIP mapping)
 *
 * Read operations do not interfere with FlexSPI IP commands, so this
 * function does not need to be placed in ITCM.
 */
int rt_qspi_flash_read(rt_uint32_t offset, rt_uint8_t *buf, rt_size_t size)
{
    if (!s_inited)
    {
        return -RT_ERROR;
    }
    if (size == 0U)
    {
        return 0;
    }
    if (buf == RT_NULL)
    {
        return -RT_EINVAL;
    }
    if (!_range_valid(offset, size))
    {
        return -RT_EINVAL;
    }

    rt_memcpy(buf, (const void *)(QSPI_FLASH_BASE + offset), size);

    return (int)size;
}

/*
 * rt_qspi_flash_mmap - zero-copy read by returning AHB mapping pointer
 */
void *rt_qspi_flash_mmap(rt_uint32_t offset, rt_size_t size)
{
    if (!s_inited)
    {
        return RT_NULL;
    }
    if (!_range_valid(offset, size))
    {
        return RT_NULL;
    }
    return (void *)(QSPI_FLASH_BASE + offset);
}

/*
 * rt_qspi_flash_write - write data to Flash (page-granular)
 *
 * This function is placed in ITCM (QSPI_RAM_CODE).
 *
 * Constraints (aligned with LittleFS prog_size = 256):
 *   - offset must be page-aligned (256B)
 *   - size must be a multiple of page size (256B)
 *
 * Data path: src -> s_write_buf (SRAM) -> Flash
 */
QSPI_RAM_CODE int rt_qspi_flash_write(rt_uint32_t offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t written = 0;
    status_t  status;

    if (!s_inited)
    {
        return -RT_ERROR;
    }
    if (size == 0U)
    {
        return 0;
    }
    if (buf == RT_NULL)
    {
        return -RT_EINVAL;
    }
    if (!_addr_safe(offset, size))
    {
        return -RT_EINVAL;
    }
    if ((offset % QSPI_PAGE_SIZE != 0U) || (size % QSPI_PAGE_SIZE != 0U))
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&s_mutex, RT_WAITING_FOREVER);

    while (written < size)
    {
        /*
         * Data must be relayed through an SRAM buffer.
         * SDK example declares s_nor_program_buffer as SDK_ALIGN(static uint8_t, 4).
         * s_write_buf is equivalently 4-byte aligned and resides in SRAM.
         */
        rt_memcpy(s_write_buf, buf + written, QSPI_PAGE_SIZE);

        status = _nor_page_program(offset + written, (const rt_uint32_t *)s_write_buf);
        if (status != kStatus_Success)
        {
            rt_mutex_release(&s_mutex);
            return -RT_ERROR;
        }

        /*
         * Cache maintenance (consistent with SDK DCACHE_InvalidateByRange):
         * Invalidate the AHB-mapped cache region after write completes to
         * ensure subsequent memcpy/mmap reads return newly written data.
         */
        DCACHE_InvalidateByRange(QSPI_FLASH_BASE + offset + written, QSPI_PAGE_SIZE);

        written += QSPI_PAGE_SIZE;
    }

    rt_mutex_release(&s_mutex);
    return (int)size;
}

/*
 * rt_qspi_flash_erase - erase Flash sectors
 *
 * This function is placed in ITCM (QSPI_RAM_CODE).
 *
 * offset and size must be sector-aligned (4KB).
 * Only the filesystem partition is allowed to be erased (_addr_safe guard).
 */
QSPI_RAM_CODE int rt_qspi_flash_erase(rt_uint32_t offset, rt_size_t size)
{
    rt_uint32_t addr;
    rt_uint32_t addr_end;
    status_t    status;

    if (!s_inited)
    {
        return -RT_ERROR;
    }
    if (size == 0U)
    {
        return 0;
    }
    if (!_addr_safe(offset, size))
    {
        return -RT_EINVAL;
    }
    if ((offset % QSPI_SECTOR_SIZE != 0U) || (size % QSPI_SECTOR_SIZE != 0U))
    {
        return -RT_EINVAL;
    }

    addr     = offset;
    addr_end = offset + (rt_uint32_t)size;

    rt_mutex_take(&s_mutex, RT_WAITING_FOREVER);

    while (addr < addr_end)
    {
        status = _nor_erase_sector(addr);
        if (status != kStatus_Success)
        {
            rt_mutex_release(&s_mutex);
            return -RT_ERROR;
        }

        /* Invalidate D-Cache for the erased AHB region */
        DCACHE_InvalidateByRange(QSPI_FLASH_BASE + addr, QSPI_SECTOR_SIZE);

        addr += QSPI_SECTOR_SIZE;
    }

    rt_mutex_release(&s_mutex);
    return (int)size;
}
