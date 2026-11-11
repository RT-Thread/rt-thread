/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-14     nxp-ran      First version for MIMXRT1180 CM33 BBNSM RTC.
 *
 * This driver is for the MIMXRT1180 (RT1180) CM33 core only.
 * The RT1180 does not have SNVS; the battery-backed domain is BBNSM.
 * CM33 in TrustZone secure world can access BBNSM registers directly.
 *
 * Do NOT use drv_rtc.c (SNVS/SNVS_LP) for RT1180 -- use this driver.
 */

#ifndef DRV_RTC_BBNSM_H__
#define DRV_RTC_BBNSM_H__

#include <rtdevice.h>

int rt_hw_rtc_init(void);

#endif /* DRV_RTC_BBNSM_H__ */
