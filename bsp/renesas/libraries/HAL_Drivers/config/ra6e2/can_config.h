/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-10-29     mazhiyuan         first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "hal_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_CAN0)
#ifndef CAN0_CONFIG
#define CAN0_CONFIG                                                 \
    {                                                               \
        .name = "can0",                                            \
        .num_of_mailboxs = CAN_NO_OF_MAILBOXES_g_can0,             \
        .p_api_ctrl = &g_can0_ctrl,                                \
        .p_cfg = &g_can0_cfg,                                      \
    }
#endif /* CAN0_CONFIG */
#endif /* BSP_USING_CAN0 */

#if defined(BSP_USING_CAN1)
#ifndef CAN1_CONFIG
#define CAN1_CONFIG                                                 \
    {                                                               \
        .name = "can1",                                            \
        .num_of_mailboxs = CAN_NO_OF_MAILBOXES_g_can1,             \
        .p_api_ctrl = &g_can1_ctrl,                                \
        .p_cfg = &g_can1_cfg,                                      \
    }
#endif /* CAN1_CONFIG */
#endif /* BSP_USING_CAN1 */

#ifdef __cplusplus
}
#endif
#endif
