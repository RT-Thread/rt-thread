/*
 * flash_rw_demo.c
 *
 * Demo: erase and write 1KB data to the last 1MB of the 16MB NOR Flash
 * using rt_qspi_flash_erase / rt_qspi_flash_write / rt_qspi_flash_read.
 *
 * Flash layout (W25Q128JWSIQ, 16MB):
 *   QSPI_FLASH_SIZE  = 16MB  (0x01000000)
 *   QSPI_FS_OFFSET   = 0x00F00000  (last 1MB, start of FS partition)
 *   QSPI_FS_SIZE     = 0x00100000  (1MB)
 *   QSPI_SECTOR_SIZE = 4KB  (minimum erase unit)
 *   QSPI_PAGE_SIZE   = 256B (minimum write unit)
 *
 * To write 1KB we need:
 *   - Erase: 1 sector (4KB) - erase is always sector-granular
 *   - Write: 4 pages x 256B = 1KB
 *
 * Usage: type "flash_rw_demo" in the MSH console.
 */

#include <rtthread.h>
#include "drv_flexspi_nor_flash.h"

/* Target offset: start of the last 1MB (FS partition base) */
#define DEMO_OFFSET QSPI_FS_OFFSET

/* We write 1KB = 4 pages, but we must erase at least one 4KB sector first */
#define DEMO_WRITE_SIZE (1024U)
#define DEMO_ERASE_SIZE QSPI_SECTOR_SIZE    /* 4KB - minimum erase granularity */

/* Fill pattern written to Flash */
#define DEMO_FILL_BYTE 0xA5U

static void flash_rw_demo(void)
{
    static rt_uint8_t write_buf[DEMO_WRITE_SIZE];
    static rt_uint8_t read_buf[DEMO_WRITE_SIZE];
    int ret;
    rt_uint32_t i;
    rt_uint32_t mismatch = 0;

    rt_kprintf("[flash_demo] target offset : 0x%08X (last 1MB of 16MB Flash)\n",
               (unsigned)DEMO_OFFSET);
    rt_kprintf("[flash_demo] erase size    : %u bytes (1 sector)\n",
               (unsigned)DEMO_ERASE_SIZE);
    rt_kprintf("[flash_demo] write size    : %u bytes (1KB)\n",
               (unsigned)DEMO_WRITE_SIZE);

    /* ------------------------------------------------------------------ */
    /* Step 1: Erase one sector (4KB) that covers our 1KB write area       */
    /* ------------------------------------------------------------------ */
    rt_kprintf("[flash_demo] erasing sector at offset 0x%08X ...\n",
               (unsigned)DEMO_OFFSET);

    ret = rt_qspi_flash_erase(DEMO_OFFSET, DEMO_ERASE_SIZE);
    if (ret < 0)
    {
        rt_kprintf("[flash_demo] ERROR: erase failed, ret=%d\n", ret);
        return;
    }
    rt_kprintf("[flash_demo] erase OK\n");

    /* ------------------------------------------------------------------ */
    /* Step 2: Write 1KB (4 pages of 256B) with pattern 0xA5              */
    /* ------------------------------------------------------------------ */
    for (i = 0; i < DEMO_WRITE_SIZE; i++)
    {
        write_buf[i] = (rt_uint8_t)(DEMO_FILL_BYTE ^ (i & 0xFFU));
    }

    rt_kprintf("[flash_demo] writing %u bytes at offset 0x%08X ...\n",
               (unsigned)DEMO_WRITE_SIZE, (unsigned)DEMO_OFFSET);

    ret = rt_qspi_flash_write(DEMO_OFFSET, write_buf, DEMO_WRITE_SIZE);
    if (ret < 0)
    {
        rt_kprintf("[flash_demo] ERROR: write failed, ret=%d\n", ret);
        return;
    }
    rt_kprintf("[flash_demo] write OK (%d bytes written)\n", ret);

    /* ------------------------------------------------------------------ */
    /* Step 3: Read back and verify                                        */
    /* ------------------------------------------------------------------ */
    rt_kprintf("[flash_demo] reading back %u bytes ...\n",
               (unsigned)DEMO_WRITE_SIZE);

    ret = rt_qspi_flash_read(DEMO_OFFSET, read_buf, DEMO_WRITE_SIZE);
    if (ret < 0)
    {
        rt_kprintf("[flash_demo] ERROR: read failed, ret=%d\n", ret);
        return;
    }

    for (i = 0; i < DEMO_WRITE_SIZE; i++)
    {
        if (read_buf[i] != write_buf[i])
        {
            rt_kprintf("[flash_demo] MISMATCH at byte %u: wrote 0x%02X, read 0x%02X\n",
                       (unsigned)i, (unsigned)write_buf[i], (unsigned)read_buf[i]);
            mismatch++;
            if (mismatch >= 8U)
            {
                rt_kprintf("[flash_demo] (too many errors, stopping report)\n");
                break;
            }
        }
    }

    if (mismatch == 0U)
    {
        rt_kprintf("[flash_demo] verify PASS - all %u bytes match\n",
                   (unsigned)DEMO_WRITE_SIZE);
    }
    else
    {
        rt_kprintf("[flash_demo] verify FAIL - %u mismatches found\n",
                   (unsigned)mismatch);
    }
}

MSH_CMD_EXPORT(flash_rw_demo, erase + write 1KB at last 1MB of 16MB NOR Flash);
