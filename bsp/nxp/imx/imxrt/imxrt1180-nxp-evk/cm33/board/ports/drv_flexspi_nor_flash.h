/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-03     CoreBoxer    support IMXRT1180-EVK
 */

#ifndef __DRV_FLEXSPI_NOR_FLASH_H__
#define __DRV_FLEXSPI_NOR_FLASH_H__

#include <rtthread.h>

/* ============================================================
 * Flash Physical Parameters
 * Source: SDK example app.h
 *   FLASH_SIZE = 0x4000 (Unit: KB) = 16MB
 *   FlexSPI1_AMBA_BASE = 0x28000000
 * ============================================================ */
#define QSPI_FLASH_BASE      FlexSPI1_AMBA_BASE    /* 0x28000000             */
#define QSPI_FLASH_SIZE      (0x4000U * 1024U)     /* 16MB (0x4000 KB)       */
#define QSPI_SECTOR_SIZE     0x00001000U            /* 4KB                    */
#define QSPI_PAGE_SIZE       256U                   /* 256B                   */

/*
 * Partition Plan (Total 16MB):
 *   0x00000000 ~ 0x007FFFFF: Application Code Area (8MB, limited by Scatter)
 *   0x00800000 ~ 0x00FFFFFF: File System Area (8MB, LittleFS)
 */
#define QSPI_FS_OFFSET       0x00800000U
#define QSPI_FS_SIZE         0x00800000U

/* ============================================================
 * RAM Code Section Attributes
 * Write/Erase functions placed in CodeQuickAccess (ITCM),
 * CPU can safely fetch instructions during FlexSPI IP command execution.
 * ============================================================ */
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    #define QSPI_RAM_CODE  __attribute__((section("CodeQuickAccess"), noinline))
#elif defined(__GNUC__)
    #define QSPI_RAM_CODE  __attribute__((section(".itcm.text"), noinline))
#elif defined(__ICCARM__)
    #define QSPI_RAM_CODE  __ramfunc
#else
    #define QSPI_RAM_CODE
#endif

/* ============================================================
 * External APIs
 * ============================================================ */
int   rt_qspi_flash_init(void);
int   rt_qspi_flash_read(uint32_t offset, uint8_t *buf, size_t size);
int   rt_qspi_flash_write(uint32_t offset, const uint8_t *buf, size_t size);
int   rt_qspi_flash_erase(uint32_t offset, size_t size);
void *rt_qspi_flash_mmap(uint32_t offset, size_t size);

#endif /* __DRV_FLEXSPI_NOR_FLASH_H__ */