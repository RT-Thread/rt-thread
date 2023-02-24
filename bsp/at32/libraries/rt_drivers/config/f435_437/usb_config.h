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

#if defined BSP_USING_DEVICE_USBFS1 || defined BSP_USING_DEVICE_USBFS2
#define USE_OTG_DEVICE_MODE
#endif

#if defined BSP_USING_HOST_USBFS1 || defined BSP_USING_HOST_USBFS2
#define USE_OTG_HOST_MODE
#endif

/* usbfs irqhandler */
#define OTGFS1_IRQHandler               OTGFS1_IRQHandler
#define OTGFS2_IRQHandler               OTGFS2_IRQHandler

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

/* otg2 device fifo */
#define USBD2_RX_SIZE                   128
#define USBD2_EP0_TX_SIZE               24
#define USBD2_EP1_TX_SIZE               20
#define USBD2_EP2_TX_SIZE               20
#define USBD2_EP3_TX_SIZE               20
#define USBD2_EP4_TX_SIZE               20
#define USBD2_EP5_TX_SIZE               20
#define USBD2_EP6_TX_SIZE               20
#define USBD2_EP7_TX_SIZE               20

/**
  * @brief usb host mode config
  */
#define USB_HOST_CHANNEL_NUM            16

/* otg1 host fifo */
#define USBH_RX_FIFO_SIZE               128
#define USBH_NP_TX_FIFO_SIZE            96
#define USBH_P_TX_FIFO_SIZE             96

/* otg2 host fifo */
#define USBH2_RX_FIFO_SIZE              128
#define USBH2_NP_TX_FIFO_SIZE           96
#define USBH2_P_TX_FIFO_SIZE            96

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

#if defined(BSP_USING_HOST_USBFS1)
#undef BSP_USING_HOST_USBFS2
#undef BSP_USING_DEVICE_USBFS1
#define USBFS1_CONFIG                                               \
    {                                                               \
        .name = "usbh1",                                            \
        .id = USB_OTG1_ID,                                          \
        .irqn = OTGFS1_IRQn,                                        \
    }
#endif /* BSP_USING_HOST_USBFS1 */

#if defined(BSP_USING_DEVICE_USBFS1)
#undef BSP_USING_DEVICE_USBFS2
#define USBFS1_CONFIG                                               \
    {                                                               \
        .name = "usbd",                                             \
        .id = USB_OTG1_ID,                                          \
        .irqn = OTGFS1_IRQn,                                        \
    }
#endif /* BSP_USING_DEVICE_USBFS1 */

#if defined(BSP_USING_HOST_USBFS2)
#undef BSP_USING_HOST_USBFS1
#undef BSP_USING_DEVICE_USBFS2
#define USBFS2_CONFIG                                               \
    {                                                               \
        .name = "usbh2",                                            \
        .id = USB_OTG2_ID,                                          \
        .irqn = OTGFS2_IRQn,                                        \
    }
#endif /* BSP_USING_HOST_USBFS2 */

#if defined(BSP_USING_DEVICE_USBFS2)
#undef BSP_USING_DEVICE_USBFS1
#define USBFS2_CONFIG                                               \
    {                                                               \
        .name = "usbd",                                             \
        .id = USB_OTG2_ID,                                          \
        .irqn = OTGFS2_IRQn,                                        \
    }
#endif /* BSP_USING_DEVICE_USBFS2 */

#ifdef __cplusplus
}
#endif

#endif
