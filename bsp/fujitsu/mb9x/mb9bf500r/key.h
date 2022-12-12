/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-06     lgnq
 */
#ifndef __KEY_H__
#define __KEY_H__

#include "mb9bf506r.h"

#define KEY_DOWN      (1<<0)
#define KEY_ENTER     (1<<1)
#define KEY_LEFT      (1<<2)
#define KEY_RIGHT     (1<<3)
#define KEY_UP        (1<<4)
#define NO_KEY        (1<<5)

#define KEY_MASK        (KEY_DOWN | KEY_ENTER | KEY_LEFT | KEY_RIGHT | KEY_UP)
#define KEY_PFR         (FM3_GPIO->PFR7)
#define KEY_PCR         (FM3_GPIO->PCR7)
#define KEY_PDIR        (FM3_GPIO->PDIR7)
#define KEY_DDR         (FM3_GPIO->DDR7)

#define RT_DEVICE_CTRL_KEY_SCAN   0
#define RT_DEVICE_CTRL_KEY_STATUS 1

#define SET_BIT(byte, bit)      ((byte) |= (1<<(bit)))
#define CLR_BIT(byte, bit)      ((byte) &= ~(1<<(bit)))
#define TST_BIT(byte, bit)      (((byte) & (1<<(bit)))?1:0)

#define KEY_ENTER_GETVALUE()  TST_BIT(KEY_PDIR, 1)
#define KEY_DOWN_GETVALUE()   TST_BIT(KEY_PDIR, 0)
#define KEY_UP_GETVALUE()     TST_BIT(KEY_PDIR, 4)
#define KEY_RIGHT_GETVALUE()  TST_BIT(KEY_PDIR, 3)
#define KEY_LEFT_GETVALUE()   TST_BIT(KEY_PDIR, 2)

void rt_hw_key_init(void);

#endif
