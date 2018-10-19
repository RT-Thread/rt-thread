/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-08-08     Urey         the first version
 */

#ifndef DRIVER_DRV_PMU_H_
#define DRIVER_DRV_PMU_H_

int drv_pmu_init(void);
void drv_pmu_power_up(void);
void drv_pmu_power_down(void);
int drv_pmu_get_keypwr(void);
#endif /* DRIVER_DRV_PMU_H_ */
