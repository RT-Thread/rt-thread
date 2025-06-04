/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-20     Rbb666       Add GT9147 Touch Device
 */

#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include "rtthread.h"
#include "rtdevice.h"

#ifdef BSP_USING_TOUCH
#   define TOUCH_DBG_LEVEL DBG_LOG

#   define TOUCH_EVENT_UP      (0x01)
#   define TOUCH_EVENT_DOWN    (0x02)
#   define TOUCH_EVENT_MOVE    (0x03)
#   define TOUCH_EVENT_NONE    (0x80)
#endif

#endif
