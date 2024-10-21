/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-10-16     Pillar       first version
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>

#include "S32K344.h"
#include <string.h>

#define SRAM_SIZE        (184)
#define SRAM_END         (0x20400000 + SRAM_SIZE * 1024)

extern int __sram_data_end__;
#define HEAP_BEGIN      ((void *)&__sram_data_end__)
#define HEAP_END        SRAM_END

#ifdef __cplusplus
extern "C" {
#endif

void rt_hw_board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */
