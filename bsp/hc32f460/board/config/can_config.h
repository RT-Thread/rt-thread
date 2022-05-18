/*
 * Copyright (C) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-13     xiaoxiaolisunny    first version
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

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */
