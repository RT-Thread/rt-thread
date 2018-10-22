/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê7ÔÂ29ÈÕ     Urey         the first version
 */

#ifndef _DRV_RESET_H_
#define _DRV_RESET_H_

/* WDT */
void wdt_start_count(int msecs);
void wdt_stop_count(void);
void wdt_clear(void);

/* hibernate */
void x1000_hibernate(void);


/* Reset */
/* reset_cmd[] = "wdt","hibernate","recovery" */
int x1000_reset(const char *reset_cmd);


#define RESET_HR_BIT	(0x01 << 3)
#define RESET_P0R_BIT	(0x01 << 2)
#define RESET_WR_BIT	(0x01 << 1)
#define RESET_PR_BIT	(0x01 << 0)
uint32_t x1000_get_last_reset(void);


#endif /* _DRV_RESET_H_ */
