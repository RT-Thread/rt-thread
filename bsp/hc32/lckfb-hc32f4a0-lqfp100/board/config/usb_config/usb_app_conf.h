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
/*
USB_FS_MODE, USB_HS_MODE, USB_HS_EXTERNAL_PHY defined comment
(1) If only defined USB_FS_MODE:
    MCU USBFS core work in full speed using internal PHY.
(2) If only defined USB_HS_MODE:
    MCU USBHS core work in full speed using internal PHY.
(3) If both defined USB_HS_MODE && USB_HS_EXTERNAL_PHY
    MCU USBHS core work in high speed using external PHY.
(4) Other combination:
    Not support, forbid!!
*/

#if defined(BSP_USING_USBHS)
#define USB_HS_MODE
#elif defined(BSP_USING_USBFS)
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

#if defined(USB_HS_MODE) && defined(BSP_USING_USBHS_PHY_EXTERN)
#define USB_HS_EXTERNAL_PHY
#endif

#ifndef USB_HS_MODE
#ifndef USB_FS_MODE
#error  "USB_HS_MODE or USB_FS_MODE should be defined"
#endif
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
#define TX6_FIFO_FS_SIZE                        (32U)
#define TX7_FIFO_FS_SIZE                        (32U)
#define TX8_FIFO_FS_SIZE                        (32U)
#define TX9_FIFO_FS_SIZE                        (32U)
#define TX10_FIFO_FS_SIZE                       (32U)
#define TX11_FIFO_FS_SIZE                       (32U)
#define TX12_FIFO_FS_SIZE                       (32U)
#define TX13_FIFO_FS_SIZE                       (32U)
#define TX14_FIFO_FS_SIZE                       (32U)
#define TX15_FIFO_FS_SIZE                       (32U)

#if ((RX_FIFO_FS_SIZE + \
      TX0_FIFO_FS_SIZE + TX1_FIFO_FS_SIZE + TX2_FIFO_FS_SIZE + TX3_FIFO_FS_SIZE + TX4_FIFO_FS_SIZE + \
      TX5_FIFO_FS_SIZE + TX6_FIFO_FS_SIZE + TX7_FIFO_FS_SIZE + TX8_FIFO_FS_SIZE + TX9_FIFO_FS_SIZE + \
      TX10_FIFO_FS_SIZE + TX11_FIFO_FS_SIZE + TX12_FIFO_FS_SIZE + TX13_FIFO_FS_SIZE + TX14_FIFO_FS_SIZE + \
      TX15_FIFO_FS_SIZE) > 640U)
#error  "The USB max FIFO size is 640 x 4 Bytes!"
#endif
#endif

#ifdef USB_HS_MODE
#define RX_FIFO_HS_SIZE                         (512U)
#define TX0_FIFO_HS_SIZE                        (64U)
#define TX1_FIFO_HS_SIZE                        (64U)
#define TX2_FIFO_HS_SIZE                        (64U)
#define TX3_FIFO_HS_SIZE                        (64U)
#define TX4_FIFO_HS_SIZE                        (64U)
#define TX5_FIFO_HS_SIZE                        (64U)
#define TX6_FIFO_HS_SIZE                        (64U)
#define TX7_FIFO_HS_SIZE                        (64U)
#define TX8_FIFO_HS_SIZE                        (64U)
#define TX9_FIFO_HS_SIZE                        (64U)
#define TX10_FIFO_HS_SIZE                       (64U)
#define TX11_FIFO_HS_SIZE                       (64U)
#define TX12_FIFO_HS_SIZE                       (64U)
#define TX13_FIFO_HS_SIZE                       (64U)
#define TX14_FIFO_HS_SIZE                       (64U)
#define TX15_FIFO_HS_SIZE                       (64U)

#if ((RX_FIFO_HS_SIZE + \
      TX0_FIFO_HS_SIZE + TX1_FIFO_HS_SIZE + TX2_FIFO_HS_SIZE + TX3_FIFO_HS_SIZE + TX4_FIFO_HS_SIZE + \
      TX5_FIFO_HS_SIZE + TX6_FIFO_HS_SIZE + TX7_FIFO_HS_SIZE + TX8_FIFO_HS_SIZE + TX9_FIFO_HS_SIZE + \
      TX10_FIFO_HS_SIZE + TX11_FIFO_HS_SIZE + TX12_FIFO_HS_SIZE + TX13_FIFO_HS_SIZE + TX14_FIFO_HS_SIZE + \
      TX15_FIFO_HS_SIZE) > 2048U)
#error  "The USB max FIFO size is 2048 x 4 Bytes!"
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
#define TXH_NP_FS_FIFOSIZ                        (32U)
#define TXH_P_FS_FIFOSIZ                         (64U)

#if ((RX_FIFO_FS_SIZE + TXH_NP_FS_FIFOSIZ + TXH_P_FS_FIFOSIZ) > 640U)
#error  "The USB max FIFO size is 640 x 4 Bytes!"
#endif
#endif

#ifdef USB_HS_MODE
#define RX_FIFO_HS_SIZE                          (512U)
#define TXH_NP_HS_FIFOSIZ                        (128U)
#define TXH_P_HS_FIFOSIZ                         (256U)

#if ((RX_FIFO_FS_SIZE + TXH_NP_FS_FIFOSIZ + TXH_P_FS_FIFOSIZ) > 2048U)
#error  "The USB max FIFO size is 2048 x 4 Bytes!"
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
