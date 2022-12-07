/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2014
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Watchdog register definitions
 */

#ifndef _SUNXI_HAL_WATCHDOG_H_
#define _SUNXI_HAL_WATCHDOG_H_

#include "sunxi_hal_common.h"

void hal_watchdog_disable(void);
void hal_watchdog_reset(int timeout);
void hal_watchdog_restart(void);
void hal_watchdog_info(void);
void hal_watchdog_init(void);
void hal_watchdog_stop(int timeout);
void hal_watchdog_start(int timeout);
void hal_watchdog_feed(void);
int hal_watchdog_suspend(int timeout);
int hal_watchdog_resume(int timeout);
int hal_watchdog_is_running(void);
#endif /* _SUNXI_HAL_WATCHDOG_H_ */
