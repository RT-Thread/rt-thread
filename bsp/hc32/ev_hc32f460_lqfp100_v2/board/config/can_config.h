/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_CAN1
#define CAN1_CLOCK_SEL                  (CAN_CLOCK_SRC_40M)
#ifdef RT_CAN_USING_CANFD
#define CAN1_CANFD_MODE                 (CAN_FD_MD_ISO)
#endif
#define CAN1_NAME                       ("can1")
#ifndef CAN1_INIT_PARAMS
#define CAN1_INIT_PARAMS                                    \
    {                                                       \
       .name = CAN1_NAME,                                   \
       .single_trans_mode = RT_FALSE                        \
    }
#endif /* CAN1_INIT_PARAMS */
#endif /* BSP_USING_CAN1 */

/* Bit time config
  Restrictions: u32TimeSeg1 >= u32TimeSeg2 + 1, u32TimeSeg2 >= u32SJW.

  Baudrate = CANClock/(u32Prescaler*(u32TimeSeg1 + u32TimeSeg2))
  TQ = u32Prescaler / CANClock.
  Bit time = (u32TimeSeg2 + u32TimeSeg2) x TQ.

  The following bit time configures are based on CAN Clock 40M
*/
#define CAN_BIT_TIME_CONFIG_1M_BAUD                         \
    {                                                       \
        .u32Prescaler = 2,                                  \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_800K_BAUD                       \
    {                                                       \
        .u32Prescaler = 2,                                  \
        .u32TimeSeg1 = 20,                                  \
        .u32TimeSeg2 = 5,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_500K_BAUD                       \
    {                                                       \
        .u32Prescaler = 4,                                  \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_250K_BAUD                       \
    {                                                       \
        .u32Prescaler = 8,                                  \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_125K_BAUD                       \
    {                                                       \
        .u32Prescaler = 16,                                 \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_100K_BAUD                       \
    {                                                       \
        .u32Prescaler = 20,                                 \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_50K_BAUD                        \
    {                                                       \
        .u32Prescaler = 40,                                 \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_20K_BAUD                        \
    {                                                       \
        .u32Prescaler = 100,                                \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#define CAN_BIT_TIME_CONFIG_10K_BAUD                        \
    {                                                       \
        .u32Prescaler = 200,                                \
        .u32TimeSeg1 = 16,                                  \
        .u32TimeSeg2 = 4,                                   \
        .u32SJW = 4                                         \
    }

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */
