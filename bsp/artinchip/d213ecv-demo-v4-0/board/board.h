/*
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include <interrupt.h>
#include "aic_soc.h"

#define MAX_HANDLERS 128
#define INTC_TYPE    INTC_TYPE_RISCV

void rt_hw_serial_init(void);

#endif /* __BOARD_H__ */
