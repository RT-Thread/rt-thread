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

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(BSP_USING_CAN0)
#ifndef CANFD0_CONFIG
#define CANFD0_CONFIG                 \
    {                                 \
        .name = "canfd0",             \
        .num_of_mailboxs = 48,        \
        .p_api_ctrl = &g_canfd0_ctrl, \
        .p_cfg = &g_canfd0_cfg,       \
    }
#endif /* CAN0_CONFIG */
#endif /* BSP_USING_CAN0 */

#if defined(BSP_USING_CAN1)
#ifndef CANFD1_CONFIG
#define CANFD1_CONFIG                 \
    {                                 \
        .name = "canfd1",             \
        .num_of_mailboxs = 48,        \
        .p_api_ctrl = &g_canfd1_ctrl, \
        .p_cfg = &g_canfd1_cfg,       \
    }
#endif /* CAN1_CONFIG */
#endif /* BSP_USING_CAN1 */

const canfd_afl_entry_t p_canfd0_afl[CANFD_CFG_AFL_CH0_RULE_NUM] =
{
    {
        .id =
        {
            .id         = 0x00,
            .frame_type = CAN_FRAME_TYPE_DATA,
            .id_mode    = CAN_ID_MODE_STANDARD
        },
        .destination =
        {
            .minimum_dlc       = CANFD_MINIMUM_DLC_0,
            .rx_buffer         = CANFD_RX_MB_NONE,
            .fifo_select_flags = CANFD_RX_FIFO_0
        }
    },
};

const canfd_afl_entry_t p_canfd1_afl[CANFD_CFG_AFL_CH1_RULE_NUM] =
{
    {
        .id =
        {
            .id         = 0x01,
            .frame_type = CAN_FRAME_TYPE_DATA,
            .id_mode    = CAN_ID_MODE_STANDARD
        },
        .destination =
        {
            .minimum_dlc       = CANFD_MINIMUM_DLC_1,
            .rx_buffer         = CANFD_RX_MB_NONE,
            .fifo_select_flags = CANFD_RX_FIFO_1
        }
    },
};

#ifdef __cplusplus
}
#endif
#endif
