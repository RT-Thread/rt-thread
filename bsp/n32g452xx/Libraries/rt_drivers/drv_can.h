/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-09     chenbin      the first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

    int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
