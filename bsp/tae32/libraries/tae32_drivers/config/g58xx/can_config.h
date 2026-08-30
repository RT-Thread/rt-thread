/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-02-27     yeml    first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define TAE32_CAN_FD_ISO 1
#define TAE32_CAN_FD_NON_ISO 0


#define CAN_CLOCK                      (60000000U)

#ifdef BSP_USING_CAN0
#ifdef RT_CAN_USING_CANFD
#define CAN0_CAN_FD_MODE                  TAE32_CAN_FD_NON_ISO
#endif
#endif

#ifdef BSP_USING_CAN1
#ifdef RT_CAN_USING_CANFD
#define CAN1_CAN_FD_MODE                  TAE32_CAN_FD_NON_ISO
#endif
#endif


/* Bit time config
  Restrictions: num_seg1 >= (num_seg2 + 1), (num_seg2 + 1) >= (num_sjw + 1).

  Baudrate = CANClock/(perescaler*((num_seg1 + 2) + (num_seg2 + 1)))
  TQ = perescaler / CANClock.


     | SYNC | PROP |    PHASE1    |     PHASE2     |
TQ:  |  1   |   1  |  um_seg1 + 2 |   num_seg2 + 1 |

  Bit time = ((num_seg1 + 2) + (num_seg2 + 1) )

  Sample point = (num_seg1 + 2) / ( (num_seg1 + 2) + (num_seg2 + 1) )

  Users need to calculate the values under different baud rates based on the actual CAN clock.

  The following bit time configures are based on CAN Clock 60M,Sample point is 80%
*/
#define CAN_BIT_TIME_CONFIG_1M_BAUD                         \
    {                                                       \
        .prescaler = 4,                                     \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_800K_BAUD                       \
    {                                                       \
        .prescaler = 5,                                     \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_500K_BAUD                       \
    {                                                       \
        .prescaler = 8,                                     \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_250K_BAUD                       \
    {                                                       \
        .prescaler = 16,                                    \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_125K_BAUD                       \
    {                                                       \
        .prescaler = 32,                                    \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_100K_BAUD                       \
    {                                                       \
        .prescaler = 40,                                    \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_50K_BAUD                        \
    {                                                       \
        .prescaler = 80,                                    \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_20K_BAUD                        \
    {                                                       \
        .prescaler = 200,                                   \
        .num_seg1 = 10,                                     \
        .num_seg2 = 2,                                      \
        .num_sjw = 2                                        \
    }

#define CAN_BIT_TIME_CONFIG_10K_BAUD                        \
    {                                                       \
        .prescaler = 240,                                   \
        .num_seg1 = 18,                                     \
        .num_seg2 = 4,                                      \
        .num_sjw = 2                                        \
    }

#ifdef __cplusplus
extern "C"
}
#endif
#endif

