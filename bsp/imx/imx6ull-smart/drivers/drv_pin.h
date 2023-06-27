/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-13     Lyons        first version
 * 2021-06-23     RiceChen     add get pin API
 */

#ifndef __DRV_PIN_H__
#define __DRV_PIN_H__

#include "board.h"

#define GET_PIN(PORTx, PIN)      (32 * (PORTx - 1) + (PIN & 31))

#endif //#ifndef __DRV_PIN_H__
