/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-13     Ran          I2C DMA sample for RT1180 CM33 EVK
 * 2026-08-14     Ran          Extend to multi-page write/read to stress DMA
 *
 * Target: 24LC32A EEPROM on LPI2C3 (RT1180 EVK)
 *   - 32 Kbit (4 KB), 32-byte page, 2-byte word address
 *   - 8-bit bus addr 0xA0/0xA1 -> 7-bit addr 0x50
 *   - Write cycle time max 5 ms
 *
 * Test plan:
 *   1. Write TEST_PAGES x PAGE_SIZE bytes, one page per write (must not cross
 *      a 32-byte page boundary in a single I2C write transaction).
 *   2. Read all bytes back in a single DMA read (or multiple if > DMA limit).
 *   3. Verify every byte.
 *
 * Usage (MSH):
 *   i2c_sample                  -- default bus "i2c3", addr 0x50, 4 pages
 *   i2c_sample i2c3 0x50 8      -- explicit bus, address, page count (1-16)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#define SAMPLE_I2C_BUS_NAME "i2c3"
#define SAMPLE_I2C_ADDR     0x50U   /* 7-bit form of 0xA0 */

/* 24LC32A page size */
#define PAGE_SIZE 32U
/* Default number of pages to test; each page = 32 bytes */
#define DEFAULT_TEST_PAGES 4U
/* Maximum pages (limited by DMA RX bounce buffer 512 bytes; 512/32 = 16) */
#define MAX_TEST_PAGES 16U
/* Starting EEPROM word address */
#define START_ADDR 0x0000U

/* Pattern generator: deterministic per-byte value for easy mismatch diagnosis */
static rt_uint8_t test_pattern(rt_uint16_t word_addr, rt_uint8_t offset)
{
    return (rt_uint8_t)((word_addr + offset + 0x5AU) & 0xFFU);
}

static void i2c_sample(int argc, char *argv[])
{
    const char *bus_name = SAMPLE_I2C_BUS_NAME;
    rt_uint16_t addr = SAMPLE_I2C_ADDR;
    rt_uint32_t num_pages = DEFAULT_TEST_PAGES;

    if (argc >= 2)
    {
        bus_name = argv[1];
    }
    if (argc >= 3)
    {
        addr = (rt_uint16_t)strtol(argv[2], RT_NULL, 0);
    }
    if (argc >= 4)
    {
        num_pages = (rt_uint32_t)strtol(argv[3], RT_NULL, 0);
        if (num_pages < 1U || num_pages > MAX_TEST_PAGES)
        {
            rt_kprintf("[i2c_sample] page count must be 1-%u\n", MAX_TEST_PAGES);
            return;
        }
    }

    rt_uint32_t total_bytes = num_pages * PAGE_SIZE;

    struct rt_i2c_bus_device *bus = rt_i2c_bus_device_find(bus_name);
    if (bus == RT_NULL)
    {
        rt_kprintf("[i2c_sample] cannot find bus: %s\n", bus_name);
        return;
    }

    rt_kprintf("[i2c_sample] writing %u pages (%u bytes) to %s addr=0x%02X ...\n",
               num_pages, total_bytes, bus_name, addr);

    /* ---- Write phase: one page per transaction ----
     * 24LC32A page write: [addr_hi, addr_lo, d0, d1, ..., d31]  (34 bytes total)
     * Must not cross a 32-byte page boundary. */
    /* tx_buf: 2-byte address + 32 data bytes = 34 bytes */
    rt_uint8_t tx_buf[2U + PAGE_SIZE];
    rt_uint32_t p;
    for (p = 0; p < num_pages; p++)
    {
        rt_uint16_t word_addr = (rt_uint16_t)(START_ADDR + p * PAGE_SIZE);
        tx_buf[0] = (rt_uint8_t)((word_addr >> 8) & 0xFFU);
        tx_buf[1] = (rt_uint8_t)(word_addr & 0xFFU);
        rt_uint8_t j;
        for (j = 0; j < PAGE_SIZE; j++)
        {
            tx_buf[2U + j] = test_pattern(word_addr, j);
        }

        struct rt_i2c_msg wr_msg;
        wr_msg.addr = addr;
        wr_msg.flags = RT_I2C_WR;
        wr_msg.len = (rt_uint16_t)(2U + PAGE_SIZE);
        wr_msg.buf = tx_buf;

        if (rt_i2c_transfer(bus, &wr_msg, 1) != 1)
        {
            rt_kprintf("[i2c_sample] write failed at page %u (addr=0x%04X)\n", p, word_addr);
            return;
        }

        /* 24LC32A write cycle: max 5 ms. Use 10 ms for margin. */
        rt_thread_mdelay(10);
    }
    rt_kprintf("[i2c_sample] write done\n");

    /* ---- Read phase ----
     * Step 1: set EEPROM internal address pointer to START_ADDR.
     * Step 2: read all bytes in one burst (DMA path). */
    rt_uint8_t reg_addr_buf[2];
    reg_addr_buf[0] = (rt_uint8_t)((START_ADDR >> 8) & 0xFFU);
    reg_addr_buf[1] = (rt_uint8_t)(START_ADDR & 0xFFU);
    struct rt_i2c_msg ptr_msg;
    ptr_msg.addr = addr;
    ptr_msg.flags = RT_I2C_WR;
    ptr_msg.len = 2U;
    ptr_msg.buf = reg_addr_buf;
    if (rt_i2c_transfer(bus, &ptr_msg, 1) != 1)
    {
        rt_kprintf("[i2c_sample] set-addr failed\n");
        return;
    }

    /* Static buffer: keep off stack so DMA4 can access it.
     * MAX_TEST_PAGES * PAGE_SIZE = 512 bytes matches DMA bounce buffer size. */
    static rt_uint8_t rx_buf[MAX_TEST_PAGES * PAGE_SIZE];
    rt_memset(rx_buf, 0xFFU, total_bytes);

    struct rt_i2c_msg rd_msg;
    rd_msg.addr = addr;
    rd_msg.flags = RT_I2C_RD;
    rd_msg.len = (rt_uint16_t)total_bytes;
    rd_msg.buf = rx_buf;
    if (rt_i2c_transfer(bus, &rd_msg, 1) != 1)
    {
        rt_kprintf("[i2c_sample] read failed\n");
        return;
    }

    /* ---- Verify ---- */
    rt_uint32_t fail_count = 0U;
    rt_uint32_t byte_idx;
    for (byte_idx = 0; byte_idx < total_bytes; byte_idx++)
    {
        rt_uint16_t word_addr = (rt_uint16_t)(START_ADDR + (byte_idx / PAGE_SIZE) * PAGE_SIZE);
        rt_uint8_t expected = test_pattern(word_addr, (rt_uint8_t)(byte_idx % PAGE_SIZE));
        if (rx_buf[byte_idx] != expected)
        {
            if (fail_count < 8U) /* report first 8 mismatches only */
            {
                rt_kprintf("[i2c_sample]   MISMATCH byte[%u]: got=0x%02X expected=0x%02X\n",
                           byte_idx, rx_buf[byte_idx], expected);
            }
            fail_count++;
        }
    }

    /* Print all received bytes, 16 per line */
    rt_kprintf("[i2c_sample] read data (%u bytes):", total_bytes);
    for (rt_uint32_t k = 0; k < total_bytes; k++)
    {
        if (k % 16U == 0U)
        {
            rt_kprintf("\n  [%04X]", (unsigned)(START_ADDR + k));
        }
        rt_kprintf(" %02X", rx_buf[k]);
    }
    rt_kprintf("\n");

    if (fail_count == 0U)
    {
        rt_kprintf("[i2c_sample] PASS -- %u bytes verified OK\n", total_bytes);
    }
    else
    {
        rt_kprintf("[i2c_sample] FAIL -- %u/%u bytes mismatched\n", fail_count, total_bytes);
    }
}

MSH_CMD_EXPORT(i2c_sample, EEPROM DMA test : i2c_sample[bus][addr][pages]);
