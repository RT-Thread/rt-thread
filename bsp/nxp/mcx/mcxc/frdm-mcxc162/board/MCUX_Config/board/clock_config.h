/*
 * Copyright 2026 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

#define BOARD_BOOTCLOCKFROHF72M_CORE_CLOCK 72000000U

void BOARD_InitBootClocks(void);
void BOARD_BootClockFROHF72M(void);

#endif
