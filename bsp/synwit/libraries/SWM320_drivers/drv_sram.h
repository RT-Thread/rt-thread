/*
 * Copyright (c) 2006-2022, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef DRV_SRAM_H__
#define DRV_SRAM_H__

#include "board.h"

#define EXT_SRAM_BASE SRAMM_BASE
#define EXT_SRAM_SIZE BSP_EXT_SRAM_SIZE
#define EXT_SRAM_BEGIN EXT_SRAM_BASE
#define EXT_SRAM_END (EXT_SRAM_BASE + EXT_SRAM_SIZE)

int rt_hw_sram_init(void);

#endif
