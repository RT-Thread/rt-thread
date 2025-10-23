/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-24     heyuan       the first version
 * 2020-08-17     malongwei    Fix something
 */

#ifndef __DRV_FDCAN_H__
#define __DRV_FDCAN_H__

#include <board.h>
#include <rtdevice.h>

#if defined(RT_USING_CAN) && defined(RT_CAN_USING_CANFD)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    const char *name;
    FDCAN_HandleTypeDef fdcanHandle;
    FDCAN_RxHeaderTypeDef RxHeader;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t u8RxDataBuffer[8];
    uint8_t u8TxDataBuffer[8];
    FDCAN_FilterTypeDef FilterConfig; /*FDCAN filter*/
    struct rt_can_device device;      /* inherit from can device */
} stm32_fdcan_t;

typedef struct {
    uint32_t u32Baudrate;
    struct rt_can_bit_timing cam_bit_timing;
}stm32_fdcan_timing_t;

#ifdef __cplusplus
}
#endif

#endif /* RT_USING_CAN */
#endif /* __DRV_FDCAN_H__ */
