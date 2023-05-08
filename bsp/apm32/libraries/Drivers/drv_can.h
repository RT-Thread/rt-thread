/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-30     luobeihai    first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#include <rtdevice.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(APM32F10X_HD) || defined(APM32E10X_HD) || defined(APM32S10X_MD)
/* Aliases for __IRQn */
#define CAN1_TX_IRQn                  USBD1_HP_CAN1_TX_IRQn
#define CAN1_RX0_IRQn                 USBD1_LP_CAN1_RX0_IRQn
#define CAN2_TX_IRQn                  USBD2_HP_CAN2_TX_IRQn
#define CAN2_RX0_IRQn                 USBD2_LP_CAN2_RX0_IRQn

/* Aliases for __IRQHandler */
#define CAN1_TX_IRQHandler            USBD1_HP_CAN1_TX_IRQHandler
#define CAN1_RX0_IRQHandler           USBD1_LP_CAN1_RX0_IRQHandler
#define CAN2_TX_IRQHandler            USBD2_HP_CAN2_TX_IRQHandler
#define CAN2_RX0_IRQHandler           USBD2_LP_CAN2_RX0_IRQHandler
#endif /* APM32F10X_HD || APM32E10X_HD || APM32S10X_MD */

struct apm32_baud_rate_tab
{
    uint32_t             baud_rate;
    uint16_t             prescaler;
    CAN_SJW_T            syncJumpWidth;
    CAN_TIME_SEGMENT1_T  timeSegment1;
    CAN_TIME_SEGMENT2_T  timeSegment2;
};

#define APM32_CAN_BAUD_DEF(rate, sjw, tbs1, tbs2, prescale) \
{                                                           \
    .baud_rate = rate,                                      \
    .syncJumpWidth = sjw,                                   \
    .timeSegment1 = tbs1,                                   \
    .timeSegment2 = tbs2,                                   \
    .prescaler = prescale                                   \
}

/* apm32 can device */
struct apm32_can
{
    char *name;
    CAN_T *CANx;
    CAN_Config_T can_init;
    CAN_FilterConfig_T FilterConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CAN_H__ */
