/*
 * COPYRIGHT (C) 2012-2022, Shanghai Real-Thread Technology Co., Ltd
 * All rights reserved.
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-20     Chushicheng  the first version
 */

#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include <stddef.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"

#define CST816_INT_PIN     GPIO_PIN_32
#define CST816_RST_PIN     GPIO_PIN_24

/* clang-format off */
#define CST816X_DEV_ADDR            0x15

#define CST816X_REG_GESTUREID       0x01
#define CST816X_REG_FINGERNUM       0x02
// xxxx.... STATUS
// ....xxxx XposH
#define CST816X_REG_XPOSH           0x03
#define CST816X_REG_XPOSL           0x04
// ....xxxx YposH
#define CST816X_REG_YPOSH           0x05
#define CST816X_REG_YPOSL           0x06

#define CST816X_REG_CHIPID          0xA7
#define CST816X_REG_PROJID          0xA8
#define CST816X_REG_FWVERSION       0xA9
#define CST816X_REG_FACTORYID       0xAA

// 0x03 -> sleep and disable wake up
#define CST816X_REG_SLEEPMODE       0xE5
// ......x. EnFatRst
// .......x En2FRst
#define CST816X_REG_ERRRESETCTL     0xEA
#define CST816X_REG_LONGPRESSTICK   0xEB

/* 0x01 CST816X_REG_GESTUREID */
#define CST816X_REG_GESTUREID_NONE          0x00
#define CST816X_REG_GESTUREID_SWIPE_UP      0x01
#define CST816X_REG_GESTUREID_SWIPE_DOWN    0x02
#define CST816X_REG_GESTUREID_SWIPE_LEFT    0x03
#define CST816X_REG_GESTUREID_SWIPE_RIGHT   0x04
#define CST816X_REG_GESTUREID_CLICK         0x05
#define CST816X_REG_GESTUREID_DOUBLE_CLICK  0x0b
#define CST816X_REG_GESTUREID_LONG_PRESS    0x0c

/* 0x02 CST816X_REG_FINGERNUM */
#define CST816X_REG_FINGERNUM_NONE          0x00
#define CST816X_REG_FINGERNUM_ONE           0x01

/* 0x03 CST816X_REG_XPOSH xxxx.... STATUS */
#define CST816X_REG_STATUS_FIRST_PRESS      0x0
#define CST816X_REG_STATUS_LONG_PRESS       0x8
#define CST816X_REG_STATUS_LIFTUP           0x4
/* clang-format on */

#endif