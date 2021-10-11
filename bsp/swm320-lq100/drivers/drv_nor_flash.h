/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef DRV_NOR_FLASH_H__
#define DRV_NOR_FLASH_H__

#include "board.h"

#define BLOCK_SIZE (64 * 1024)
#define FLASH_SIZE (BSP_NOR_FLASH_SIZE)
#define BLOCK_COUNTER (FLASH_SIZE / BLOCK_SIZE)

int rt_hw_norflash_init(void);

#endif
