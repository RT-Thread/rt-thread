/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      add E906 ram size
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#define APB_DEFAULT_FREQ         20000000   /* Hz */
#define E906FD_IRAM_SIZE         128
#define E906FD_IRAM_END          (0x20000000 + E906FD_IRAM_SIZE * 1024)

#endif /* __BOARD_H__ */
