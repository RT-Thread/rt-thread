/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
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

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_CAN1
#ifndef CAN1_CONFIG
#define CAN1_CONFIG                                         \
    {                                                       \
       .name = "can1",                                      \
    }
#endif /* CAN1_CONFIG */
#endif /* BSP_USING_CAN1 */

#ifdef BSP_USING_CAN2
#ifndef CAN2_CONFIG
#define CAN2_CONFIG                                         \
    {                                                       \
       .name = "can2",                                      \
    }
#endif /* CAN2_CONFIG */
#endif /* BSP_USING_CAN2 */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */
