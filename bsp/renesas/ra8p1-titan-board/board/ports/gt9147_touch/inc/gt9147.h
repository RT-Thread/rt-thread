/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-01     tyustli     the first version
 */

#ifndef __GT9147_H_
#define __GT9147_H_
#include <rtthread.h>
#include <rtdevice.h>

#define GTP_ADDR_LENGTH        (2)
#define GT9147_MAX_TOUCH       (5)
#define GT9147_POINT_INFO_NUM  (8)

#define GT9147_ADDRESS_HIGH    (0x5D)
#define GT9147_ADDRESS_LOW     (0x14)

#define GT9147_COMMAND         (0x8040)
#define GT9147_CONFIG          (0x8047)

#define GT9XX_PRODUCT_ID       (0x8140)
#define GT9147_READ_STATUS     (0x814E)

#define GT9147_POINT1_REG      (0x814F)
#define GT9147_POINT2_REG      (0X8157)
#define GT9147_POINT3_REG      (0X815F)
#define GT9147_POINT4_REG      (0X8167)
#define GT9147_POINT5_REG      (0X816F)

#define GT9147_CHECK_SUM       (0X80FF)

int rt_hw_gt9147_init(const char *name, struct rt_touch_config *cfg);

#endif
