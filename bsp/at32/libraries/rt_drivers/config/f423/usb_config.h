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

#if defined BSP_USING_DEVICE_USBOTG1
#define USE_OTG_DEVICE_MODE
#endif

#if defined BSP_USING_HOST_USBOTG1
#define USE_OTG_HOST_MODE
#endif

/* usb irqhandler */
#define OTGFS1_IRQHandler               OTGFS1_IRQHandler

/**
  * @brief usb device mode config
  */
#define USB_EPT_MAX_NUM                 8

/* otg1 device fifo */
#define USBD_RX_SIZE                    128
#define USBD_EP0_TX_SIZE                24
#define USBD_EP1_TX_SIZE                20
#define USBD_EP2_TX_SIZE                20
#define USBD_EP3_TX_SIZE                20
#define USBD_EP4_TX_SIZE                20
#define USBD_EP5_TX_SIZE                20
#define USBD_EP6_TX_SIZE                20
#define USBD_EP7_TX_SIZE                20

/**
  * @brief usb host mode config
  */
#define USB_HOST_CHANNEL_NUM            16

/* otg1 host fifo */
#define USBH_RX_FIFO_SIZE               128
#define USBH_NP_TX_FIFO_SIZE            96
#define USBH_P_TX_FIFO_SIZE             96

/**
  * @brief usb sof output enable
  */
// #define USB_SOF_OUTPUT_ENABLE

/**
  * @brief usb vbus ignore, not use vbus pin
  */
#define USB_VBUS_IGNORE

/**
  * @brief usb low power wakeup handler enable
  */
// #define USB_LOW_POWER_WAKUP

#if defined(BSP_USING_HOST_USBOTG1)
#undef BSP_USING_DEVICE_USBOTG1
#define USBOTG1_CONFIG                                              \
    {                                                               \
        .name = "usbh",                                             \
        .id = USB_OTG1_ID,                                          \
        .dev_spd = USB_FULL_SPEED_CORE_ID,                          \
        .irqn = OTGFS1_IRQn,                                        \
    }
#endif /* BSP_USING_HOST_USBOTG1 */

#if defined(BSP_USING_DEVICE_USBOTG1)
#define USBOTG1_CONFIG                                              \
    {                                                               \
        .name = "usbd",                                             \
        .id = USB_OTG1_ID,                                          \
        .dev_spd = USB_FULL_SPEED_CORE_ID,                          \
        .irqn = OTGFS1_IRQn,                                        \
    }
#endif /* BSP_USING_DEVICE_USBOTG1 */

#ifdef __cplusplus
}
#endif

#endif
