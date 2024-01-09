/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

#ifndef __USB_APP_CONF_H__
#define __USB_APP_CONF_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "rtconfig.h"

/* USB MODE CONFIGURATION */


#if defined(BSP_USING_USBFS)
#define USB_FS_MODE
#else
#define USB_FS_MODE
#endif

#if defined(BSP_USING_USBD)
#define USE_DEVICE_MODE
#elif defined(BSP_USING_USBH)
#define USE_HOST_MODE
#else
#define USE_DEVICE_MODE
#endif

#ifndef USB_FS_MODE
#error  "USB_FS_MODE should be defined"
#endif

#ifndef USE_DEVICE_MODE
#ifndef USE_HOST_MODE
#error  "USE_DEVICE_MODE or USE_HOST_MODE should be defined"
#endif
#endif

#if defined(BSP_USING_USBD)
/* USB DEVICE FIFO CONFIGURATION */
#ifdef USB_FS_MODE
#define RX_FIFO_FS_SIZE                         (128U)
#define TX0_FIFO_FS_SIZE                        (32U)
#define TX1_FIFO_FS_SIZE                        (32U)
#define TX2_FIFO_FS_SIZE                        (32U)
#define TX3_FIFO_FS_SIZE                        (32U)
#define TX4_FIFO_FS_SIZE                        (32U)
#define TX5_FIFO_FS_SIZE                        (32U)

#if ((RX_FIFO_FS_SIZE + \
      TX0_FIFO_FS_SIZE + TX1_FIFO_FS_SIZE + TX2_FIFO_FS_SIZE + TX3_FIFO_FS_SIZE + TX4_FIFO_FS_SIZE + \
      TX5_FIFO_FS_SIZE) > 320U)
#error  "The USB max FIFO size is 320 x 4 Bytes!"
#endif
#endif

#if defined(BSP_USING_USBD_VBUS_SENSING)
#define VBUS_SENSING_ENABLED
#endif
#endif

#if defined(BSP_USING_USBH)
/* USB HOST FIFO CONFIGURATION */
#ifdef USB_FS_MODE
#define RX_FIFO_FS_SIZE                          (128U)
#define TXH_NP_FS_FIFOSIZ                        (64U)
#define TXH_P_FS_FIFOSIZ                         (128U)

#if ((RX_FIFO_FS_SIZE + TXH_NP_FS_FIFOSIZ + TXH_P_FS_FIFOSIZ) > 320U)
#error  "The USB max FIFO size is 320 x 4 Bytes!"
#endif
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* __USB_APP_CONF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
