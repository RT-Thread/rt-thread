/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-11     kurisaW           first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "hal_data.h"

#if defined(BSP_USING_CANFD)

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(BSP_USING_CAN0)
#ifndef CAN0_CONFIG
#define CAN0_CONFIG                   \
    {                                 \
        .name = "canfd0",             \
        .num_of_mailboxs = 48,        \
        .p_api_ctrl = &g_canfd0_ctrl, \
        .p_cfg = &g_canfd0_cfg,       \
    }
#endif /* CAN0_CONFIG */
#endif /* BSP_USING_CAN0 */

#if defined(BSP_USING_CAN1)
#ifndef CAN1_CONFIG
#define CAN1_CONFIG                   \
    {                                 \
        .name = "canfd1",             \
        .num_of_mailboxs = 48,        \
        .p_api_ctrl = &g_canfd1_ctrl, \
        .p_cfg = &g_canfd1_cfg,       \
    }
#endif /* CAN1_CONFIG */
#endif /* BSP_USING_CAN1 */

#ifdef __cplusplus
}
#endif

#endif /* BSP_USING_CANFD */

#endif /* __CAN_CONFIG_H__ */
