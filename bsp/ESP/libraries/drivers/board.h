/*
 * Copyright (c) 2021-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-02     supperthomas first version
 * 2024-12-08     wumingzi     support rt_hw_us_delay
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtconfig.h>
#include "rttypes.h"

#ifdef __cplusplus
extern "C" {
#endif
void rt_hw_board_init(void);
void rt_hw_us_delay(rt_uint32_t us);

#ifdef __cplusplus
}
#endif
#endif