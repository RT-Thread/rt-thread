/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-07-10     ox-horse         first version
 */

#include <rtconfig.h>

#ifdef BSP_USING_NAND

#include "femc_timing.h"

//#define DRV_DEBUG
#define LOG_TAG "drv.nand"
#include <drv_log.h>
#include <rtdevice.h>
#include <drivers/mtd_nand.h>

#if defined(SOC_SERIES_N32H7xx)
static FEMC_InitType NAND_InitStructure = { 0 };

/* NAND chip select and bank address derived from Kconfig */
#ifdef BSP_USING_NAND_BANK1
#define NAND_CHIP      NAND_CHIP_1
#define NAND_BANK_ADDR ((uint32_t)0xA0000000)
#endif

#ifdef BSP_USING_NAND_BANK2
#define NAND_CHIP      NAND_CHIP_2
#define NAND_BANK_ADDR ((uint32_t)0xB0000000)
#endif

#endif

static struct rt_mtd_nand_device _nand_dev;

/*
 * FEMC AXI address layout for NAND access:
 *
 *   [31:24]  Chip select address
 *   [23:21]  Number of address cycles (0..7)
 *   [20]     End command valid
 *   [19]     0 = command phase, 1 = data phase
 *   [18:11]  End command
 *   [10:3]   Start command
 *   [2:0]    Byte lane strobes (AXI standard)
 */
#define NAND_CMD_AREA  ((uint32_t)0x00000000)   /* bit19 = 0 */
#define NAND_DATA_AREA ((uint32_t)0x00080000)   /* bit19 = 1 */

/*
 * Address cycle count auto-derived from Kconfig NAND chip parameters.
 *
 * Total pages = pages_per_block * block_count.
 * row_bits = ceil(log2(total_pages)), row_cycles = ceil(row_bits / 8).
 *
 *   total_pages <= 65536     → 16-bit row, 2 row cycles
 *   total_pages <= 16777216  → 24-bit row, 3 row cycles
 *   total_pages >  16777216  → 32-bit row, 4 row cycles
 *
 * Read/Write: 2 column address cycles + row address cycles.
 * Erase:      row address cycles only (no column address).
 * READ_ID:    fixed at 1 address cycle per NAND standard.
 */
#define NAND_TOTAL_PAGES (BSP_NAND_PAGES_PER_BLOCK * BSP_NAND_BLOCK_COUNT)

#if NAND_TOTAL_PAGES <= 65536
#define NAND_ROW_ADDR_CYCLES 2
#elif NAND_TOTAL_PAGES <= 16777216
#define NAND_ROW_ADDR_CYCLES 3
#else
#define NAND_ROW_ADDR_CYCLES 4
#endif

#define NAND_RW_ADDR_CYCLES    (2 + NAND_ROW_ADDR_CYCLES)
#define NAND_ERASE_ADDR_CYCLES NAND_ROW_ADDR_CYCLES

/* Encode cycle count into AXI address bits [23:21] */
#define NAND_ADDR_CYCLES(n) ((uint32_t)(n) << 21)

#define NAND_CMD_END_ENABLE   ((uint32_t)0x00100000)
#define NAND_CMD_END_DISABLE  ((uint32_t)0x00000000)
#define NAND_CLEAR_CS_ENABLE  ((uint32_t)0x00200000)
#define NAND_CLEAR_CS_DISABLE ((uint32_t)0x00000000)

#define NAND_ECC_LAST_ENABLE  ((uint32_t)0x00000400)
#define NAND_ECC_LAST_DISABLE ((uint32_t)0x00000000)

/* Standard NAND flash commands */
#define NAND_CMD_READ_1ST  ((uint8_t)0x00)
#define NAND_CMD_READ_2ND  ((uint8_t)0x30)
#define NAND_CMD_WRITE_1ST ((uint8_t)0x80)
#define NAND_CMD_WRITE_2ND ((uint8_t)0x10)
#define NAND_CMD_ERASE_1ST ((uint8_t)0x60)
#define NAND_CMD_ERASE_2ND ((uint8_t)0xD0)
#define NAND_CMD_READ_ID   ((uint8_t)0x90)
#define NAND_CMD_STATUS    ((uint8_t)0x70)
#define NAND_CMD_RESET     ((uint8_t)0xFF)

/* NAND status bits */
#define NAND_STATUS_READY ((uint32_t)0x40)
#define NAND_STATUS_ERROR ((uint32_t)0x01)

/*
 * FEMC uses Hamming code with 1-bit correction / 2-bit detection.
 * Each 512-byte frame generates a 24-bit (3-byte) ECC value stored
 * in the spare area.
 *
 * ECC bytes per page = (page_size / 512) * 3
 *
 * Example: page_size = 2048 -> ECC = 2048/512 * 3 = 12 bytes
 *          oob_size  = 64   -> oob_free = 64 - 12 = 52 bytes
 */
#define NAND_ECC_SECTOR_SIZE      512
#define NAND_ECC_BYTES_PER_SECTOR 3

#define ECC_BYTES(page_size) ((page_size) / NAND_ECC_SECTOR_SIZE * NAND_ECC_BYTES_PER_SECTOR)
#define OOB_FREE(page, oob)  ((oob) - ECC_BYTES(page))

static rt_err_t rt_nand_init(void)
{
#if defined(SOC_SERIES_N32H7xx)
    /* FEMC Operating Mode for NAND Devices */
    AFIO_ConfigFEMCNANDSRAM(FEMC_NAND_SEL);

    FEMC_InitStruct(&NAND_InitStructure);

#ifdef BSP_USING_NAND_BUS_WIDTH_8B
    NAND_InitStructure.ChipCfg.MemWidth = FEMC_MEMORY_WIDTH_8BIT;
#endif /* BSP_USING_NAND_BUS_WIDTH_8B */

#ifdef BSP_USING_NAND_BUS_WIDTH_16B
    NAND_InitStructure.ChipCfg.MemWidth = FEMC_MEMORY_WIDTH_16BIT;
#endif /* BSP_USING_NAND_BUS_WIDTH_16B */

    /* FEMC Nand Timing Configuration */
    FEMC_Nnad_Timing_Config(&NAND_InitStructure.TimingCfg);

    FEMC_Init(&NAND_InitStructure);

    FEMC_SetCommand(NAND_CHIP, FEMC_CMD_UPDATEREGS, FEMC_CRE_POLARITY_LOW, 0);

    if (FEMC_CheckChipStatus(NAND_CHIP, &NAND_InitStructure.ChipCfg) != SUCCESS)
    {
        LOG_E("femc nand initialization chip mode parameter check error!");
        return -RT_ERROR;
    }

    if (FEMC_CheckTimingStatus(NAND_CHIP, &NAND_InitStructure.TimingCfg) != SUCCESS)
    {
        LOG_E("femc nand initialization timing parameter check error!");
        return -RT_ERROR;
    }

    /* Reset NAND chip */
    {
        uint32_t reset_cmd;

        reset_cmd                     = NAND_BANK_ADDR | NAND_ADDR_CYCLES(0) | NAND_CMD_END_DISABLE | NAND_CMD_AREA | (NAND_CMD_RESET << 3);
        *((__IO uint16_t *)reset_cmd) = 0x0000;
    }
#endif

    return RT_EOK;
}

/*
 * Wait for NAND operation to complete via FEMC busy flag.
 *
 * The FEMC_NAND_FLAG is set by hardware when the NAND R/B signal goes high
 * (all NAND chips in the wired-AND busy line are ready).
 *
 * Uses rt_thread_delay() between polls to yield to the scheduler instead
 * of a tight while-loop, preventing other threads from being starved.
 */
static rt_err_t nand_wait_busy(void)
{
    rt_uint32_t timeout = 0x100000;

    while (FEMC_GetFlag(FEMC_NAND_FLAG) != SET)
    {
        if (--timeout == 0)
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_delay(rt_tick_from_millisecond(1));
    }
    FEMC_ClrFlag(FEMC_NAND_FLAG_CLEAR);

    return RT_EOK;
}

/*
 * Poll NAND status register until ready or timeout.
 *
 * Re-issues READ STATUS (0x70) on each poll iteration for maximum
 * compatibility with different NAND chips (some chips require the
 * command to be re-sent before each status read).
 *
 * Returns -RT_EIO if the error bit is set, -RT_ETIMEOUT on timeout.
 */
static rt_err_t nand_check_status(uint32_t bank_addr)
{
    uint32_t timeout = 0x100000;
    uint32_t cmd, stat_addr;
    uint8_t  status;

    cmd       = bank_addr | NAND_ADDR_CYCLES(0) | NAND_CMD_END_DISABLE | NAND_CMD_AREA | (NAND_CMD_STATUS << 3);
    stat_addr = bank_addr | NAND_CLEAR_CS_ENABLE | NAND_CMD_END_DISABLE | NAND_DATA_AREA | NAND_ECC_LAST_DISABLE;

    do
    {
        *((__IO uint8_t *)cmd) = 0x00;
        status                 = *(__IO uint8_t *)(stat_addr);

        if (status & NAND_STATUS_ERROR)
        {
            return -RT_EIO;
        }
        if (status & NAND_STATUS_READY)
        {
            return RT_EOK;
        }
        timeout--;
        rt_thread_delay(rt_tick_from_millisecond(1));
    } while (timeout);

    return -RT_ETIMEOUT;
}

/*
 * ===========================================================================
 *  MTD NAND Driver Operations
 * ===========================================================================
 */

/*
 * Read NAND flash ID.
 * SDK reads 5 bytes, but rt_mtd_nand_read_id() returns only 32 bits.
 * Pack bytes 1-4 (Device + 3rd + 4th + 5th), discard byte 0 (Maker ID).
 * This matches the stm32mp1 convention in the RT-Thread codebase.
 */
static rt_err_t _read_id(struct rt_mtd_nand_device *device)
{
    uint32_t    cmd_addr, data_addr;
    uint8_t     id_bytes[5];
    rt_uint32_t id;

    cmd_addr  = NAND_BANK_ADDR | NAND_ADDR_CYCLES(1) | NAND_CMD_END_DISABLE | NAND_CMD_AREA | (NAND_CMD_READ_ID << 3);
    data_addr = NAND_BANK_ADDR | NAND_CLEAR_CS_DISABLE | NAND_CMD_END_DISABLE | NAND_DATA_AREA | NAND_ECC_LAST_DISABLE;

    *((__IO uint8_t *)cmd_addr) = 0x00;

    /* Read all 5 ID bytes */
    for (uint8_t i = 0; i < 5; i++)
    {
        id_bytes[i] = *((__IO uint8_t *)data_addr);
    }

    LOG_D("NAND ID: %02X %02X %02X %02X %02X",
          id_bytes[0], id_bytes[1], id_bytes[2], id_bytes[3], id_bytes[4]);

    /* Pack bytes 1-4 into 32-bit return value (byte 0 = Maker ID, discarded) */
    id  = (rt_uint32_t)id_bytes[1] << 24;
    id |= (rt_uint32_t)id_bytes[2] << 16;
    id |= (rt_uint32_t)id_bytes[3] << 8;
    id |= (rt_uint32_t)id_bytes[4];

    return (rt_err_t)id;
}

/* read one page (data + spare) */
static rt_err_t _read_page(struct rt_mtd_nand_device *device,
                           rt_off_t                   page,
                           rt_uint8_t *data, rt_uint32_t data_len,
                           rt_uint8_t *spare, rt_uint32_t spare_len)
{
    uint32_t cmd_addr, data_addr;
    uint32_t row_addr, i;

    row_addr = (uint32_t)page;

    /* Clear any stale R/B flag before issuing the command */
    FEMC_ClrFlag(FEMC_NAND_FLAG_CLEAR);

    /* Command phase: READ_1ST + row address + READ_2ND */
    cmd_addr = NAND_BANK_ADDR | NAND_ADDR_CYCLES(NAND_RW_ADDR_CYCLES) | NAND_CMD_END_ENABLE | NAND_CMD_AREA | (NAND_CMD_READ_2ND << 11) | (NAND_CMD_READ_1ST << 3);

    *((__IO uint32_t *)cmd_addr) = row_addr << 16;

    rt_err_t ret;

    /* Wait for NAND to load the page into internal buffer */
    ret = nand_wait_busy();
    if (ret != RT_EOK)
    {
        LOG_E("read page %d busy timeout", (int)page);
        return ret;
    }

    /*
     * Data phase: 32-bit AXI access for efficiency, 8-bit for remainder.
     *
     * The AXI access width is independent of the NAND bus width —
     * FEMC hardware handles the packing/unpacking transparently.
     * Using 32-bit access reduces the number of AXI transactions by 4x
     * compared to 8-bit, improving throughput on both 8-bit and 16-bit NAND.
     */
    if (data && data_len)
    {
        uint32_t *p32;
        uint32_t  word_cnt;

        data_addr = NAND_BANK_ADDR | NAND_CLEAR_CS_DISABLE | NAND_CMD_END_DISABLE | NAND_DATA_AREA | NAND_ECC_LAST_DISABLE;

        /* 32-bit aligned bulk */
        word_cnt = data_len / 4;
        p32      = (uint32_t *)data;
        for (i = 0; i < word_cnt; i++)
        {
            p32[i] = *((__IO uint32_t *)data_addr);
        }

        /* 8-bit remainder */
        for (i = word_cnt * 4; i < data_len; i++)
        {
            data[i] = *((__IO uint8_t *)data_addr);
        }
    }

    /* spare area read not implemented yet */

    ret = nand_check_status(NAND_BANK_ADDR);
    if (ret != RT_EOK)
    {
        LOG_E("read page %d status error %d", (int)page, ret);
    }
    return ret;
}

/* write one page (data + spare) */
static rt_err_t _write_page(struct rt_mtd_nand_device *device,
                            rt_off_t                   page,
                            const rt_uint8_t *data, rt_uint32_t data_len,
                            const rt_uint8_t *spare, rt_uint32_t spare_len)
{
    uint32_t cmd_addr, data_addr;
    uint32_t row_addr, i;

    row_addr = (uint32_t)page;

    /* Clear any stale R/B flag before issuing the command */
    FEMC_ClrFlag(FEMC_NAND_FLAG_CLEAR);

    /* Command phase: WRITE_1ST + row address */
    cmd_addr = NAND_BANK_ADDR | NAND_ADDR_CYCLES(NAND_RW_ADDR_CYCLES) | NAND_CMD_END_DISABLE | NAND_CMD_AREA | (NAND_CMD_WRITE_1ST << 3);

    *((__IO uint32_t *)cmd_addr) = row_addr << 16;

    /*
     * Data phase: 32-bit AXI access for efficiency, 8-bit for remainder.
     * See _read_page for rationale.
     */
    if (data && data_len)
    {
        uint32_t addr_no_end, addr_end;
        uint32_t word_cnt, remain_start;

        addr_no_end = NAND_BANK_ADDR | NAND_CLEAR_CS_DISABLE | NAND_CMD_END_DISABLE | NAND_DATA_AREA | (NAND_CMD_WRITE_2ND << 11) | NAND_ECC_LAST_DISABLE;
        addr_end    = NAND_BANK_ADDR | NAND_CLEAR_CS_ENABLE | NAND_CMD_END_ENABLE | NAND_DATA_AREA | (NAND_CMD_WRITE_2ND << 11) | NAND_ECC_LAST_DISABLE;

        word_cnt     = data_len / 4;
        remain_start = word_cnt * 4;

        /*
         * 32-bit writes:
         * - If no remainder, the last 32-bit word IS the last write overall → addr_end.
         * - If there is a remainder, all 32-bit words are NOT the last → addr_no_end.
         */
        if (remain_start == data_len)
        {
            /* No remainder: bulk - 1 with no_end, last word with end */
            for (i = 0; i < word_cnt - 1; i++)
            {
                *((__IO uint32_t *)addr_no_end) = ((const uint32_t *)data)[i];
            }
            *((__IO uint32_t *)addr_end) = ((const uint32_t *)data)[word_cnt - 1];
        }
        else
        {
            /* Has remainder: all words with no_end */
            for (i = 0; i < word_cnt; i++)
            {
                *((__IO uint32_t *)addr_no_end) = ((const uint32_t *)data)[i];
            }
        }

        /*
         * 8-bit remainder: last byte uses addr_end, preceding bytes use addr_no_end.
         */
        for (i = remain_start; i + 1 < data_len; i++)
        {
            *((__IO uint8_t *)addr_no_end) = data[i];
        }
        if (remain_start < data_len)
        {
            *((__IO uint8_t *)addr_end) = data[data_len - 1];
        }
    }
    else
    {
        data_addr                    = NAND_BANK_ADDR | NAND_CLEAR_CS_ENABLE | NAND_CMD_END_ENABLE | NAND_DATA_AREA | (NAND_CMD_WRITE_2ND << 11) | NAND_ECC_LAST_DISABLE;
        *((__IO uint8_t *)data_addr) = 0x00;
    }

    /* spare area write not implemented yet */

    rt_err_t ret;

    /* Wait for program completion, then check status */
    ret = nand_wait_busy();
    if (ret != RT_EOK)
    {
        LOG_E("write page %d busy timeout", (int)page);
        return ret;
    }

    ret = nand_check_status(NAND_BANK_ADDR);
    if (ret != RT_EOK)
    {
        LOG_E("write page %d status error %d", (int)page, ret);
    }
    return ret;
}

/* move page (for garbage collection) */
static rt_err_t _move_page(struct rt_mtd_nand_device *device,
                           rt_off_t src_page, rt_off_t dst_page)
{
    uint8_t *buf;
    rt_err_t result;

    buf = rt_malloc(device->page_size);
    if (!buf)
    {
        return -RT_ENOMEM;
    }

    /* Read source page (main data only, spare not handled yet) */
    result = _read_page(device, src_page, buf, device->page_size, RT_NULL, 0);
    if (result != RT_EOK)
    {
        rt_free(buf);
        return result;
    }

    /* Write to destination page */
    result = _write_page(device, dst_page, buf, device->page_size, RT_NULL, 0);
    rt_free(buf);
    return result;
}

/* erase one block */
static rt_err_t _erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    uint32_t cmd_addr;
    uint32_t row_addr;

    /*
     * Convert block number to row address.
     * The erase command only needs the block address (row address with
     * page bits zeroed). The FEMC uses 2 address cycles for erase.
     */
    row_addr = block * device->pages_per_block;

    /* Clear any stale R/B flag before issuing the command */
    FEMC_ClrFlag(FEMC_NAND_FLAG_CLEAR);

    /* Command phase: ERASE_1ST (2 addr cycles) + ERASE_2ND */
    cmd_addr = NAND_BANK_ADDR | NAND_ADDR_CYCLES(NAND_ERASE_ADDR_CYCLES) | NAND_CMD_END_ENABLE | NAND_CMD_AREA | (NAND_CMD_ERASE_2ND << 11) | (NAND_CMD_ERASE_1ST << 3);

    /*
     * Erase uses only row address cycles (no column address).
     * FEMC consumes data bytes from LSB upward per address cycle,
     * so row_addr goes into bits [15:0] without shifting.
     * (Read/Write uses << 16 to put column=0 in [15:0] and row in [31:16].)
     */
    *((__IO uint32_t *)cmd_addr) = row_addr;

    rt_err_t ret;

    /* Wait for erase completion, then check status */
    ret = nand_wait_busy();
    if (ret != RT_EOK)
    {
        LOG_E("erase block %d busy timeout", (int)block);
        return ret;
    }

    ret = nand_check_status(NAND_BANK_ADDR);
    if (ret != RT_EOK)
    {
        LOG_E("erase block %d status error %d", (int)block, ret);
    }
    return ret;
}

/*
 * Check if a block is bad.
 *
 * Requires reading spare area (bad block marker at first byte of spare
 * area of the first page). Spare area read is not yet implemented.
 */
static rt_err_t _check_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    return -RT_ENOSYS;
}

/*
 * Mark a block as bad.
 *
 * Requires writing spare area (bad block marker at first byte of spare
 * area of the first page). Spare area write is not yet implemented.
 */
static rt_err_t _mark_badblock(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    return -RT_ENOSYS;
}

static const struct rt_mtd_nand_driver_ops _nand_ops = {
    _read_id,
    _read_page,
    _write_page,
    _move_page,
    _erase_block,
    _check_block,
    _mark_badblock,
};

int rt_hw_nand_init(void)
{
    rt_err_t result;

    /* Initialize FEMC hardware */
    result = rt_nand_init();
    if (result != RT_EOK)
    {
        return result;
    }

    _nand_dev.page_size = BSP_NAND_PAGE_SIZE;
    _nand_dev.oob_size  = BSP_NAND_OOB_SIZE;
    /*
     * oob_free: bytes in the spare area available for the upper layer.
     *
     * FEMC ECC (Hamming code, 1-bit correction / 2-bit detection) generates
     * a 24-bit (3-byte) ECC value per 512-byte sector. See FEMC.md section 8.7.
     *
     *   ecc_bytes = page_size / 512 * 3
     *   oob_free  = oob_size - ecc_bytes
     *
     * The remaining oob_free bytes are available for bad block markers,
     * wear-leveling metadata, and filesystem bookkeeping.
     */
    _nand_dev.oob_free        = OOB_FREE(BSP_NAND_PAGE_SIZE, BSP_NAND_OOB_SIZE);
    _nand_dev.pages_per_block = BSP_NAND_PAGES_PER_BLOCK;
    _nand_dev.plane_num       = BSP_NAND_PLANE_NUM;
    _nand_dev.block_start     = 0;
    _nand_dev.block_end       = BSP_NAND_BLOCK_COUNT;
    _nand_dev.block_total     = _nand_dev.block_end - _nand_dev.block_start;
    _nand_dev.ops             = &_nand_ops;
    _nand_dev.priv            = RT_NULL;

    result = rt_mtd_nand_register_device("nand0", &_nand_dev);
    if (result != RT_EOK)
    {
        rt_device_unregister(&_nand_dev.parent);
        return result;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_nand_init);

#endif /* BSP_USING_NAND */
