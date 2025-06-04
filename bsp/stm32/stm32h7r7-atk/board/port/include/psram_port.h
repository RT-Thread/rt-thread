/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-24     yuanjie      The first version for STM32H7RSxx
 */

#ifndef __PSRAM_PORT_H__
#define __PSRAM_PORT_H__

/* parameters for psram peripheral */
#define PSRAM_BANK_ADDR ((uint32_t)0x70000000)
/* data width: 8, 16, 32 */
#define PSRAM_DATA_WIDTH 32
#define PSRAM_SIZE ((uint32_t)0x2000000) // 256Mbits, 32MB

#endif
