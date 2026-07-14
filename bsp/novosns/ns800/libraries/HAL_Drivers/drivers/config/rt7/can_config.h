/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAN_USING_INTERNAL_CLOCK    0U
#define CAN_USING_EXTERNAL_OSC      1U

#ifndef CAN_CLOCK_SELECTION
#define CAN_CLOCK_SELECTION         CAN_USING_EXTERNAL_OSC
#endif

#if CAN_CLOCK_SELECTION == CAN_USING_EXTERNAL_OSC
#define BSP_CAN_CLOCK_FREQ          HXTL_FREQ_VALUE
#elif CAN_CLOCK_SELECTION == CAN_USING_INTERNAL_CLOCK
#define BSP_CAN_CLOCK_FREQ          MIRC2_FREQ_VALUE
#else
#error "Unsupported CAN_CLOCK_SELECTION"
#endif

#ifndef BSP_CAN1_TX_PIN
#define BSP_CAN1_TX_PIN             GPIO_19_CAN1_TX
#endif

#ifndef BSP_CAN1_RX_PIN
#define BSP_CAN1_RX_PIN             GPIO_18_CAN1_RX
#endif

#ifndef BSP_CANFD1_TX_PIN
#define BSP_CANFD1_TX_PIN           GPIO_4_CANFD1_TX
#endif

#ifndef BSP_CANFD1_RX_PIN
#define BSP_CANFD1_RX_PIN           GPIO_10_CANFD1_RX
#endif

#ifndef BSP_CANFD2_TX_PIN
#define BSP_CANFD2_TX_PIN           GPIO_6_CANFD2_TX
#endif

#ifndef BSP_CANFD2_RX_PIN
#define BSP_CANFD2_RX_PIN           GPIO_7_CANFD2_RX
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */

