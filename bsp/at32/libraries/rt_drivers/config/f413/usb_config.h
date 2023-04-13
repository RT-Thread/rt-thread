/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-28     leo          first version
 */

#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* usb irqhandler */
#define USB_IRQHandler                  USBFS_L_CAN1_RX0_IRQHandler

/**
  * @brief usb endpoint number
  */
#define USB_EPT_MAX_NUM                 8

/**
  * @brief auto malloc usb endpoint buffer
  */
#define USB_EPT_AUTO_MALLOC_BUFFER

#ifndef USB_EPT_AUTO_MALLOC_BUFFER
#define EPT0_TX_ADDR                    0x40
#define EPT0_RX_ADDR                    0x80
#define EPT1_TX_ADDR                    0xC0
#define EPT1_RX_ADDR                    0x100
#define EPT2_TX_ADDR                    0x140
#define EPT2_RX_ADDR                    0x180
#define EPT3_TX_ADDR                    0x00
#define EPT3_RX_ADDR                    0x00
#define EPT4_TX_ADDR                    0x00
#define EPT4_RX_ADDR                    0x00
#define EPT5_TX_ADDR                    0x00
#define EPT5_RX_ADDR                    0x00
#define EPT6_TX_ADDR                    0x00
#define EPT6_RX_ADDR                    0x00
#define EPT7_TX_ADDR                    0x00
#define EPT7_RX_ADDR                    0x00
#endif

/**
  * @brief usb low power wakeup handler enable
  */
#define USB_LOW_POWER_WAKUP

#if defined(BSP_USING_USBD)
#define USBD_CONFIG                                                 \
    {                                                               \
        .name = "usbd",                                             \
        .irqn = USBFS_L_CAN1_RX0_IRQn,                              \
    }
#endif /* BSP_USING_USBD */

#ifdef __cplusplus
}
#endif

#endif
