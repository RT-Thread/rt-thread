/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 * Copyright (c) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                   Notes
 * 2022-06-07     xiaoxiaolisunny          first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_CAN1
#ifndef CAN1_INIT_PARAMS
#define CAN1_INIT_PARAMS                                    \
    {                                                       \
       .name = "can1",                                      \
    }
#endif /* CAN1_INIT_PARAMS */
#endif /* BSP_USING_CAN1 */

/* Bit time config
  Restrictions: u32TimeSeg1 >= u32TimeSeg2 + 1, u32TimeSeg2 >= u32SJW.

  Baudrate = CANClock/(u32Prescaler*(u32TimeSeg1 + u32TimeSeg2))
  TQ = u32Prescaler / CANClock.
  Bit time = (u32TimeSeg1 + u32TimeSeg2) x TQ.

  The following bit time configures are based on CAN Clock 8M
*/
#define CAN_BIT_TIME_CONFIG_1M_BAUD                         \
    {                                                       \
        .u32Prescaler = 1,                                  \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_800K_BAUD                       \
    {                                                       \
        .u32Prescaler = 1,                                  \
        .u32TimeSeg1 = 6,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_500K_BAUD                       \
    {                                                       \
        .u32Prescaler = 2,                                  \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_250K_BAUD                       \
    {                                                       \
        .u32Prescaler = 4,                                  \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_125K_BAUD                       \
    {                                                       \
        .u32Prescaler = 8,                                 \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_100K_BAUD                       \
    {                                                       \
        .u32Prescaler = 10,                                 \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_50K_BAUD                        \
    {                                                       \
        .u32Prescaler = 20,                                 \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_20K_BAUD                        \
    {                                                       \
        .u32Prescaler = 50,                                \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#define CAN_BIT_TIME_CONFIG_10K_BAUD                        \
    {                                                       \
        .u32Prescaler = 100,                                \
        .u32TimeSeg1 = 5,                                  \
        .u32TimeSeg2 = 3,                                   \
        .u32SJW = 3                                         \
    }

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */


